/*
 * display.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Minh Duc Quach
 */

#include "display.h"

int led_buffer[4] = {0, 0, 0, 0};

void clearLEDs(){
	HAL_GPIO_WritePin(GPIOA, LED_1_Pin|LED_2_Pin|LED_3_Pin, GPIO_PIN_SET);
}

void clear7SEGs(){
	HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
	                          |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_SET);
}

void clearEN(){
	HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
}

void blinkLEDs(int index){
	switch(index){
	case 0:
		HAL_GPIO_TogglePin(GPIOA, LED_1_Pin);
		break;
	case 1:
		HAL_GPIO_TogglePin(GPIOA, LED_2_Pin);
		break;
	case 2:
		HAL_GPIO_TogglePin(GPIOA, LED_3_Pin);
		break;
	default:
		break;
	}
}

void setLEDs(int index){
	switch(index){
	case 0:
		HAL_GPIO_WritePin(GPIOA, LED_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_3_Pin, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, LED_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, LED_3_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, LED_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_3_Pin, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}

void display7SEG(int counter){
	if (counter == 0){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
			                          |SEG4_Pin|SEG5_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 1){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 2){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG3_Pin
			                          |SEG4_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 3){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
						     	 	  |SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 4){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin|SEG5_Pin
						     	 	  |SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 5){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin
						     	 	  |SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 6){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin
									  |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 7){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 8){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
						              |SEG4_Pin|SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
	else if (counter == 9){
		clear7SEGs();
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin
						              |SEG5_Pin|SEG6_Pin, GPIO_PIN_RESET);
	}
}

void choose7SEG(int index){
	switch ( index ) {
		case 0:
			// Display the first 7 SEG with led_buffer [0]
			HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
			display7SEG(led_buffer[0]);
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, GPIO_PIN_RESET);
			break ;
		case 1:
			// Display the second 7 SEG with led_buffer [1]
			HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN2_Pin|EN3_Pin, GPIO_PIN_SET);
			display7SEG(led_buffer[1]);
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, GPIO_PIN_RESET);
			break ;
		case 2:
			// Display the third 7 SEG with led_buffer [2]
			HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN0_Pin|EN3_Pin, GPIO_PIN_SET);
			display7SEG(led_buffer[2]);
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, GPIO_PIN_RESET);
			break ;
		case 3:
			// Display the forth 7 SEG with led_buffer [3]
			HAL_GPIO_WritePin(GPIOA, EN1_Pin|EN2_Pin|EN0_Pin, GPIO_PIN_SET);
			display7SEG(led_buffer[3]);
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, GPIO_PIN_RESET);
			break ;
		default :
			break ;
	}
}

void updateBuffer(int timer, int mode){
	led_buffer[0] = timer / 10;
	led_buffer[1] = timer % 10;
	led_buffer[2] = mode / 10;
	led_buffer[3] = mode % 10;
}

