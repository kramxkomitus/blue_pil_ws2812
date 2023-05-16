#ifndef INC_BSP_UART_H_
#define INC_BSP_UART_H_

#include "main.h"
#include "stdbool.h"
#include "inttypes.h"
#include "string.h"
#include "usart.h"

#define max_Tx_buf 100
#define max_Rx_buf 100

struct uart_t
{
  UART_HandleTypeDef *HW_interface;
  uint8_t *Rx_buff;
  uint8_t stop_byte;
  enum
  {
    UART_LINE_STATE_WAIT,
    UART_LINE_STATE_READY,
    UART_LINE_STATE_ACTIVE
  } Rx_state,
      Tx_state;
  uint8_t Rx_buff_sz;
};

enum UART_ERROR
{
  ER_RX_BUF_OVERFLOW,
  ER_ACCESS,
  ER_TX_BUF_SZ,
  ER_RX_BUF_SZ,
  ER_TX_HAL
};

void uart_init(struct uart_t *uart, UART_HandleTypeDef *uart_handler, uint8_t UART_stop_byte);

bool uart_send_mes_IT(struct uart_t *uart, uint8_t *message);

bool uart_ask_str_IT(struct uart_t *uart, uint8_t *Rx_return_ptr);

void uart_error(enum UART_ERROR error);

#endif /* INC_BSP_APP_H_ */