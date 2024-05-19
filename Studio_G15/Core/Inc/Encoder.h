/*
 * Encoder.h
 *
 *  Created on: May 2, 2024
 *      Author: napat
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "main.h"
typedef struct
	{
		// for record New / Old value to calculate dx / dt
		uint32_t Position[2];
		uint64_t TimeStamp[2];
		float Linear_Velo[2];
		int QEIPostion_1turn;
		float Angular_Velocity;			//RPM
		float Linear_Acceleration;		//mm/s^2
		float Linear_Velocity;			//mm/s
		float Linear_kalmanVelocity;
		float Linear_Position;			//mm
		TIM_HandleTypeDef *EncoderTIM;	//Difine Encoder Timer

	} AMT_Encoder;

	enum
	{
	QEI_NOW,QEI_PREV
	};
	// Encoder Funtion
	void AMT_encoder_init(AMT_Encoder *AMT_data,TIM_HandleTypeDef *Encoder_timer);
	void AMT_encoder_update(AMT_Encoder *AMT_data, TIM_HandleTypeDef *Encoder_timer, uint64_t current_time);
	void AMT_encoder_reset(AMT_Encoder *AMT_data);
	float lowPassFilter(float raw_data);

#endif /* INC_ENCODER_H_ */
