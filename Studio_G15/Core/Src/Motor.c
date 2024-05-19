/*
 * Motor.c
 *
 *  Created on: May 4, 2024
 *      Author: napat
 */

// Include Library here !
#include "Motor.h"
#include "math.h"

//-------------------------------------------Function Code-------------------------------------------------------//

void MOTOR_init(MOTOR* MT,TIM_HandleTypeDef* htimx,uint16_t timd_chx,uint16_t timp_chx)
{
	MT->htimx = htimx;
	MT->timd_chx = timd_chx;
	MT->timp_chx = timp_chx;
	HAL_TIM_PWM_Start_IT(htimx, timp_chx);		// PWM
	HAL_TIM_PWM_Start_IT(htimx, timd_chx);		// Direction

}

void MOTOR_set_duty(MOTOR* MT, float percent_duty)
{
    if (MT == NULL || MT->htimx == NULL) {
        return;
    }
    if(percent_duty*42.499 >= 42499) percent_duty = 42499;
    if(percent_duty*42.499 <= -42499) percent_duty = -42499;

    if (percent_duty == 0) {
        __HAL_TIM_SET_COMPARE(MT->htimx, MT->timd_chx, 0);
        __HAL_TIM_SET_COMPARE(MT->htimx, MT->timp_chx, 0);
    } else if (percent_duty > 0) {
        __HAL_TIM_SET_COMPARE(MT->htimx, MT->timd_chx, 0);
        __HAL_TIM_SET_COMPARE(MT->htimx, MT->timp_chx, (uint32_t)(percent_duty*42.499));
    } else {
        __HAL_TIM_SET_COMPARE(MT->htimx, MT->timd_chx, 42499);
        __HAL_TIM_SET_COMPARE(MT->htimx, MT->timp_chx, (uint32_t)fabs((percent_duty*42.499)));
    }
}

//void MOTOR_set_range(MOTOR* MT, float freq, float duty);


