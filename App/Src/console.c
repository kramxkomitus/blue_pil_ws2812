#include "console.h"

#define whitespaces " \n\t\r"

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
    uart_send_mes_IT(terminal->uart_driver, "\nuser@blue_pill:$ ");
    memset(terminal->cmd_line, 0, sizeof(terminal->cmd_line));
    memset(terminal->cmd_line_args, 0, sizeof(terminal->cmd_line_args));
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
        uint8_t *word; // искать проблему здесь
        uint8_t i = 0;

        word = strtok(terminal->cmd_line, whitespaces); // проверить как strtok работает
        while (word != NULL)
        {
            terminal->cmd_line_args[i] = word;
            i++;
            word = strtok(NULL, whitespaces);
        }
        // request_word_arr[i] = NULL;          хз что это, надо вспомнить и подписать

        if (strcmp(terminal->cmd_line_args[0], "whoareyou") == 0)
        {
            console_whoareyou(terminal);
        }

        else if (strcmp(terminal->cmd_line_args[0], "led") == 0)
        {
            console_led(terminal);
        }
        console_start(terminal);
    }
}

void console_whoareyou(struct console_t *terminal)
{
    console_send_mes(terminal, "blue_pill");
}

void console_led(struct console_t *terminal)
{
    uint8_t *led_state = terminal->cmd_line_args[1];
    if (strcmp(led_state, "on") == 0)
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
    else if (strcmp(led_state, "off") == 0)
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, RESET);
    else
        console_send_mes(terminal, "wrong args\n");
}
