/*
 * LED_Ao.c
 *
 *  Created on: Aug 8, 2023
 *      Author: pghole
 */


#include "LED_AO.h"

void LEDAO_Initialize(void);
static void LEDAO_ctor(LED_AO * const me);
static void LEDAO_init(LED_AO * const me, SST_Evt const * const ie);
static void LEDAO_dispatch(LED_AO * const me, SST_Evt const * const e);


static LED_AO LED_AO_instance;
SST_Task * const ptrLED_AO = &LED_AO_instance.super;

/* Construct task */
static void LEDAO_ctor(LED_AO * const me)
{
    SST_Task_ctor(&me->super,
    (SST_Handler)&LEDAO_init,
    (SST_Handler)&LEDAO_dispatch);
}

static void LEDAO_init(LED_AO * const me, SST_Evt const * const ie)
{}
static void LEDAO_dispatch(LED_AO *const me, SST_Evt const *const e) {
	switch (e->sig) {
	case LED_ON:
		break;
	case LED_OFF:
		break;
	}
}


void LEDAO_Initialize(void)
{
	LEDAO_ctor(&LED_AO_instance);
}
