/*
 * Encoder_AMT.c
 *
 *  Created on: May 3, 2024
 *      Author: napat
 */

#include "Encoder.h"
#include "main.h"

uint32_t cnt_per_rev = 8192.0;
float pulley_cir = 2.0*(22.0/7.0)*12.5;				//mm
int32_t diffPosition;
float diffTime;
float filtered_data;
float ALPHA = 0.3f;

void AMT_encoder_init(AMT_Encoder *AMT_data,TIM_HandleTypeDef *Encoder_timer)
{
	AMT_data->EncoderTIM = Encoder_timer;
	HAL_TIM_Encoder_Start(AMT_data->EncoderTIM, TIM_CHANNEL_ALL);
	AMT_data->Position[QEI_NOW] = 10.0;
	AMT_data->Position[QEI_PREV] = 10.0;
}

void AMT_encoder_update(AMT_Encoder *AMT_data, TIM_HandleTypeDef *Encoder_timer, uint64_t current_time)
{
	//collect data
	AMT_data->TimeStamp[QEI_NOW] = current_time;
	AMT_data->Position[QEI_NOW] = __HAL_TIM_GET_COUNTER(Encoder_timer);

	//Postion 1 turn calculation
	AMT_data->QEIPostion_1turn = AMT_data->Position[QEI_NOW] % cnt_per_rev;

	//calculate dx
	diffPosition = AMT_data->Position[QEI_NOW] - AMT_data->Position[QEI_PREV];

	//Handle Warp around
	if(diffPosition > 32767)
		diffPosition -= 65535;
	if(diffPosition < -32767)
		diffPosition += 65535;

	//calculate dt
	diffTime = (AMT_data->TimeStamp[QEI_NOW] - AMT_data->TimeStamp[QEI_PREV] );

	//calculate anglar velocity
	AMT_data->Angular_Velocity = (diffPosition * 60.0) / (cnt_per_rev * (diffTime / 1e6));	//RPM
	AMT_data->Linear_Position += (diffPosition*pulley_cir)/cnt_per_rev;			//mm
	AMT_data->Linear_Velocity = lowPassFilter((AMT_data->Angular_Velocity / 60.0) * pulley_cir);		//mm/s
	AMT_data->Linear_Velo[QEI_NOW] = AMT_data->Linear_Velocity;					//Uodate Velo
//	AMT_data->Linear_Acceleration = ((AMT_data->Linear_Velo[QEI_NOW] - AMT_data->Linear_Velo[QEI_PREV]) *  1000000.0) / (diffTime);		//mm/s^2

	//store value for next loop
	AMT_data->Position[QEI_PREV] = AMT_data->Position[QEI_NOW];
	AMT_data->TimeStamp[QEI_PREV] = AMT_data->TimeStamp[QEI_NOW];
	AMT_data->Linear_Velo[QEI_PREV] = AMT_data->Linear_Velo[QEI_NOW];
}

void AMT_encoder_reset(AMT_Encoder *AMT_data)
{
	AMT_data->Linear_Position = 0;
	AMT_data->Position[QEI_NOW] = 0;

}

float lowPassFilter(float raw_data) {
    // Apply exponential moving average filter
    filtered_data = ALPHA * raw_data + (1.0f - ALPHA) * filtered_data;
    return filtered_data;
}
