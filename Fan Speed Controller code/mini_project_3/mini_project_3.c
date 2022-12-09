/******************************************************************************
 *
 * File Name: Mini project 3 fan speed controller
 *
 * Date Creation : Oct 9, 2021
 *
 * Description: project Main file
 *
 * Author: Youssef Abdel Aziz
 *
 *******************************************************************************/
/*******************************************************************************
                                INCLUDED FILES                                 *
 *******************************************************************************/
#include <avr/io.h>

#include "lm35_sensor.h"
#include "adc.h"
#include "gpio.h"
#include "pwm.h"
#include "dc_motor.h"
#include "lcd.h"
/**********************************************************************************
 *                              MAIN FUNCTION                                     *
 **********************************************************************************/
void main(void)
{
	uint8 g_temp;/*global variable to monitor the current temperature*/
	LCD_init();/*initialize the LCD driver*/
	DcMotor_Init();/*initialize the DC motor driver*/
	Adc_ConfigType ADC_configuartion={PRESCALER_8,INTERNAL};/*select the ADC desired configuration*/
	ADC_init(&ADC_configuartion);/*initializing the ADC driver according to the config-type created structure*/
	/* Display this string "  Fan is off" only once on LCD at the first row */
	LCD_displayString("  Fan is off");/*start edit from 10th place*/
	LCD_moveCursor(1,0);
	/* Display this string "Temp =   C" only once on LCD at the first row */
	LCD_displayString("  temp=     C");/*start edit from 8th place*/
	while(1)
	{
		g_temp= LM35_getTemperature();/*taking the current temperature from the LM35 and saving it into g_temp*/
		LCD_moveCursor(1,8);/*change the cursor place on LCD screen*/
			/*this if else condition will adjust the DC motor state according
			 * to the current temperature saved in g_temp
			 * and display the state and the temperature on screen*/
		if(g_temp<=30)
		{
			DcMotor_Rotate(STOP,ZERO_PERCENT);
			LCD_moveCursor(0,9);
			LCD_displayString("off");/*start edit from 10th place*/
			LCD_moveCursor(1,8);
			LCD_intgerToString(g_temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		else if(g_temp>30 && g_temp<=60)
		{
			DcMotor_Rotate(CLOCKWISE,_25_PERCENT);
			LCD_moveCursor(0,9);
			LCD_displayString(" on ");/*start edit from 10th place*/
			LCD_moveCursor(1,8);
			LCD_intgerToString(g_temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		else if(g_temp>60 && g_temp<=90)
		{
			DcMotor_Rotate(ANTI_CLOCKWISE,_50_PERCENT);
			LCD_moveCursor(0,9);
			LCD_displayString(" on ");/*start edit from 10th place*/
			LCD_moveCursor(1,8);
			LCD_intgerToString(g_temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		else if (g_temp>90 && g_temp<=100)
		{
			DcMotor_Rotate(CLOCKWISE,_75_PERCENT);
			LCD_moveCursor(0,9);
			LCD_displayString(" on ");/*start edit from 10th place*/
			LCD_moveCursor(1,8);
			LCD_intgerToString(g_temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
		else if( g_temp>100 && g_temp <= 120)
		{
			DcMotor_Rotate(CLOCKWISE,_75_PERCENT);
			LCD_moveCursor(0,9);
			LCD_displayString(" on ");/*start edit from 10th place*/
			LCD_moveCursor(1,8);
			LCD_intgerToString(g_temp);
			LCD_displayCharacter(' ');
		}
		else if( g_temp > 120)
		{
			DcMotor_Rotate(ANTI_CLOCKWISE,_100_PERCENT);
			LCD_moveCursor(0,9);
			LCD_displayString(" on ");/*start edit from 10th place*/
			LCD_moveCursor(1,8);
			LCD_intgerToString(g_temp);
			LCD_displayCharacter(' ');
		}
	}
}
