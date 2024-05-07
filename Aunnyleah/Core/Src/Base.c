/*
 * Base.c
 *
 *  Created on: May 7, 2024
 *      Author: napat
 */
#include "Modbus.h"
#include "main.h"
#include "kalman.h"
#include "Base.h"
BaseStruct base;

u16u8_t registerFrame[200];

//------------ Function ------------//
void Base_init(BaseStruct* Base)
{
	Base->bStatus = 0;
	Base->PositionZ = 0;
	Base->PositionX = 0;
	Base->Speed = 0;
	Base->Acc = 0;
	Base->Vacuum = 0;
	Base->Gripper = 0;
	Base->ShelveMode = 0; 	//for ps2
	Base->Shelve[5] = 0;
//	Base-> PointMode;
	Base->GoalPoint = 0;
	Base->Pick = 0;
	Base->Place = 0;
	Base->bS = 0;
	Base->vS = 0;
	Base->gmS = 0;
	Base->gmaS = 0;
	Base->zmS = 0;

// for testing
	Base->sw = 0;
	Base->swp = 0;
	Base->sh = 0;
	Base->sp = 0;
}
void ResetState(){
	registerFrame[0x01].U16 = 0;
	registerFrame[0x10].U16 = 0;
}
void easyCase(){
	base.bS = registerFrame[0x01].U16;
	base.vS = registerFrame[0x02].U16;
	base.gmS = registerFrame[0x03].U16;
//	base.gmaS = registerFrame[0x04].U16;
	base.zmS = registerFrame[0x10].U16;
}
void heart(){
	registerFrame[0x00].U16 = 22881;
}

void Routine(){
	if(registerFrame[0x00].U16 == 18537)
	{
		//Gripper 0x04 not sure!?!?
//		  registerFrame[0x04].U16 = 0b0000;
//		  registerFrame[0x04].U16 = 0b0001;   //Gripper status 0b0010 = 0000 0000 0000 0010
		registerFrame[0x10].U16 = base.bStatus;	//Z-axis status 0010 = 1
		registerFrame[0x11].U16 = base.PositionZ	*10;	//Z-axis position
		registerFrame[0x12].U16 = base.Speed		*10;		//Z-axis speed
		registerFrame[0x13].U16 = base.Acc			*10;		//Z-axis acceleration
		registerFrame[0x40].U16 = base.PositionX	*10;	//X-axis position
	}
}

void Vacuum(){
	if(registerFrame[0x02].U16 == 0b0000){
		base.Vacuum = 0;			//Vacuum status: Off
	}
	else if(registerFrame[0x02].U16 == 0b0001){
		base.Vacuum = 1;			//Vacuum status: On
	}
}

void GripperMovement(){
	if(registerFrame[0x03].U16 == 0b0000){
		base.Gripper = 0;			//Gripper Movement: Backward
	}
	else if(registerFrame[0x03].U16 == 0b0001){
		base.Gripper = 1;			//Gripper Movement: Forward
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
		base.bStatus = 0;
		registerFrame[0x01].U16 = base.bStatus;
		registerFrame[0x10].U16 = 0;
		base.sw = 0;
	}
}

void RunPoint(){
	base.GoalPoint = (registerFrame[0x30].U16)/10; //Get Goal point from BaseSytem(Point Mode) that we pick/write After pressing Run Button
	registerFrame[0x10].U16 = 16;
	//finish
	if(base.swp == 1){
		base.bStatus = 0;
		registerFrame[0x01].U16 = base.bStatus;
		registerFrame[0x10].U16 = 0;
		base.swp = 0;
	}
}

void SetHome(){
	registerFrame[0x10].U16 = 2;
	if(base.sh == 1){
		base.bStatus = 0;
		registerFrame[0x01].U16 = base.bStatus;
		registerFrame[0x10].U16 = 0;
		base.sh = 0;
	}
}

void RunJog(){
	base.Pick = registerFrame[0x21].U16 ; 	//Get Pick from BaseSystem
	base.Place = registerFrame[0x22].U16 ;	//Get Place from BaseSystem
	registerFrame[0x10].U16 = 4;
	registerFrame[0x10].U16 = 8;
	//pick place 5 time
	if(base.sp == 1){
		base.bStatus = 0;
		registerFrame[0x01].U16 = base.bStatus;
		registerFrame[0x10].U16 = 0;
		base.sp = 0;
	}
}

void Select_case()
{
	      easyCase();
      switch(base.bS){
      case 1:
          base.bStatus = 4;
          SetShelves();
          base.bS = 0;
          break;
      case 2:
          base.bStatus = 4;
          SetHome();
          base.bS = 0;
          break;
      case 4:
          base.bStatus = 4;
          RunJog();
          base.bS = 0;
          break;
      case 8:
          base.bStatus = 8;
          RunPoint();
          base.bS = 0;
          break;
      default:
          registerFrame[0x01].U16 = 0;;
      }

      switch(base.vS){
      case 0:
          base.Vacuum = 0;
          break;
      case 1:
          base.Vacuum = 1;
          break;
      }

      switch(base.gmS){
      case 0:
          base.Gripper = 0;
          break;
      case 1:
          base.Gripper = 1;
          break;
      }


      Modbus_Protocal_Worker();
      Routine();
}
