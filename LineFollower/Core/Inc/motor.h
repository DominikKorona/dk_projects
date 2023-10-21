/*
 * motor.h
 *
 *  Created on: Sep 27, 2023
 *      Author: domko
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

typedef enum
{
	SLEEP = 0,
	START = 1
}TB6612_Mode;

typedef enum
{
	CW = 0, //cockwise
	CCW = 1 //counterclockwise
}TB6612_Direction;

extern TIM_HandleTypeDef htim1;

void tb6612_init();
void motor_a_direction(TB6612_Direction);
void motor_a_speed(int8_t);
void motor_b_direction(TB6612_Direction);
void motor_b_speed(int8_t);
void tb6612_mode_control(TB6612_Mode);

#endif /* INC_MOTOR_H_ */
