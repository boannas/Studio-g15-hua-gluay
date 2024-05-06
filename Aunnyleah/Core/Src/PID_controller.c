/*
 * PID_Controller.c
 *
 *  Created on: May 4, 2024
 *      Author: porpo
 */
#include "PID_controller.h"
#include "Encoder.h"
#include "main.h"

float boundary = 0.05;
void PID_controller_init(PID_struct* PID,float UP_Kp, float UP_Ki, float UP_Kd, float Down_Kp, float Down_Ki, float Down_Kd)
{
 PID->Upward_Kp = UP_Kp;
 PID->Upward_Ki = UP_Ki;
 PID->Upward_Kd = UP_Kd;

 PID->Downward_Kp = Down_Kp;
 PID->Downward_Ki = Down_Ki;
 PID->Downward_Kd = Down_Kd;

 PID->Error[n] = 0;
 PID->Error[n_1] = 0;
 PID->Error[n_2] = 0;
 PID->out = 0;
}
void PID_controller_calculate(PID_struct* PID,AMT_Encoder* Feedback, float setpoint)
{
 // Distance between setpoint real read
 PID->Error[n] = setpoint - Feedback->Linear_Position;
// if(fabs(PID->Error[n]) >= boundary)
// {
 if (!((PID->out >= 1000 && PID->Error[n] > 0) || (PID->out <= -1000 && PID->Error[n] < 0))) {
     PID->out += ((PID->Upward_Kp + PID->Upward_Ki + PID->Upward_Kd) * PID->Error[n])
                      - ((PID->Upward_Kp + (2 * PID->Upward_Kd)) * PID->Error[n_1])
                      + (PID->Upward_Kd * PID->Error[n_2]);
 }
// }
// else PID->out = -150;

 PID->Error[n_2] = PID->Error[n_1];
 PID->Error[n_1] = PID->Error[n];
}

void PID_controller_calculate_velo(PID_struct* PID,AMT_Encoder* Feedback, float setpoint)
{
 // Distance between setpoint real read
 PID->Error[n] = setpoint - Feedback->Linear_Velocity;
// if(fabs(PID->Error[n]) >= boundary)
// {
 if (!((PID->out >= 1000 && PID->Error[n] > 0) || (PID->out <= -1000 && PID->Error[n] < 0))) {
     PID->out += ((PID->Upward_Kp + PID->Upward_Ki + PID->Upward_Kd) * PID->Error[n])
                      - ((PID->Upward_Kp + (2 * PID->Upward_Kd)) * PID->Error[n_1])
                      + (PID->Upward_Kd * PID->Error[n_2]);
 }
// }
// else PID->out = -150;
 PID->Error[n_2] = PID->Error[n_1];
 PID->Error[n_1] = PID->Error[n];

}

void PID_controller_cascade(PID_struct* PID_pos, PID_struct* PID_vel, AMT_Encoder* QEI, float setpoint)
{
	PID_controller_calculate(PID_pos, QEI , setpoint);
	PID_controller_calculate_velo(PID_vel, QEI, PID_pos->out);
}
//void PID_controller_Trajectory(PID_struct* PID_pos, PID_struct* PID_vel, AMT* QEI, Traj* traj);
