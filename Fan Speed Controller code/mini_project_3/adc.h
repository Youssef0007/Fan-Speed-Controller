/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the AVR ADC driver
 *
 * Date Creation : Oct 9, 2021
 *
 * Author: Youssef Abdel Aziz
 *
 *******************************************************************************/
#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MAX_ADC_VALUE   1023
#define MIN_ADC_VALUE    0
#define AREF_SELECTED    5	/*IF AREF IS SELECTED USER MUST EDIT THIS NUMBER  */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
/* Enum Name:Adc_DivisonFactor
 * description: contain all the pre-scaler values according to the ADC register pins
 * 				from 0 to 8 referring to pre-scaling values from 1 to 128
 */
typedef enum
{
	PRESCALER_1,PRESCALER_2,PRESCALER_4,PRESCALER_8,PRESCALER_16,PRESCALER_32,PRESCALER_64,PRESCALER_128
}Adc_DivisonFactor;


/* Enum Name:Adc_VoltSource
 * description: contain all the values for the Reference selection bits
 * AREF=00
 * AVCC=01
 * RESERVED=10
 * INTERNAL=11
 */
typedef enum
{
	AREF,AVCC,RESERVED,INTERNAL
}Adc_VoltSource;

/* Structure name:Adc_ConfigType
 * description:this structure allow the user to choose the suitable configuration among
 * the ADC different configuration for the selected voltage source and the pre-scaler value
 */
typedef struct
{
	Adc_DivisonFactor prescaler;
	Adc_VoltSource source;
}Adc_ConfigType;
/*******************************************************************************
 *                      Variable Prototypes                                   *
 *******************************************************************************/

extern  float32 g_voltage_source;/*SW global variable so that the LM35 driver can
 	 	 	 	 	 	 	 	 	use it to calculate temp. value  */
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Function Name:ADC_init
 * Description:initialize the ADC driver according to the selected configuration
 * Arguments:address of the config-type structure received in a pointer to structure
 */
void ADC_init(const Adc_ConfigType * a_Config_Ptr);
/*
 * Function Name:ADC_readChannel
 * Description:choose the adc channel among the 8 channels
 * start the conversion of data then pooling until the ADIF flag is set
 * then the function clear the flag and read the data
 * Arguments:the ADC used channel number
 * return:the read data in the ADC register
 */

uint16 ADC_readChannel(uint8 a_ch_num);
#endif /* ADC_H_ */
