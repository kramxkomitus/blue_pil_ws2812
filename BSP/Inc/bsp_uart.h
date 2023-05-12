#ifndef INC_BSP_UART_H_
#define INC_BSP_UART_H_

#include "main.h"
#include "stdbool.h"
#include "inttypes.h"
#include "string.h"
#include "usart.h"

enum UART_ERROR
{
  ER_RX_BUF_OVERFLOW,
  ER_ACCESS,
  ER_TX_BUF_SZ,
  ER_RX_BUF_SZ,
  ER_TX_HAL
};

// typedef enum
// {
//   WAIT,
//   READY,
//   ACTIVE
// } UART_LINE_STATE;

// enum UART_LINE_STATE
// {
// WAIT,
// READY,
// ACTIVE
// };

// enum UART_LINE_STATE UART_Tx_state = WAIT;
// enum UART_LINE_STATE UART_Rx_state = WAIT;

static enum {
  UART_LINE_STATE_WAIT,
  UART_LINE_STATE_READY,
  UART_LINE_STATE_ACTIVE
} UART_Rx_state = UART_LINE_STATE_WAIT,
  UART_Tx_state = UART_LINE_STATE_WAIT;

// static enum {
//   WAIT,
//   READY,
//   ACTIVE
// } UART_Rx_state = WAIT,
//   UART_Tx_state = WAIT;

bool uart_send_mes_IT(uint8_t *message);
bool uart_ask_str_IT(uint8_t *dst_ptr);
void uart_str_RxCPLTCallback();
void uart_error(enum UART_ERROR error);

#endif /* INC_BSP_APP_H_ */