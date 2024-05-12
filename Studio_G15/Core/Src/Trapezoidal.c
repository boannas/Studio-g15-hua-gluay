/*
 * Trapezoidal.c
 *
 *  Created on: May 5, 2024
 *      Author: napat
 */

// Include Library here !
#include "Trapezoidal.h"
#include "main.h"
#include "math.h"

// Import variable from other .c file
extern float elapsedTime;

// Define variable inside library
float Acc_max ;
float Vel_max;
float Distance_Velo_Max;
float Time_Velo_const;
float Time_acc_under;
float temp_pos_acc;
float temp_pos_const;
float temp_velo_acc;
float time_ref1;
float time_ref2;
float Distance;
float Time_acc;
float Time_dec;

//-------------------------------------------Function Code-------------------------------------------------------//

void Traject_init(Trap_Traj* Traj, float v_max, float a_max)
{
	Traj->Velo_max = v_max;
	Traj->Accel_max = a_max;

	Traj->currentAcceleration = 0;
	Traj->currentVelocity = 0;
	Traj->currentPosition = 0;
}

void Traject(Trap_Traj* Traj, float Pos_initial, float Pos_final)
{

	  Distance = Pos_final - Pos_initial;
	  Time_acc = Traj->Velo_max / Traj->Accel_max;
	  Time_dec = Time_acc;


	  if (Distance >0)
			{
		  Acc_max = Traj->Accel_max;
		  Vel_max = Traj->Velo_max;
		  Distance_Velo_Max = Distance - (Vel_max * Time_acc);
		  Time_Velo_const = Distance_Velo_Max / Vel_max;
			}
	  else if(Distance < 0)
	  {
		  Acc_max = -Traj->Accel_max;
		  Vel_max = -Traj->Velo_max;
		  Distance_Velo_Max = Distance - (Vel_max * Time_acc);
		  Time_Velo_const = Distance_Velo_Max / Vel_max;
	}
	// Update trajectory phase
	time_ref1 = Time_acc + Time_Velo_const;
	time_ref2 = time_ref1 + Time_dec;
	if(Time_Velo_const >0)
	{
//		Time_acc_under = sqrt(Distance/Acc_max);
		if (elapsedTime < Time_acc)
		{
			// Acceleration phase
			Traj->currentAcceleration = Acc_max;
			Traj->currentVelocity = Acc_max * elapsedTime;
			Traj->currentPosition = 0.5f * Acc_max * elapsedTime * elapsedTime + Pos_initial;
			temp_pos_acc = Traj->currentPosition;
			temp_pos_const = Traj->currentPosition;
		}
		else if (elapsedTime < time_ref1 )
		{
			// Constant velocity phase
			Traj->currentAcceleration = 0;
			Traj->currentVelocity = Vel_max;
			Traj->currentPosition = (Vel_max * (elapsedTime-Time_acc)) + temp_pos_acc;
			temp_pos_const = Traj->currentPosition;
		}
		else if (elapsedTime < time_ref2)
		{
			// Deceleration phase
			Traj->currentAcceleration = -Acc_max;
			Traj->currentVelocity = -(Acc_max * (elapsedTime-time_ref1)) + Vel_max;
			Traj->currentPosition = Traj->currentVelocity*(elapsedTime-time_ref1)+(0.5f*Acc_max*(elapsedTime-time_ref1)*(elapsedTime-time_ref1))+temp_pos_const ;
		}
		else {
			// Trajectory complete
			Traj->currentAcceleration = 0.0f;
			Traj->currentVelocity = 0.0f;
//			elapsedTime = 0.0f;
		}
	}
	if (Time_Velo_const <= 0)
	{
		Time_acc_under = sqrt(Distance/Acc_max);
//	            	currentPosition++;
		if (elapsedTime < Time_acc_under)
		{
			Traj->currentAcceleration = Acc_max;
			Traj->currentVelocity = Acc_max * elapsedTime;
			Traj->currentPosition = Pos_initial + 0.5f * Acc_max * elapsedTime * elapsedTime;
			temp_pos_acc = Traj->currentPosition;
			temp_velo_acc = Traj->currentVelocity;
		}
		else if (elapsedTime < 2*Time_acc_under)
		{
			Traj->currentAcceleration = -Acc_max;
			Traj->currentVelocity = temp_velo_acc - Acc_max*(elapsedTime-Time_acc_under);
			Traj->currentPosition = temp_pos_acc + Traj->currentVelocity *(elapsedTime-Time_acc_under)+(0.5f*Acc_max*(elapsedTime-Time_acc_under)*(elapsedTime-Time_acc_under));
		}
		else
		{
			Traj->currentAcceleration = 0.0f;
			Traj->currentVelocity = 0.0f;
//			elapsedTime = 0.0f;

		}


	}
}
