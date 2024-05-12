/*
 * PID_controler.h
 *
 *  Created on: May 4, 2024
 *      Author: porpo
 */

#ifndef INC_PID_CONTROLER_H_
#define INC_PID_CONTROLER_H_
#include "Encoder.h"

typedef struct
{
 // PID Constant for upward and downward case
 float Kp;
 float Ki;
 float Kd;

 // Error to target point
 float Error[3];
 float out;
}PID_struct;

enum
{
 n,n_1,n_2
};

void PID_controller_init(PID_struct* PID,float UP_Kp, float UP_Ki, float UP_Kd);
void PID_controller_calculate_pos(PID_struct* PID,AMT_Encoder* Feedback, float setpoint);
void PID_controller_cascade(PID_struct* PID_pos, PID_struct* PID_vel, AMT_Encoder* QEI, float setpoint);
void PID_controller_calculate_velo(PID_struct* PID,AMT_Encoder* Feedback, float setpoint);
//void PID_controller_Trajectory(PID_struct* PID_pos, PID_struct* PID_vel, AMT* QEI, Traj* traj);

#endif /* INC_PID_CONTROLER_H_ */
