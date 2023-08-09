/*
 * Interrupts.c
 *
 *  Created on: Aug 9, 2023
 *      Author: pghole
 */
#include "sst.h"
#include "keyboard.h"

/**
 * @brief
 *
 */
void SysTick_Handler(void)
{ /* system clock tick ISR */

  SST_TimeEvt_tick(); /* process all SST time events */

  ButtonDebounceHandler();
}
