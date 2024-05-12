/*
 * PID_Controller.c
 *
 *  Created on: May 4, 2024
 *      Author: porpo
 */
#include "PID_controller.h"
#include "Trapezoidal.h"
#include "Encoder.h"
#include "main.h"

extern Trap_Traj Traj;

float boundary = 0.05;
void PID_controller_init(PID_struct* PID,float UP_Kp, float UP_Ki, float UP_Kd)
{
 PID->Kp = UP_Kp;
 PID->Ki = UP_Ki;
 PID->Kd = UP_Kd;

 PID->Error[n] = 0;
 PID->Error[n_1] = 0;
 PID->Error[n_2] = 0;
 PID->out = 0;
}
void PID_controller_calculate_pos(PID_struct* PID,AMT_Encoder* Feedback, float setpoint)
{
 // Output velocity in boundary of 550mm/s
 PID->Error[n] = setpoint - Feedback->Linear_Position;
 if (!((PID->out >= 550 && PID->Error[n] > 0) || (PID->out <= -550 && PID->Error[n] < 0))) {
     PID->out += ((PID->Kp + PID->Ki + PID->Kd) * PID->Error[n])
                      - ((PID->Kp + (2 * PID->Kd)) * PID->Error[n_1])
                      + (PID->Kd * PID->Error[n_2]);
 }
 PID->Error[n_2] = PID->Error[n_1];
 PID->Error[n_1] = PID->Error[n];
}

void PID_controller_calculate_velo(PID_struct* PID,AMT_Encoder* Feedback, float setpoint)
{
 // Output pwm to drive the motor
 PID->Error[n] = setpoint - Feedback->Linear_Velocity;
 if (!((PID->out >= 1000 && PID->Error[n] > 0) || (PID->out <= -1000 && PID->Error[n] < 0))) {
     PID->out += ((PID->Kp + PID->Ki + PID->Kd) * PID->Error[n])
                      - ((PID->Kp + (2 * PID->Kd)) * PID->Error[n_1])
                      + (PID->Kd * PID->Error[n_2]);
 }
 PID->Error[n_2] = PID->Error[n_1];
 PID->Error[n_1] = PID->Error[n];
}

void PID_controller_cascade(PID_struct* PID_pos, PID_struct* PID_vel, AMT_Encoder* QEI, float setpoint)
{
	PID_controller_calculate_pos(PID_pos, QEI , setpoint);
	PID_controller_calculate_velo(PID_vel, QEI, ((PID_pos->out)));
//	PID_controller_calculate_velo(PID_vel, QEI, Traj.currentVelocity);
}
//void PID_controller_Trajectory(PID_struct* PID_pos, PID_struct* PID_vel, AMT* QEI, Traj* traj);
