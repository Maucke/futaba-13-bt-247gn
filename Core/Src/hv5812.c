#include "hv5812.h"
#include "gpio.h"

static void delay()
{
	int i = 0;
	for (i = 0; i < 2048; i++)
		;
}

// maximum data bit 20
void hv5812_dataout(unsigned char *data)
{
	unsigned char i, temp;
	for (i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(HV2_CLK_GPIO_Port, HV2_CLK_Pin, GPIO_PIN_RESET);
		if (((*data >> i) & 0x01))
			HAL_GPIO_WritePin(HV2_DIN_GPIO_Port, HV2_DIN_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(HV2_DIN_GPIO_Port, HV2_DIN_Pin, GPIO_PIN_RESET);
		delay();
		HAL_GPIO_WritePin(HV2_CLK_GPIO_Port, HV2_CLK_Pin, GPIO_PIN_SET);
		delay();
		HAL_GPIO_WritePin(HV2_DIN_GPIO_Port, HV2_DIN_Pin, GPIO_PIN_RESET);
		delay();
	}
	data++;
	for (i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(HV2_CLK_GPIO_Port, HV2_CLK_Pin, GPIO_PIN_RESET);
		if (((*data >> i) & 0x01))
			HAL_GPIO_WritePin(HV2_DIN_GPIO_Port, HV2_DIN_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(HV2_DIN_GPIO_Port, HV2_DIN_Pin, GPIO_PIN_RESET);
		delay();
		HAL_GPIO_WritePin(HV2_CLK_GPIO_Port, HV2_CLK_Pin, GPIO_PIN_SET);
		delay();
		HAL_GPIO_WritePin(HV2_DIN_GPIO_Port, HV2_DIN_Pin, GPIO_PIN_RESET);
		delay();
	}
	data++;
	for (i = 0; i < 2; i++)
	{
		HAL_GPIO_WritePin(HV2_CLK_GPIO_Port, HV2_CLK_Pin, GPIO_PIN_RESET);
		if (((*data >> i) & 0x01))
			HAL_GPIO_WritePin(HV2_DIN_GPIO_Port, HV2_DIN_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(HV2_DIN_GPIO_Port, HV2_DIN_Pin, GPIO_PIN_RESET);
		delay();
		HAL_GPIO_WritePin(HV2_CLK_GPIO_Port, HV2_CLK_Pin, GPIO_PIN_SET);
		delay();
		HAL_GPIO_WritePin(HV2_DIN_GPIO_Port, HV2_DIN_Pin, GPIO_PIN_RESET);
		delay();
	}
	HAL_GPIO_WritePin(HV2_BLANK_GPIO_Port, HV2_BLANK_Pin, GPIO_PIN_SET);
	delay();
	HAL_GPIO_WritePin(HV2_LOAD_GPIO_Port, HV2_LOAD_Pin, GPIO_PIN_SET);
	delay();
	HAL_GPIO_WritePin(HV2_LOAD_GPIO_Port, HV2_LOAD_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HV2_BLANK_GPIO_Port, HV2_BLANK_Pin, GPIO_PIN_RESET);
	HAL_Delay(2);
}
