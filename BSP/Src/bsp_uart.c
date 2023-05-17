#include "bsp_uart.h"

#define max_Tx_buf 100
#define max_Rx_buf 100
#define max_map_grid_records 10

// initialisation

static struct
{
  UART_HandleTypeDef *hal_uart[max_map_grid_records];
  struct uart_t *bsp_uart[max_map_grid_records];
} uart_map_grid;

void uart_reg_struct(struct uart_t *uart, UART_HandleTypeDef *uart_p)
{
  for (uint8_t i = 0; i < max_map_grid_records; i++)
  {
    if (uart_map_grid.hal_uart[i] == NULL)
    {
      uart_map_grid.hal_uart[i] = uart_p;
      uart_map_grid.bsp_uart[i] = uart;
      return;
    }
  }
}

void uart_init(
    struct uart_t *uart,
    UART_HandleTypeDef *uart_handler,
    uint8_t UART_stop_byte)
{
  uart->HW_interface = uart_handler;
  uart->stop_byte = '\n';
  uart->Rx_state = UART_LINE_STATE_WAIT;
  uart->Tx_state = UART_LINE_STATE_WAIT;
  uart->Rx_buff_sz = 0;
  uart_reg_struct(uart, uart_handler);
}

// Tx line's functions

bool uart_send_mes_IT(struct uart_t *uart, uint8_t *message)
{
  if (uart->Tx_state == UART_LINE_STATE_ACTIVE)
  {
    uart_error(ER_ACCESS);
    return false;
  }
  else
  {
    if (strlen(message) > max_Tx_buf)
    {
      uart_error(ER_TX_BUF_SZ);
      return false;
    }
    uart->Tx_state = UART_LINE_STATE_ACTIVE;
    if (HAL_OK == HAL_UART_Transmit_IT(&huart1, message, strlen(message)))
      return true;
    else
    {
      uart_error(ER_TX_HAL);
      return false;
    }
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  for (uint8_t i = 0; i < max_map_grid_records; i++)
  {
    if (uart_map_grid.hal_uart [i]== huart)
    {
      struct uart_t *uart = uart_map_grid.bsp_uart[i];
      if (uart->Tx_state == UART_LINE_STATE_ACTIVE)
        uart->Tx_state = UART_LINE_STATE_READY;
        return;
    }
  }
}

// Rx line's functions

bool uart_ask_str_IT(struct uart_t *uart, uint8_t *Rx_return_ptr)
{
  if (uart->Rx_state == UART_LINE_STATE_ACTIVE)
  {
    uart_error(ER_ACCESS);
    return false;
  }
  else
  {
    uart->Rx_buff_sz = strlen(Rx_return_ptr);
    if (uart->Rx_buff_sz > max_Rx_buf)
    {
      uart_error(ER_RX_BUF_SZ);
      return false;
    }
    uart->Rx_state = UART_LINE_STATE_ACTIVE;
    uart->Rx_buff = Rx_return_ptr;
    if (HAL_OK == HAL_UART_Receive_IT(&huart1, uart->Rx_buff, 1))
      return true;
    else
    {
      uart_error(ER_TX_HAL);
      return false;
    }
  }
}

// interaption processing

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  for (uint8_t i = 0; i < max_map_grid_records; i++)
  {
    if (uart_map_grid.hal_uart[i] == huart)
    {
      struct uart_t *uart = uart_map_grid.bsp_uart[i];
      if (*uart->Rx_buff != uart->stop_byte)
      {
        uart->Rx_buff_sz--;
        uart->Rx_buff++;
        if (uart->Rx_buff_sz == 0)
        {
          uart_error(ER_RX_BUF_SZ);
        }
        HAL_UART_Receive_IT(&huart1, uart->Rx_buff, 1);
      }
      else
      {
        uart->Rx_state = UART_LINE_STATE_READY;
      }
    }
  }
}

// error processing

void uart_error(enum UART_ERROR error)
{
  switch (error)
  {
    break;
    // case ER_RX_BUF_OVERFLOW:
    //   break;
    // case ER_RX_BUF_OVERFLOW:
    //   Rx_state = WAIT;
    //   break;
    // case ER_ACCESS:
    //   break;
    // case ER_TX_BUF_OWERSIZE:
    //   break;
    // default:
    //   break;
  }
}