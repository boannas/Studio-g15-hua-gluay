/*
 * PS2.c
 *
 *  Created on: May 7, 2024
 *      Author: napat
 */

// Include Library here !
#include <BaseSystem.h>
#include "PS2.h"
#include "main.h"
#include "Motor.h"
#include "ModBusRTU.h"
#include "Encoder.h"
#include "PID_controller.h"

// Import variable from other .c file
PID_struct PID_pos;
BaseStruct base;
extern AMT_Encoder AMT;
extern MOTOR MT;
extern u16u8_t registerFrame[200];

// Define variable inside library
int num[10]= {48,49,50,51,52,53,54,55,56,57};
float count = 1;

//-------------------------------------------Function Code-------------------------------------------------------//

void PS2_init(PS2_typedef* PS2)
{
    PS2->ps2RX[10] = 0;
    PS2->digit= 0;
    PS2->gain[3] = 0;
    PS2->ps2Y = 0;
    PS2->ps2YPos = 0;
    PS2->floor[5] = 0;
    PS2->r[6] = 0;
    PS2->l[6] = 0;
    PS2->pwmOut = 0;
    PS2->mode = 0;
    PS2->stop = 0;
    PS2->counts = 0;
    PS2->PIDPos = 0;
    PS2->on = 0;
}
extern PS2_typedef ps2;

void PS2X_Reader()
{
//	ps2.ps2Y = 0;
//	ps2.ps2X = 0;
	if (ps2.ps2RX[0] == 69) 		//Press L4 to switch to use Joy stick
	{
		ps2.mode = 1;
		ps2.on = 0;
//		ps2.ps2YPos = 132;
	}
	if (ps2.ps2RX[0] == 70)		//Press L5 to switch to use Button
	{
		ps2.mode = 2;
		ps2.on =1;
		ps2.PIDPos = AMT.Linear_Position;


	}
	//Mode Joy stick
	if (ps2.mode == 1)
	{
		//Read Ps2 Joy stick in VERTICAL
		if(ps2.ps2RX[0] == 81){
			if (ps2.ps2RX[2] == 83){
				ps2.digit = 1;
			}
			else if (ps2.ps2RX[3] == 83){
				ps2.digit = 2;
			}
			else if (ps2.ps2RX[4] == 83){
				ps2.digit = 3;
			}
			for(int k=1 ; k<5 ; k++){
				for (int l=0; l<10 ; l++){
					if (ps2.ps2RX[k] == num[l]){
						ps2.gain[k-1] = l;
					}
				}
			}
			if (ps2.digit == 1){
				ps2.ps2YPos = ps2.gain[0];
			}
			else if (ps2.digit == 2){
				ps2.ps2YPos = (ps2.gain[0]*10)+ps2.gain[1];
			}
			else if (ps2.digit == 3){
				ps2.ps2YPos = (ps2.gain[0]*100)+(ps2.gain[1]*10)+ps2.gain[2];
			}
		}

		//Convert from 0 - 255 to -128 - 128
//		ps2.ps2Y = (ps2.ps2YPos - 132);
//		ps2.ps2X = ps2.ps2XPos - 132;

		//Generate PWM
		ps2.pwmOut = ((ps2.ps2Y/ 132.0)*300) + 150;
		ps2.pwmOut = 320 - ps2.ps2YPos;
		if (ps2.pwmOut > 300)
		{
			ps2.pwmOut = 300;
		}
		if (ps2.pwmOut < -300)
		{
			ps2.pwmOut = 0;
		}
		if (ps2.pwmOut < 0)
		{
			MOTOR_set_duty(&MT, 0);
		}
		else if (ps2.pwmOut > 0)
		{
			MOTOR_set_duty(&MT, ps2.pwmOut);
		}
	}

	//--- Mode Button ---//
	else if (ps2.mode == 2)
	{
//		ps2.PIDPos = AMT.Linear_Position;
		ps2.on = 1;
		ps2.ps2Y = 0;
//		ps2.ps2X = 0;
		//Keys Map
		static uint32_t timestamp =0;
		if(timestamp < HAL_GetTick())
		{
			timestamp = HAL_GetTick()+100;
			ps2.ps2RX[0] = 0;
		}
		for (int i =0;i<6;i++)
		{
			if (ps2.ps2RX[0] == 0)
			{
				//Left
				ps2.l[0] = 0; //w
				ps2.l[1] = 0;	//a
				ps2.l[2] = 0;	//s
				ps2.l[3] = 0;	//d
				ps2.l[4] = 0;	//l1
				ps2.l[5] = 0;	//l2
				//Right
				ps2.r[0] = 0;	//w
				ps2.r[1] = 0;	//a
				ps2.r[2] = 0;	//s
				ps2.r[3] = 0;	//d
				ps2.r[4] = 0;	//r1
				ps2.r[5] = 0;	//r2
			}

			if (ps2.ps2RX[0] - 65 == i)
			{
				ps2.l[i] = 1;
			}

			else if (ps2.ps2RX[0] - 73 == i)
			{
				ps2.r[i] = 1;
			}
		}

		//Generate PWM
		if (ps2.l[2] == 1)
		{
			//Adjust How to decrease(-) Linear position
			ps2.PIDPos -= 0.1;
//			ps2.pwmOut = ps2.pwmOut - count;	// - PWM with x
//			if (ps2.pwmOut < 0)
//			{
//				ps2.pwmOut = 0;		// to make pwm1 >= 0
//			}
		}
		else if (ps2.l[3] == 1)
		{
			//Adjust How to increase(+) Linear position
			ps2.PIDPos += 0.1;
//			ps2.pwmOut = ps2.pwmOut + count;	// + PWM with count
		}
		else if (ps2.l[0] == 1)		//Press down button(l1) to PWM out forward
		{
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ps2.pwmOut);
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
		}
		else if (ps2.l[1] == 1)		//Press down button(l1) to PWM out backward
		{
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ps2.pwmOut);
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);
		}
		else if (ps2.r[1] == 1)		//Press X(r1) to stop
		{
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);		//Stop
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
		}
		else{
//			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 150);
			MOTOR_set_duty(&MT, 150);
		}
	}
	// Floor Selection
	if(base.ShelveMode == 1){
		if (ps2.ps2RX[0] == 71){
			base.Shelve[ps2.counts-1] = ps2.PIDPos;
			ps2.counts=  +1;
		}
		else if (ps2.ps2RX[0] == 73){
			base.Shelve[ps2.counts-1] = 0;
			ps2.counts = ps2.counts -1;
		}

		if (ps2.ps2RX[0] == 72 && base.ShelveMode == 1){
			base.ShelveMode = 0;
			registerFrame[0x10].U16 = 0b0000;
		}
	}
}
