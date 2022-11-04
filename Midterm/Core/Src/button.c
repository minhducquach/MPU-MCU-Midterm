/*
 * button.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Minh Duc Quach
 */

#include "button.h"

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTONS];

int timeOut[NO_OF_BUTTONS];
int timeOutDoublePressed[NO_OF_BUTTONS];

int buttonFlag[NO_OF_BUTTONS];
int buttonFlag1s[NO_OF_BUTTONS];
int buttonFlagDoublePressed[NO_OF_BUTTONS];

int counterDoublePressed[NO_OF_BUTTONS] = {0, 0, 0};

GPIO_TypeDef* port[NO_OF_BUTTONS] = {Button1_GPIO_Port, Button2_GPIO_Port, Button3_GPIO_Port};
uint16_t pin[NO_OF_BUTTONS] = {Button1_Pin, Button2_Pin, Button3_Pin};

void button_reading(){
	for(int i = 0; i < NO_OF_BUTTONS; i ++){
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(port[i], pin[i]);
		if(debounceButtonBuffer3[i] == debounceButtonBuffer2[i] && debounceButtonBuffer2[i] == debounceButtonBuffer1[i]){
			if (buttonBuffer[i] != debounceButtonBuffer1[i]){
				buttonBuffer[i] = debounceButtonBuffer1[i];
				if (buttonBuffer[i] == BUTTON_IS_PRESSED){
					buttonFlag[i] = 1;
					timeOut[i] = 100;
					timeOutDoublePressed[i] = 10;
					counterDoublePressed[i]++;
				}
			}
			else {
				timeOut[i]--;
				if (timeOut[i] <= 0 && debounceButtonBuffer1[i] == BUTTON_IS_PRESSED){
					buttonFlag1s[i] = 1;
					buttonBuffer[i] = BUTTON_IS_RELEASED;
				}
			}
		}
	}
}

int isButtonPressed(int index){
	if(index >= NO_OF_BUTTONS) return 0;
	if (buttonFlag[index] == 1){
		buttonFlag[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonPressed1s(int index){
	if(index >= NO_OF_BUTTONS) return 0;
	if (buttonFlag1s[index] == 1){
		buttonFlag1s[index] = 0;
		return 1;
	}
	return 0;
}
