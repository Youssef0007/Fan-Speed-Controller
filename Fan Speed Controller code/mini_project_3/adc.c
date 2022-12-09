
 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the AVR ADC driver
 *
 * Date Creation : Oct 9, 2021
 *
 * Author: Youssef Abdel Aziz
 *
 *******************************************************************************/

#include "common_macros.h"
#include "avr/io.h"
#include "adc.h"
/*******************************************************************************
 *                         Global Variables                                    *
 *******************************************************************************/

 float32 g_voltage_source;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function Name:ADC_init
 * Description:initialize the ADC driver according to the selected configuration
 * Arguments:address of the config-type structure received in a pointer to structure
 */
void ADC_init(const Adc_ConfigType * a_Config_Ptr)
{	/*switch case on the type of voltage source
 	 *then put the voltage value inside a global variable voltage_source*/
	switch (a_Config_Ptr->source)
	{
	case AREF:
		g_voltage_source=AREF_SELECTED;
		break;
	case AVCC:
		g_voltage_source=5;
		break;
	case INTERNAL:
		g_voltage_source=2.56;
		break;
	default:
		g_voltage_source=5;
	}
	ADMUX=(ADMUX & 0x3F)|((a_Config_Ptr->source)<<6);/*choose the voltage source*/
	SET_BIT(ADCSRA,ADEN);/*ENBLE ADC*/
	CLEAR_BIT(ADCSRA,ADIE);/*DISABLE INTERRUPT*/
	/*CONFIGURE THE PRESCALER*/
	ADCSRA=(ADCSRA & 0xF8)|(a_Config_Ptr->prescaler);/* pre-scaler configuration*/
	}
/*
 * Function Name:ADC_readChannel
 * Description:choose the adc channel among the 8 channels
 * start the conversion of data then pooling until the ADIF flag is set
 * then the function clear the flag and read the data
 * Arguments:the ADC used channel number
 * return:the read data in the ADC register
 */

uint16 ADC_readChannel(uint8 a_ch_num)
{
	ADMUX=(ADMUX & 0XE0)|(a_ch_num & 0x07);/*insert channel in ADMUX*/
	SET_BIT(ADCSRA,ADSC);/*START CONVERSION*/
	/*POLLING IN WHILE LOOP TO CHECK FOR ADIF FLAG*/
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);/*CLEAR FLAG BY SETTING ADIF */
	return ADC;/*READ DATA*/
}
