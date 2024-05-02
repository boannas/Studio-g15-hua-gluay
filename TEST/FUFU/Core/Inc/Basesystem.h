/*
 * Basesystem.h
 *
 *  Created on: Apr 30, 2024
 *      Author: porpo
 */

#ifndef INC_BASESYSTEM_H_
#define INC_BASESYSTEM_H_

#include <ModBusRTU.h>

//------------ PV ------------//

ModbusHandleTypedef hmodbus;
u16u8_t registerFrame[200];

typedef struct{
	uint32_t Position;
	uint32_t Speed;
	uint32_t Acc;
	uint16_t Vacuum;
	uint16_t Gripper;
	uint16_t ShelveMode;
	int Shelve[5];
	uint16_t PointMode;
	uint16_t GoalPoint;
}BaseStruct;
BaseStruct base = {0};



//------------ Function ------------//
void Heartbeat()
{
	registerFrame[0x00].U16 = 22881;
}

void Routine()
{
	if(registerFrame[0x00].U16 == 18537)
	{
		  registerFrame[0x04].U16 = 0b0001;
		  registerFrame[0x04].U16 = 0b0010;   //Gripper status 0b0010 = 0000 0000 0000 0010
		  registerFrame[0x10].U16 = 0010;	//Z-axis status
		  registerFrame[0x11].U16 = base.Position*10;	//Z-axis position
		  registerFrame[0x12].U16 = base.Speed*10;		//Z-axis speed
		  registerFrame[0x13].U16 = base.Acc*10;		//Z-axis acceleration
		  registerFrame[0x40].U16 = 40;
	}
}

void Vacuum()
{
	if(registerFrame[0x02].U16 == 0b0000){
		base.Vacuum = 0;			//Vacuum status: Off
	}
	else if(registerFrame[0x02].U16 == 0b0001){
		base.Vacuum = 1;			//Vacuum status: On
	}
}

void GripperMovement()
{
	if(registerFrame[0x03].U16 == 0b0000){
		base.Gripper = 0;			//Gripper Movement: Backward
	}
	else if(registerFrame[0x03].U16 == 0b0001){
		base.Gripper = 1;			//Gripper Movement: Forward
	}
}

void SetShelves()
{
	if(registerFrame[0x01].U16 == 0b0001){
		base.ShelveMode = 1;
		registerFrame[0x01].U16 = 0b0000;
		registerFrame[0x10].U16 = 0b0001;
		if (base.ShelveMode == 0){
			registerFrame[0x23].U16 = base.Shelve[0]*10; 	// 0 = Position Shelve 1
			registerFrame[0x24].U16 = base.Shelve[0]*10;
			registerFrame[0x25].U16 = base.Shelve[0]*10;
			registerFrame[0x26].U16 = base.Shelve[0]*10;
			registerFrame[0x27].U16 = base.Shelve[0]*10;
		}
	}
}

void SetGoalPoint()
{
	base.GoalPoint = registerFrame[0x30].U16;
}

void RunPointMode()
{
	if(registerFrame[0x01].U16 == 0b1000)		//Run Point Mode
	{
		base.PointMode = 1;
		registerFrame[0x01].U16 = 0b0000;		//Reset Base System Status
		registerFrame[0x10].U16 = 0b0001;	//Update Z-axis Moving Status (Going to p
		registerFrame[0x10].U16 = 0b0000;		//Update Z-axis Moving Status (Finish)
	}
}



#endif /* INC_BASESYSTEM_H_ */
