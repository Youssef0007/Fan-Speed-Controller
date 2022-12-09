/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: source file for the AVR PWM timer0 driver
 *
 * Date Creation : Oct 9, 2021
 *
 * Author: Youssef Abdel Aziz
 *
 *******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"
#include "pwm.h"
/*******************************************************************************
 *                         Global Variables                                    *
 *******************************************************************************/

uint8 g_duty_cycle;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Function Name: Timer0_PWM_Init
 * description: initialize the AVR Timer0 driver to generate a fast PWM signal
 * with a certain duty cycle
 * Argument :the desired duty cycle of the pulse
 */
void Timer0_PWM_Init(uint8 a_set_duty_cycle)
{
	TCNT0 = 0; // Set Timer Initial Value to 0

	OCR0  = a_set_duty_cycle; //Set Compare value

	GPIO_setupPinDirection( PORTB_ID , PIN3_ID , PIN_OUTPUT ); // Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);


}
