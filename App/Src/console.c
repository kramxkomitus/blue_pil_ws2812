#include "console.h"

void console_init(struct console_t *terminal, struct uart_t *uart)
{
    terminal->uart_driver = uart;
}

bool console_is_ready(struct console_t *terminal)
{
    if (terminal->uart_driver->Rx_state == UART_LINE_STATE_READY)
    {
        return true;
    }
    else
        return false;
}

void console_start(struct console_t *terminal)
{
    uart_send_mes_IT(terminal->uart_driver, "user@blue_pill:$ ");
    uart_ask_str_IT(terminal->uart_driver, terminal->cmd_line);
}

bool console_send_mes(struct console_t *terminal, uint8_t *mes, ...)
{
    uint8_t i = 0;
    while (terminal->uart_driver->Tx_state == UART_LINE_STATE_ACTIVE)
    {
        i++;
        HAL_Delay(1);
        if (i >= terminal->max_Tx_timeout)
        {
            return false;
        }
    }
    uint8_t buffer[100];
    va_list digit;
    va_start(digit, mes);
    vsprintf(buffer, mes, digit);

    uart_send_mes_IT(terminal->uart_driver, buffer);
    console_start(terminal);
    return true;
}

bool console_processing(struct console_t *terminal)
{
    if (console_is_ready(terminal) == false)
    {
        return false;
    }
    else
    {
        uint8_t *word;
        uint8_t i = 0;

        word = strtok(terminal->cmd_line, " "); // проверить как strtok работает
        while (word != NULL)
        {
            terminal->cmd_line_args[i] = word;
            i++;
            word = strtok(NULL, " ");
        }
        // request_word_arr[i] = NULL;          хз что это, надо вспомнить и подписать

        if (strcmp(terminal->cmd_line_args[0], "whoareyou") == 0)
        {
            console_whoareyou(terminal);
        }
    }
}

void console_whoareyou(struct console_t *terminal)
{
    uart_send_mes_IT(terminal, "drives\n");
    console_start(terminal);
}
