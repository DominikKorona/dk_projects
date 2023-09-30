/*
 * tb6612fng.c
 *
 *  Created on: Sep 19, 2023
 *      Author: domko
 */

#include "main.h"
#include "tb6612fng.h"

void tb6612fng_init()
{

	tb6612fng_mode_control(LOW, HIGH);
	tb6612fng_set_motorA_speed(0);

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

void tb6612fng_mode_control(TB6612FNG_INPUT in1, TB6612FNG_INPUT in2)
{
	/*
	 *  IN1=0 | IN2=1  | ClockWise         |
	 *  IN1=1 | IN2=0  | Counter ClockWise |
	 * **/

	if (in1==HIGH){
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, SET);
	}else if (in1==LOW){
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, RESET);
	}
	if (in2==HIGH){
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, SET);
	}else if (in2==LOW){
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, RESET);
	}
	HAL_GPIO_WritePin(ASTBY_GPIO_Port, ASTBY_Pin, SET);
}

void tb6612fng_set_motorA_speed(uint8_t speed)
{
//	if(speed >= htim2.Instance->ARR)
//		speed = htim2.Instance->ARR;
	if(speed >= 100)
		speed = 99;
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, speed);
}
