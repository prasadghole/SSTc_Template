#include "LED_AO.h"
#include "stm32f3xx.h"

void LEDAO_Initialize(void);

static void LEDAO_ctor(LED_AO * const me);
static void LEDAO_init(LED_AO * const me, SST_Evt const * const ie);
static void LEDAO_dispatch(LED_AO * const me, SST_Evt const * const e);

void BSP_d6on(void)  { GPIOA->BSRR = (1U << 5);         } /* LED2 */
void BSP_d6off(void) { GPIOA->BSRR = (1U << (5 + 16U)); }

static LED_AO LED_AO_instance;
SST_Task * const ptrLED_AO = &LED_AO_instance.super;

static SST_Evt const *LED_AOq[10];
/* Construct task */
static void LEDAO_ctor(LED_AO * const me)
{
    SST_Task_ctor(&me->super,
    (SST_Handler)&LEDAO_init,
    (SST_Handler)&LEDAO_dispatch);
}

/**
 * @fn void LEDAO_Initialize(void)
 * @brief
 *
 * @pre
 * @post
 */
static void LEDAO_init(LED_AO * const me, SST_Evt const * const ie)
{

}
/**
 * @fn void LEDAO_dispatch(LED_AO* const, const SST_Evt* const)
 * @brief
 *
 * @pre
 * @post
 * @param me
 * @param e
 */
static void LEDAO_dispatch(LED_AO *const me, SST_Evt const *const e) {
	switch (e->sig) {
	case LED_ON:
	  BSP_d6on();
		break;
	case LED_OFF:
	  BSP_d6off();
		break;
	}
}

/**
 * @fn void LEDAO_Initialize(void)
 * @brief
 *
 * @pre
 * @post
 */
void LEDAO_Initialize(void)
{
	LEDAO_ctor(&LED_AO_instance);
}
/**
 * @fn void LEDAO_Start(void)
 * @brief
 *
 * @pre
 * @post
 */
void LEDAO_Start(void)
{
  SST_Task_start(ptrLED_AO, 1U, LED_AOq, ARRAY_NELEM(LED_AOq),
      (SST_Evt const*) 0);
}
