/*
 * Trapezoidal.h
 *
 *  Created on: May 5, 2024
 *      Author: napat
 */

#ifndef INC_TRAPEZOIDAL_H_
#define INC_TRAPEZOIDAL_H_
#include "main.h"

typedef struct
	{
		// for record New / Old value to calculate dx / dt
	float Velo_max;						// units per second
	float Accel_max;					// units per second squared

	float currentPosition ;
	float currentVelocity ;
	float currentAcceleration;

	} Trap_Traj;

	void Traject_init(Trap_Traj* Traj, float v_max, float a_max);
	void Traject(Trap_Traj* Traj, float Pos_initial, float Pos_final);


#endif /* INC_TRAPEZOIDAL_H_ */
