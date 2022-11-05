/*
 * software_timer.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Minh Duc Quach
 */

#include "software_timer.h"

//flag is on after a specific duration
int timerFlag[NO_OF_COUNTERS] = {0};

//counter to determine if flag is on or not
int counter[NO_OF_COUNTERS] = {0};

//set counter and reset flag
void setTimer(int duration){
	for (int i = 0; i < NO_OF_COUNTERS; i++){
		counter[i] = duration / TICK;
		timerFlag[i] = 0;
	}
}

//decrement counter and check if flag is on or not
void timerRun(){
	for (int i = 0; i < NO_OF_COUNTERS; i++){
		if (counter[i] > 0){
			counter[i]--;
			if (counter[i] <= 0){
				timerFlag[i] = 1;
			}
		}
	}
}

int cnt = 100;	//counter for DEBUG_LED

//timer callback
void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		timerRun();
		button_reading();
		cnt--;
		//toggle DEBUG_LED
		if (cnt <= 0){
			cnt = 100;
			HAL_GPIO_TogglePin(GPIOA, DEBUG_LED_Pin);
		}
	}
}
