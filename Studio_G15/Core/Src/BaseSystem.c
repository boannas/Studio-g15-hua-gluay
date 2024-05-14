/*
 * BaseSystem.c
 *
 *  Created on: May 12, 2024
 *      Author: porpo
 */

// Include Library here !
#include "BaseSystem.h"
#include "main.h"
#include "Encoder.h"
#include "Motor.h"
#include "Trapezoidal.h"
#include "stm32g4xx_hal.h"

// Import variable from other .c file
extern AMT_Encoder AMT;
extern MOTOR MT;
extern Trap_Traj Traj;
//-------------------------------------------Function Code-------------------------------------------------------//

void Reset(){
	registerFrame[0x01].U16 = 0;
	registerFrame[0x10].U16 = 0;
}

void easyCase(){
	base.Base_case = registerFrame[0x01].U16;
	base.Vacuum_case = registerFrame[0x02].U16;
	base.Gripper_case = registerFrame[0x03].U16;
}

void Heartbeat(){
	registerFrame[0x00].U16 = 22881;
}

void Routine(){
	if(registerFrame[0x00].U16 == 18537)
	{
		//Gripper 0x04 not sure!?!?
		registerFrame[0x04].U16 = base.ReedStatus;   					//Gripper status 0b0010 = 0000 0000 0000 0010
		registerFrame[0x10].U16 = base.BaseStatus;							//Z-axis status 0010 = 1
		registerFrame[0x11].U16 = AMT.Linear_Position			*10;	//Z-axis position
		registerFrame[0x12].U16 = fabs(AMT.Linear_Velocity)		*10;	//Z-axis speed
		registerFrame[0x13].U16 = fabs(AMT.Linear_Acceleration)	*10;	//Z-axis acceleration
		registerFrame[0x40].U16 = 4								*10;	//X-axis position
	}
}

void Vacuum(){
	if(registerFrame[0x02].U16 == 0b0000){
		base.Vacuum = 0;			//Vacuum status: Off
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, RESET);			// Vacuum off


	}
	else if(registerFrame[0x02].U16 == 0b0001){
		base.Vacuum = 1;			//Vacuum status: On
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, SET);			// Vacuum on

	}
}

void GripperMovement(){
	if(registerFrame[0x03].U16 == 0b0000){
		base.Gripper = 0;			//Gripper Movement: Backward
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, SET);			// Backward
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, RESET);
	}
	else if(registerFrame[0x03].U16 == 0b0001){
		base.Gripper = 1;			//Gripper Movement: Forward
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, RESET);			//Forward
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, SET);
	}
}



void SetShelves(){
	registerFrame[0x10].U16 = 1; 		//Z-axis update z-xis moving status to "Set Shelves"
	// save Position = floor[0] for moving to that position
	// set shelves 1 = 100 mm shelves 2 = 250 mm
	registerFrame[0x23].U16 = 10 *10; 	//0 = Position Shelve 1
	registerFrame[0x24].U16 = 20 *10;
	registerFrame[0x25].U16 = 30 *10;
	registerFrame[0x26].U16 = 40 *10;
	registerFrame[0x27].U16 = 50 *10;
	//finish
	if (base.sw == 1){
		base.BaseStatus = 0;
		registerFrame[0x01].U16 = base.BaseStatus;
		registerFrame[0x10].U16 = 0;
		base.sw = 0;
	}
}

void RunPoint(){
	base.GoalPoint = (registerFrame[0x30].U16)/10; //Get Goal point from BaseSytem(Point Mode) that we pick/write After pressing Run Button
	registerFrame[0x10].U16 = 16;
//	Traject(j);
	//finish
	if(base.swp == 1){
		base.BaseStatus = 0;
		registerFrame[0x01].U16 = base.BaseStatus;
		registerFrame[0x10].U16 = 0;
		base.swp = 0;
	}
}

void SetHome(){
	registerFrame[0x10].U16 = 2;
	base.MotorHome = 350;		// Set duty cycle to go upward at slowest speed
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET)		// Top photo limit was triggered
		{
			base.MotorHome = 150;		// Set duty cycle to hold position gripper
			AMT_encoder_reset(&AMT);	// Set linear position to ...
			base.BaseStatus = 0;
			registerFrame[0x01].U16 = base.BaseStatus;
			registerFrame[0x10].U16 = 0;
		}
}

void RunJog(){
	base.Pick = registerFrame[0x21].U16 ; 	//Get Pick from BaseSystem
	base.Place = registerFrame[0x22].U16 ;	//Get Place from BaseSystem
	registerFrame[0x10].U16 = 4;
	registerFrame[0x10].U16 = 8;
	//pick place 5 time
	if(base.sp == 1){
		base.BaseStatus = 0;
		registerFrame[0x01].U16 = base.BaseStatus;
		registerFrame[0x10].U16 = 0;
		base.sp = 0;
	}
}


