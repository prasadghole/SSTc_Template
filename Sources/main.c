/***********************************************************************************************************************
 *
 *                                                  I N C L U D E S
 *
 **********************************************************************************************************************/
/* Main Module Header */

/* Standard Includes */

#include <stdint.h>
/* External Includes */
#include "SST.h"
#include "LED_AO.h"
#include "gpio.h"
#include "stm32f3xx.h"

/* Private Module Includes */
// #include "{__name__}_private.h"        // either this
// #include "sl_unit_test_facilitator.h"  // or this

/***********************************************************************************************************************
 *
 *                                                   D E F I N E S
 *
 **********************************************************************************************************************/

#define BSP_TICKS_PER_SEC 1000U
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

/***********************************************************************************************************************
 *
 *                                  P R I V A T E   D A T A   D E F I N I T I O N S
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *                                         P R I V A T E   F U N C T I O N S
 *
 **********************************************************************************************************************/
static void System_Init(void);
/***********************************************************************************************************************
 *
 *                                          P U B L I C   F U N C T I O N S
 *
 **********************************************************************************************************************/


/**
 * @fn int main(void)
 * @brief
 *
 * @pre
 * @post
 * @return
 */
int main(void)
{
  SST_init();
  System_Init();

  LEDAO_Initialize();
  LEDAO_Start();

  return SST_Task_run();
}

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
void DBC_fault_handler(char const *const module, int const label)
{
}
/**
 * @fn void SST_onStart(void)
 * @brief
 *
 * @pre
 * @post
 */
void SST_onStart(void)
{
  SystemCoreClockUpdate();

  /* set up the SysTick timer to fire at BSP_TICKS_PER_SEC rate */
  SysTick_Config((SystemCoreClock / BSP_TICKS_PER_SEC) + 1U);

  /* set priorities of ISRs used in the system */
  NVIC_SetPriority(SysTick_IRQn, 0U);
  /* ... */
}
/**
 * @fn void SST_onIdle(void)
 * @brief
 *
 * @pre
 * @post
 */
void SST_onIdle(void)
{
#ifdef NDEBUG
   __WFI(); /* Wait-For-Interrupt */
#endif
}

/**
 * @fn void System_Init(void)
 * @brief
 *
 * @pre
 * @post
 */
static void System_Init(void)
{

  /* Configure the MPU to prevent NULL-pointer dereferencing
   * see: www.state-machine.com/null-pointer-protection-with-arm-cortex-m-mpu
   */
  MPU->RBAR = 0x0U /* base address (NULL) */
  | MPU_RBAR_VALID_Msk /* valid region */
  | (MPU_RBAR_REGION_Msk & 7U); /* region #7 */
  MPU->RASR = (7U << MPU_RASR_SIZE_Pos) /* 2^(7+1) region */
  | (0x0U << MPU_RASR_AP_Pos) /* no-access region */
  | MPU_RASR_ENABLE_Msk; /* region enable */

  MPU->CTRL = MPU_CTRL_PRIVDEFENA_Msk /* enable background region */
  | MPU_CTRL_ENABLE_Msk; /* enable the MPU */
  __ISB();
  __DSB();

  /* repurpose regular IRQs for SST Tasks */
  SST_Task_setIRQ(ptrLED_AO, PVD_IRQn);

  MX_GPIO_Init();

}

