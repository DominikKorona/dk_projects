/*
 * pca9685_myFunctions.c
 *
 *  Created on: Mar 1, 2024
 *      Author: domko
 */
#include "pca9685_myFunctions.h"

void set_default_value(void){
	  // NOGA - A
	  PCA9685_SetServoAngle(0, 90);
	  PCA9685_SetServoAngle(1, 90);
	  PCA9685_SetServoAngle(2, 90);

	  // NOGA - B
	  PCA9685_SetServoAngle(3, 90);
	  PCA9685_SetServoAngle(4, 90);
	  PCA9685_SetServoAngle(5, 90);

	  // NOGA - C
	  PCA9685_SetServoAngle(6, 90);
	  PCA9685_SetServoAngle(7, 90);
	  PCA9685_SetServoAngle(8, 90);

	  // NOGA - D
	  PCA9685_SetServoAngle(9, 90);
	  PCA9685_SetServoAngle(10, 90);
	  PCA9685_SetServoAngle(11, 90);
}
