/*
 * tb6612fng.h
 *
 *  Created on: Sep 19, 2023
 *      Author: domko
 */

#ifndef INC_TB6612FNG_H_
#define INC_TB6612FNG_H_

#include "main.h"


extern TIM_HandleTypeDef htim2;

typedef enum
{
	LOW = 0,
	HIGH = 1
}TB6612FNG_INPUT;

void tb6612fng_init();
void tb6612fng_mode_control(TB6612FNG_INPUT, TB6612FNG_INPUT);
void tb6612fng_set_motorA_speed(uint8_t);

#endif /* INC_TB6612FNG_H_ */
