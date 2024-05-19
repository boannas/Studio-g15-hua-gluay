/*
 * Encoder_AMT.c
 *
 *  Created on: May 3, 2024
 *      Author: napat
 */

// Include Library here !
#include "Encoder.h"
#include "main.h"
#include "kalman.h"
#include "PID_controller.h"

// Import variable from other .c file
KalmanFilter Vel_filtered;
extern PID_struct PID_velo;

// Define variable inside library
int32_t diffPosition;
uint32_t cnt_per_rev = 8192;
float cnt_per_rev_f = 8192.0;
float pulley_cir = 2.0*(22.0/7.0)*12.5;				// millimeter
float diffTime;
float ALPHA = 0.3f;									// smoothing param
const float cnt_per_rev_inv = 1.0f / 8192.0 ;
const float one_million_inv = 1e-6f;

//-------------------------------------------Function Code-------------------------------------------------------//

long kalman_filter(long ADC_Value)
{
    float x_k1_k1,x_k_k1;
    static float ADC_OLD_Value;
    float Z_k;
    static float P_k1_k1;

    static float Q = 0.0001;//Q: Regulation noise, Q increases, dynamic response becomes faster, and convergence stability becomes worse
    static float R = 0.2; //R: Test noise, R increases, dynamic response becomes slower, convergence stability becomes better
    static float Kg = 0;
    static float P_k_k1 = 1;

    float kalman_adc;
    static float kalman_adc_old=0;
    Z_k = ADC_Value;
    x_k1_k1 = kalman_adc_old;

    x_k_k1 = x_k1_k1;
    P_k_k1 = P_k1_k1 + Q;

    Kg = P_k_k1/(P_k_k1 + R);

    kalman_adc = x_k_k1 + Kg * (Z_k - kalman_adc_old);
    P_k1_k1 = (1 - Kg)*P_k_k1;
    P_k_k1 = P_k1_k1;

    ADC_OLD_Value = ADC_Value;
    kalman_adc_old = kalman_adc;

    return kalman_adc;
}


void AMT_encoder_init(AMT_Encoder *AMT_data,TIM_HandleTypeDef *Encoder_timer)
{
	AMT_data->EncoderTIM = Encoder_timer;
	HAL_TIM_Encoder_Start(AMT_data->EncoderTIM, TIM_CHANNEL_ALL);
	AMT_data->Position[QEI_NOW] = 0.0;
	AMT_data->Position[QEI_PREV] = 0.0;
}

//void AMT_encoder_update(AMT_Encoder *AMT_data, TIM_HandleTypeDef *Encoder_timer, uint64_t current_time)
//{
//	//collect data
//	AMT_data->TimeStamp[QEI_NOW] = current_time;
//	AMT_data->Position[QEI_NOW] = __HAL_TIM_GET_COUNTER(Encoder_timer);
//
//	//Postion 1 turn calculation
//	AMT_data->QEIPostion_1turn = AMT_data->Position[QEI_NOW] % cnt_per_rev;
//
//	//calculate dx
//	diffPosition = AMT_data->Position[QEI_NOW] - AMT_data->Position[QEI_PREV];
//
//	//Handle Warp around
//	if(diffPosition > 32767)
//		diffPosition -= 65535;
//	if(diffPosition < -32767)
//		diffPosition += 65535;
//
//	//calculate dt
//	diffTime = (AMT_data->TimeStamp[QEI_NOW] - AMT_data->TimeStamp[QEI_PREV] );
//
//	//calculate anglar velocity
//	float Vin = (PID_velo.out/1000)*24;
////	AMT_data->Angular_Velocity = lowPassFilter(SteadyStateKalmanFilter(&Vel_filtered,Vin, (diffPosition * 60.0) / (cnt_per_rev * (diffTime / 1e6))));	//RPM
//	AMT_data->Angular_Velocity = (diffPosition * 60.0) / (cnt_per_rev * (diffTime / 1e6));	//RPM
//
//	// Calculate Linear
//	AMT_data->Linear_Position += (diffPosition*pulley_cir)/cnt_per_rev;			//mm
//	AMT_data->Linear_Velocity = (AMT_data->Angular_Velocity / 60.0) * pulley_cir;		//mm/s
//	AMT_data->Linear_Velo[QEI_NOW] = AMT_data->Linear_Velocity;					//Uodate Velo
////	AMT_data->Linear_Acceleration = ((AMT_data->Linear_Velo[QEI_NOW] - AMT_data->Linear_Velo[QEI_PREV]) *  1e6) / (diffTime);		//mm/s^2
//
//	//store value for next loop
//	AMT_data->Position[QEI_PREV] = AMT_data->Position[QEI_NOW];
//	AMT_data->TimeStamp[QEI_PREV] = AMT_data->TimeStamp[QEI_NOW];
//	AMT_data->Linear_Velo[QEI_PREV] = AMT_data->Linear_Velo[QEI_NOW];
//}

void AMT_encoder_update(AMT_Encoder *AMT_data, TIM_HandleTypeDef *Encoder_timer, uint64_t current_time)
{


    // Collect data
    AMT_data->TimeStamp[QEI_NOW] = current_time;
    AMT_data->Position[QEI_NOW] = __HAL_TIM_GET_COUNTER(Encoder_timer);

    // Position 1 turn calculation
    AMT_data->QEIPostion_1turn = AMT_data->Position[QEI_NOW] % cnt_per_rev;

    // Calculate dx
    int32_t diffPosition = AMT_data->Position[QEI_NOW] - AMT_data->Position[QEI_PREV];

    // Handle wrap-around
    if (diffPosition > 32767)
        diffPosition -= 65535;
    if (diffPosition < -32767)
        diffPosition += 65535;

    // Calculate dt
    uint64_t diffTime = AMT_data->TimeStamp[QEI_NOW] - AMT_data->TimeStamp[QEI_PREV];

    // Calculate angular velocity
    float time_seconds = diffTime * one_million_inv;
    AMT_data->Angular_Velocity = ((diffPosition * 60.0f) * cnt_per_rev_inv / time_seconds); // RPM

    // Calculate linear position and velocity
    float position_change_mm = (diffPosition * pulley_cir) * cnt_per_rev_inv;
//    float Vin = base.MotorHome * 24.0 / 1000;
    AMT_data->Linear_Position += position_change_mm; // mm
    AMT_data->Linear_Velocity = (AMT_data->Angular_Velocity / 60.0f * pulley_cir); // mm/s
    AMT_data->Linear_kalmanVelocity = kalman_filter(AMT_data->Linear_Velocity);
    AMT_data->Linear_Velo[QEI_NOW] = AMT_data->Linear_Velocity; // Update Velo

    // Store value for next loop
    AMT_data->Position[QEI_PREV] = AMT_data->Position[QEI_NOW];
    AMT_data->TimeStamp[QEI_PREV] = AMT_data->TimeStamp[QEI_NOW];
    AMT_data->Linear_Velo[QEI_PREV] = AMT_data->Linear_Velo[QEI_NOW];
}


void AMT_encoder_reset(AMT_Encoder *AMT_data)
{
	AMT_data->Linear_Position = 600;
//	AMT_data->Position[QEI_NOW] = 0;

}

float lowPassFilter(float raw_data) {
    // Apply exponential moving average filter
    float filtered_data = ALPHA * raw_data + (1.0f - ALPHA) * filtered_data;
    return filtered_data;
}
