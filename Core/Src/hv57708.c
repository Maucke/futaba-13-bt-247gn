#include "hv57708.h"
#include "gpio.h"

static void delay()
{
	int i = 0;
	for (i = 0; i < 256; i++)
		;
}

// maximum data bit 20
void hv57708_dataout(unsigned char *data)
{
	unsigned char i, j;
	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 2; i++)
		{
			HAL_GPIO_WritePin(HV_CLK_GPIO_Port, HV_CLK_Pin, GPIO_PIN_RESET);
			if (((*data >> (i * 4 + 0)) & 0x01))
				HAL_GPIO_WritePin(HV_DIN1_GPIO_Port, HV_DIN1_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(HV_DIN1_GPIO_Port, HV_DIN1_Pin, GPIO_PIN_RESET);
			if (((*data >> (i * 4 + 1)) & 0x01))
				HAL_GPIO_WritePin(HV_DIN2_GPIO_Port, HV_DIN2_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(HV_DIN2_GPIO_Port, HV_DIN2_Pin, GPIO_PIN_RESET);
			if (((*data >> (i * 4 + 2)) & 0x01))
				HAL_GPIO_WritePin(HV_DIN3_GPIO_Port, HV_DIN3_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(HV_DIN3_GPIO_Port, HV_DIN3_Pin, GPIO_PIN_RESET);
			if (((*data >> (i * 4 + 3)) & 0x01))
				HAL_GPIO_WritePin(HV_DIN4_GPIO_Port, HV_DIN4_Pin, GPIO_PIN_SET);
			else
				HAL_GPIO_WritePin(HV_DIN4_GPIO_Port, HV_DIN4_Pin, GPIO_PIN_RESET);

			delay();
			HAL_GPIO_WritePin(HV_CLK_GPIO_Port, HV_CLK_Pin, GPIO_PIN_SET);
			delay();
		}
		data++;
	}
}

void hv57708_updata()
{
	HAL_GPIO_WritePin(HV_LE_GPIO_Port, HV_LE_Pin, GPIO_PIN_RESET);
	delay();
	HAL_GPIO_WritePin(HV_LE_GPIO_Port, HV_LE_Pin, GPIO_PIN_SET);
	delay();
	HAL_GPIO_WritePin(HV_LE_GPIO_Port, HV_LE_Pin, GPIO_PIN_RESET);
}
