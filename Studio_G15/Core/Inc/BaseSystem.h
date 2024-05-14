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

extern ModbusHandleTypedef hmodbus;
extern u16u8_t registerFrame[200];
extern int caseF;
typedef struct{
	uint16_t BaseStatus;
	uint32_t PositionZ;
	uint32_t PositionX;
	uint32_t Speed;
	uint32_t Acc;
	uint16_t Vacuum;
	uint16_t Gripper;
	uint16_t ShelveMode; 	//for ps2
	int Shelve[5];
//	uint16_t PointMode;
	uint16_t GoalPoint;
	uint16_t Pick;
	uint16_t Place;
	uint16_t Base_case;	//bs
	uint16_t Vacuum_case;			//vS
	uint16_t Gripper_case;	//gms
	uint16_t ReedStatus;
//	uint16_t Z_axis_movement_status;	//zms

// for testing
	uint16_t sw;
	uint16_t swp;
	uint16_t sh;
	uint16_t sp;
	uint16_t MotorHome;

}BaseStruct;
extern BaseStruct base;

//------------ Function ------------//

extern void Reset();
extern void easyCase();
extern void Heartbeat();
extern void Routine();
extern void Vacuum();
extern void GripperMovement();
extern void GripperMovementStatus();
extern void SetShelves();
extern void RunPoint();
extern void SetHome();
extern void RunJog();

#endif /* INC_BASESYSTEM_H_ */

