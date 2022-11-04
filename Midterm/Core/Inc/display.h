/*
 * display.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Minh Duc Quach
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "global.h"

void clearLEDs();
void clear7SEGs();
void clearEN();

void blinkLEDs(int);

void setLEDs(int);
void display7SEG(int);

void choose7SEG(int);

void updateBuffer(int, int);
#endif /* INC_DISPLAY_H_ */
