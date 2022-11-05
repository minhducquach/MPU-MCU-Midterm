/*
 * display.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Minh Duc Quach
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "global.h"

#define NO_OF_7SEGS	1
#define TIMER_7SEG	10

//extern int index7SEG;

//void clearLEDs();
void clear7SEGs();
void clearEN();

void openEN();

//void blinkLEDs(int);

//void setLEDs(int);
void display7SEG(int);

//void choose7SEG(int);

int bufferValue();
void updateBuffer(int);
void resetBuffer();
void increaseBuffer(int);
void decreaseBuffer(int);

//void control7SEG();
#endif /* INC_DISPLAY_H_ */
