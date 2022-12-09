/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for the AVR PWM timer0 driver
 *
 * Date Creation : Oct 9, 2021
 *
 * Author: Youssef Abdel Aziz
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_


#include "std_types.h"
/*******************************************************************************
 *                      Variable Prototypes                                   *
 *******************************************************************************/

extern uint8 g_duty_cycle;/*SW global variable so that the dc_motor driver can
 	 	 	 	 	 	 	use it to communicate with the PWM driver to select the
 	 	 	 	 	 	 	duty cycle and control the motor speed*/

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Function Name: Timer0_PWM_Init
 * description: initialize the AVR Timer0 driver to generate a fast PWM signal
 * with a certain duty cycle
 * Argument :the desired duty cycle of the pulse
 */

void Timer0_PWM_Init(uint8 a_set_duty_cycle);

#endif /* PWM_H_ */
