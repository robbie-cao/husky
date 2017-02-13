#include "OSAL.h"
#include "hal_uart.h"
#include "uart.h"

static UARTRxCB_t uartRxCB = NULL;

/* Callback for handling stuff */
static void UART_CB(uint8 port, uint8 event)
{
  if (event & (HAL_UART_RX_FULL | HAL_UART_RX_ABOUT_FULL | HAL_UART_RX_TIMEOUT)) {
    // Read into buffer
    uint8  buf[UART_RX_BUF_SIZE];
    uint16 len = Hal_UART_RxBufLen(UART_PORT);
    uint16 rxLen = HalUARTRead(UART_PORT, buf, len);
    if (rxLen > 0) {
      // Parse received string and handle it accordingly
      if (uartRxCB) {
        uartRxCB(buf, rxLen);
      }
    }
  }
}

void UART_Init(UARTRxCB_t cb)
{
  halUARTCfg_t uartConfig;

  uartConfig.configured           = TRUE;
  uartConfig.baudRate             = UART_BR;
  uartConfig.flowControl          = UART_FC;
  uartConfig.flowControlThreshold = UART_FC_THRESHOLD;
  uartConfig.rx.maxBufSize        = UART_RX_BUF_SIZE;
  uartConfig.tx.maxBufSize        = UART_TX_BUF_SIZE;
  uartConfig.idleTimeout          = UART_IDLE_TIMEOUT;
  uartConfig.intEnable            = UART_INT_ENABLE;
  uartConfig.rxChRvdTime          = 0;
  uartConfig.callBackFunc         = (halUARTCBack_t)UART_CB;

  uartRxCB = cb;

  HalUARTOpen(UART_PORT, &uartConfig);
}

/* vim: set ts=2 sw=2 tw=0 list : */
