/***********************************************************************************************************************
 *
 *                                                  I N C L U D E S
 *
 **********************************************************************************************************************/
/* Main Module Header */

/* Standard Includes */

/* External Includes */
#include "LED_AO.h"
#include "stm32f3xx.h"

/* Private Module Includes */
// #include "{__name__}_private.h"        // either this
// #include "sl_unit_test_facilitator.h"  // or this

/***********************************************************************************************************************
 *
 *                                                   D E F I N E S
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *                                                  T Y P E D E F S
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *                             P R I V A T E   F U N C T I O N   D E C L A R A T I O N S
 *
 **********************************************************************************************************************/
static void LEDAO_ctor(LED_AO * const me);
static void LEDAO_init(LED_AO * const me, SST_Evt const * const ie);
static void LEDAO_dispatch(LED_AO * const me, SST_Evt const * const e);
/***********************************************************************************************************************
 *
 *                                  P R I V A T E   D A T A   D E F I N I T I O N S
 *
 **********************************************************************************************************************/
static SST_Evt const *LED_AOq[10];
static LED_AO LED_AO_instance;
/***********************************************************************************************************************
 *
 *                                         P R I V A T E   F U N C T I O N S
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *                                          P U B L I C   F U N C T I O N S
 *
 **********************************************************************************************************************/

void LEDAO_Initialize(void);

void BSP_d6on(void)  { GPIOA->BSRR = (1U << 5);         } /* LED2 */
void BSP_d6off(void) { GPIOA->BSRR = (1U << (5 + 16U)); }

SST_Task * const ptrLED_AO = &LED_AO_instance.super;

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
