/*
 * motor.c
 *
 *  Created on: Sep 27, 2023
 *      Author: domko
 */
#include "main.h"
#include "motor.h"

#define ABS(x)   ((x) > 0 ? (x) : -(x))

void tb6612_init()
{
	tb6612_mode_control(START);
	motor_a_direction(CCW);
	motor_b_direction(CW);
	motor_a_speed(0);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	motor_b_speed(0);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

void motor_a_direction(TB6612_Direction dir){
	if (dir==CW){
		HAL_GPIO_WritePin(A_IN1_GPIO_Port, A_IN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(A_IN2_GPIO_Port, A_IN2_Pin, GPIO_PIN_RESET);
	}else if(dir==CCW){
		HAL_GPIO_WritePin(A_IN1_GPIO_Port, A_IN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(A_IN2_GPIO_Port, A_IN2_Pin, GPIO_PIN_SET);
	}
}

void motor_a_speed(uint8_t speed)
{
	motor_a_direction(CCW);
//	if(speed >= 90)
//		speed = 89;
	if(speed < 0){
		motor_a_direction(CW);
		ABS(speed);
	}
	if(ABS(speed) >= 100)
		speed = 99;
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, speed);
}


void motor_b_direction(TB6612_Direction dir){
	if (dir==CW){
		HAL_GPIO_WritePin(B_IN1_GPIO_Port, B_IN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(B_IN2_GPIO_Port, B_IN2_Pin, GPIO_PIN_RESET);
	}else if(dir==CCW){
		HAL_GPIO_WritePin(B_IN1_GPIO_Port, B_IN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(B_IN2_GPIO_Port, B_IN2_Pin, GPIO_PIN_SET);
	}
}

void motor_b_speed(uint8_t speed)
{
//	if(speed >= 100)
//		speed = 99;
	motor_b_direction(CW);

	if(speed < 0){
		motor_b_direction(CCW);
		ABS(speed);
//		speed +=15;
	}
	if(ABS(speed) >= 100)
		speed = 99;

	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, speed);
}

void tb6612_mode_control(TB6612_Mode mode){
	if (mode==SLEEP){
		HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_RESET);
	}else if(mode==START){
		HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
	}
}
