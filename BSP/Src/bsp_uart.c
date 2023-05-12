#include "bsp_uart.h"

#define max_Tx_buf 100
#define max_Rx_buf 100




uint8_t UART_stop_byte = '\n';
uint8_t Rx_buf_size;
uint8_t *Rx_buff = NULL;

bool uart_send_mes_IT(uint8_t *message)
{
  if (UART_Tx_state == UART_LINE_STATE_ACTIVE)
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
    UART_Tx_state = UART_LINE_STATE_ACTIVE;
    if (HAL_OK == HAL_UART_Transmit_IT(&huart1, message, strlen(message)))
      return true;
    else
    {
      uart_error(ER_TX_HAL);
      return false;
    }
  }
}

bool uart_ask_str_IT(uint8_t *Rx_return_ptr)
{
  if (UART_Rx_state == UART_LINE_STATE_ACTIVE)
  {
    uart_error(ER_ACCESS);
    return false;
  }
  else
  {
    Rx_buf_size = strlen(Rx_return_ptr);
    if (Rx_buf_size > max_Rx_buf)
    {
      uart_error(ER_RX_BUF_SZ);
      return false;
    }
    UART_Rx_state = UART_LINE_STATE_ACTIVE;
    Rx_buff = Rx_return_ptr;
    if (HAL_OK == HAL_UART_Receive_IT(&huart1, Rx_buff, 1))
      return true;
    else
    {
      uart_error(ER_TX_HAL);
      return false;
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

// interaption processing

__weak void uart_str_RxCPLTCallback()
{
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    if (*Rx_buff != UART_stop_byte)
    {
      Rx_buf_size--;
      Rx_buff++;
      if (Rx_buf_size == 0)
      {
        uart_error(ER_RX_BUF_SZ);
      }
      HAL_UART_Receive_IT(&huart1, Rx_buff, 1);
    }
    else
    {
      UART_Rx_state = UART_LINE_STATE_READY;
      uart_str_RxCPLTCallback();
    }
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    if (UART_Tx_state == UART_LINE_STATE_ACTIVE)
      UART_Tx_state = UART_LINE_STATE_READY;
  }
}