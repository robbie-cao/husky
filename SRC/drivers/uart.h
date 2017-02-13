#ifndef __UART_H__
#define __UART_H__

/* UART config */
#define UART_RX_BUF_SIZE            128     // Make sure this size <= HAL_UART_DMA_RX_MAX
#define UART_TX_BUF_SIZE            128     // Make sure this size <= HAL_UART_DMA_TX_MAX

#define UART_FC                     FALSE
#define UART_FC_THRESHOLD           0
#define UART_INT_ENABLE             FALSE

#define UART_IDLE_TIMEOUT           6

#define UART_BR                     HAL_UART_BR_115200
#define UART_PORT                   HAL_UART_PORT_1

#define UART_PIN_TX                 P0_4
#define UART_PIN_RX                 P0_5
#define UART_BIT_TX                 4
#define UART_BIT_RX                 5

typedef void (*UARTRxCB_t)(uint8 * rxBuf, uint16 rxLen);

void UART_Init(UARTRxCB_t cb);

#endif /* __UART_H__ */

/* vim: set ts=2 sw=2 tw=0 list : */
