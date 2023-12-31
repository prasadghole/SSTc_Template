/***********************************************************************************************************************
 *
 *                                                  I N C L U D E S
 *
 **********************************************************************************************************************/
/* Main Module Header */

/* Standard Includes */

/* External Includes */
#include "sst.h"
#include "keyboard.h"

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

/***********************************************************************************************************************
 *
 *                                          P U B L I C   F U N C T I O N S
 *
 **********************************************************************************************************************/


/**
 * @brief
 *
 */
void SysTick_Handler(void)
{ /* system clock tick ISR */

  SST_TimeEvt_tick(); /* process all SST time events */

  ButtonDebounceHandler();
}
