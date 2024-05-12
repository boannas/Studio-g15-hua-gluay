/*
 * Motor.h
 *
 *  Created on: May 4, 2024
 *      Author: napat
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"

typedef struct {
	TIM_HandleTypeDef* htimx;
	uint16_t timd_chx;
	uint16_t timp_chx;
}MOTOR;

void MOTOR_init(MOTOR* MT,TIM_HandleTypeDef* htimx,uint16_t timd_chx,uint16_t timp_chx);
void MOTOR_set_duty(MOTOR* MT, float percent_duty);
//void MOTOR_set_range(MOTOR* MT, float freq, float duty);

#endif /* INC_MOTOR_H_ */
