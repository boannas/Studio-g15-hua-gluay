/*
 * Basesystem.h
 *
 *  Created on: May 7, 2024
 *      Author: napat
 */

#ifndef INC_BASE_H_
#define INC_BASE_H_

#include <Modbus.h>



typedef struct{
	uint16_t bStatus;
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
	uint16_t bS;
	uint16_t vS;
	uint16_t gmS;
	uint16_t gmaS;
	uint16_t zmS;

// for testing
	uint16_t sw;
	uint16_t swp;
	uint16_t sh;
	uint16_t sp;

}BaseStruct;

//------------ Function ------------//
void Base_init();
//void ResetState();
//void easyCase(){;
//void heart();
//void Routine();
//void Vacuum();
//void GripperMovement();
//void SetShelves();
//void RunPoint();
//void SetHome();
//void RunJog();


#endif /* INC_BASE_H_ */
