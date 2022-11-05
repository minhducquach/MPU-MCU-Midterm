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
//int timeOutDoublePressed[NO_OF_BUTTONS];

int buttonFlag[NO_OF_BUTTONS];
int buttonFlag3s[NO_OF_BUTTONS];
//int buttonFlagDoublePressed[NO_OF_BUTTONS];

int counterDoublePressed[NO_OF_BUTTONS] = {0, 0, 0};
//int flagDoublePressed[NO_OF_BUTTONS] = {0, 0, 0};

int flagLongPressed[NO_OF_BUTTONS] = {0, 0, 0};

GPIO_TypeDef* port[NO_OF_BUTTONS] = {RESET_GPIO_Port, INC_GPIO_Port, DEC_GPIO_Port};
uint16_t pin[NO_OF_BUTTONS] = {RESET_Pin, INC_Pin, DEC_Pin};

void button_reading(){
	for(int i = 0; i < NO_OF_BUTTONS; i ++){
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(port[i], pin[i]);
		if(debounceButtonBuffer3[i] == debounceButtonBuffer2[i] && debounceButtonBuffer2[i] == debounceButtonBuffer1[i]){
			if (buttonBuffer[i] != debounceButtonBuffer1[i]){
				buttonBuffer[i] = debounceButtonBuffer1[i];
				if (buttonBuffer[i] == BUTTON_IS_PRESSED){
//					if (counterDoublePressed[i] > 0 && counterDoublePressed[i] < DOUBLE_PRESSED_TIME && flagDoublePressed[i] == 1){
//						buttonFlagDoublePressed[i] = 1;
//						counterDoublePressed[i] = 0;
//						flagDoublePressed[i] = 0;
//					}
//					else {
//						counterDoublePressed[i] = 0;
//						flagDoublePressed[i] = 1;
//					}
					if (flagLongPressed[i] == 0){
						buttonFlag[i] = 1;
						timeOut[i] = LONG_PRESSED_TIME;
					}
					else timeOut[i] = 100;
				}
				else flagLongPressed[i] = 0;
			}
			else {
				timeOut[i]--;
				if (timeOut[i] <= 0 && debounceButtonBuffer1[i] == BUTTON_IS_PRESSED){
					timeOut[i] = 0;
					buttonFlag3s[i] = 1;
					buttonBuffer[i] = BUTTON_IS_RELEASED;
					flagLongPressed[i] = 1;
				}
				else if (timeOut[i] <= 0) timeOut[i] = 0;
//				if (debounceButtonBuffer1[i] == BUTTON_IS_RELEASED && flagDoublePressed[i] == 1){
//					counterDoublePressed[i]++;
//				}
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

int isButtonPressed3s(int index){
	if(index >= NO_OF_BUTTONS) return 0;
	if (buttonFlag3s[index] == 1){
		buttonFlag3s[index] = 0;
		return 1;
	}
	return 0;
}

//int isButtonDoublePressed(int index){
//	if(index >= NO_OF_BUTTONS) return 0;
//	if (buttonFlagDoublePressed[index] == 1){
//		buttonFlagDoublePressed[index] = 0;
//		return 1;
//	}
//	return 0;
//}
