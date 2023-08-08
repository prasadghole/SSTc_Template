/*
 * LED_AO.h
 *
 *  Created on: Aug 8, 2023
 *      Author: pghole
 */

#ifndef INCLUDES_LED_AO_H_
#define INCLUDES_LED_AO_H_

#include "sst.h"

enum Signals {
	LED_ON, LED_OFF, MAX_SIG
};

typedef struct {
	SST_Evt super; /*< inherit from SST_evt */
	uint32_t pin; /*< Pin number  */
} LED_Evt;

typedef struct {
SST_Task super;
}LED_AO;


extern SST_Task * const ptrLED_AO;
extern void LEDAO_Initialize(void);

#endif /* INCLUDES_LED_AO_H_ */
