/**************************************************************************************************
 *                                           Includes
 **************************************************************************************************/
/* Hal Drivers */
#include "hal_types.h"
#include "hal_timer.h"
#include "hal_drivers.h"
#include "hal_led.h"

/* OSAL */
#include "OSAL.h"
#include "OSAL_Tasks.h"
#include "OSAL_PwrMgr.h"
#include "osal_snv.h"
#include "OnBoard.h"

#include "util.h"
#include "log.h"
#include "uart.h"

/**************************************************************************************************
 * FUNCTIONS
 **************************************************************************************************/

/**************************************************************************************************
 * @fn          main
 *
 * @brief       Start of application.
 *
 * @param       none
 *
 * @return      none
 **************************************************************************************************
 */
int main(void)
{
  /* Initialize hardware */
  HAL_BOARD_INIT();

  /* Initialize board I/O */
  InitBoard( OB_COLD );

  /* Initialze the HAL driver */
  HalDriverInit();

  /* Initialize NV system */
  osal_snv_init();

  /* Initialize LL */
  // Empty

  LOG("=-=-=-=-=\r\n");
  UART_Init(NULL);

  /* Initialize the operating system */
  osal_init_system();

  /* Enable interrupts */
  HAL_ENABLE_INTERRUPTS();

  /* Final board initialization */
  InitBoard( OB_READY );
#if 0
  WDCTL = 0X00;
  WDCTL |= 0X08;
#endif
  /*
   * Detect external input during power-on
   * Listen to UART and action accordingly if AT CMD received
   *
   * Yet another solution to make UART work with POWER_SAVING enabled
   */

#if defined ( POWER_SAVING )
  osal_pwrmgr_device( PWRMGR_BATTERY );
#endif

  /* Start OSAL */
  osal_start_system(); // No Return from here

  return 0;
}

/* vim: set ts=2 sw=2 tw=0 list : */
