#ifndef INC_CONSOLE_H_
#define INC_CONSOLE_H_

#include "main.h"
#include "bsp_uart.h"
#include "stdarg.h"
#include "stdbool.h"

struct console_t
{
    struct uart_t *uart_driver;
    uint8_t cmd_line[100];
    uint8_t *cmd_line_args[10];
    uint8_t max_Tx_timeout;
};

void console_init(struct console_t *console, struct uart_t *uart);
bool console_processing(struct console_t *console);
void console_start(struct console_t *console);

bool console_send_mes(struct console_t *terminal, uint8_t *mes, ...);
void console_whoareyou(struct console_t *console);
void console_led(struct console_t *terminal);

#endif /* INC_APP_H_ */