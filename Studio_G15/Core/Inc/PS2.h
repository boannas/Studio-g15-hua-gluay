/*
 * PS2.h
 *
 *  Created on: May 7, 2024
 *      Author: napat
 */

#ifndef INC_PS2_H_
#define INC_PS2_H_

#include "main.h"

typedef struct
	{
    uint8_t ps2RX[10];
    int digit;
    int gain[3];
    int ps2Y;
    int ps2YPos;
    int floor[5];
    int r[6];
    int l[6];
    int pwmOut;
    int mode;
    int stop;
    int counts;
    float PIDPos;
    int on;
	} PS2_typedef;
extern PS2_typedef ps2;

void PS2X_Reader();
void PS2_init();

#endif /* INC_PS2_H_ */
