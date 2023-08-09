/*
 * Keyboard.c
 *
 *  Created on: Aug 9, 2023
 *      Author: pghole
 */

#include "LED_AO.h"
#include "Keyboard.h"
#include "stm32f3xx.h"

#define B1_PIN 13
/**
 * @brief
 *
 */
void PVD_IRQHandler(void)
{
  SST_Task_activate(ptrLED_AO);
}
/**
 * @brief
 *
 */
void ButtonDebounceHandler(void)
{
  static struct ButtonsDebouncing
  {
    uint32_t depressed;
    uint32_t previous;
  } buttons =
  { 0U, 0U };
  uint32_t current = ~GPIOC->IDR;
  /* read GPIO PortC */uint32_t tmp = buttons.depressed;
  /* save the debounced depressed */buttons.depressed |= (buttons.previous
      & current); /* set depressed */
  buttons.depressed &= (buttons.previous | current); /* clear released */
  buttons.previous = current; /* update the history */
  tmp ^= buttons.depressed; /* changed debounced depressed */
  if ((tmp & (1U << B1_PIN)) != 0U)
  {
    /* debounced B1 state changed? */
    if ((buttons.depressed & (1U << B1_PIN)) != 0U)
    {
      /* depressed? */
      static const LED_Evt pressEvt =
      { .super.sig = LED_ON, .pin = B1_PIN };
      SST_Task_post(ptrLED_AO, &pressEvt.super);
    }
    else
    {
      /* B1 is released */
      static const LED_Evt pressEvt =
      { .super.sig = LED_OFF, .pin = 13 };
      SST_Task_post(ptrLED_AO, &pressEvt.super);
    }
  }
}



