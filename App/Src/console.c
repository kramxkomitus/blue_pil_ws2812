#include "console.h"

uint8_t request_str[100];
uint8_t *request_word_arr[10];

// bool console_is_ready()
// {
//     if (UART_Rx_state == READY)
//         return true;
//     else
//         return false;
// }

void console_start()
{
    uart_send_mes_IT("user@blue_pill:$ ");
    uart_ask_str_IT(request_str);
}

bool console_processing()
{
    // if (console_is_ready() == false)
    if (false)
    {
        return false;
    }
    else
    {
        uint8_t *word;
        uint8_t i = 0;

        word = strtok(request_str, " "); // проверить как strtok работает
        while (word != NULL)
        {
            request_word_arr[i] = word;
            i++;
            word = strtok(NULL, " ");
        }
        request_word_arr[i] = NULL;

        if (strcmp(request_word_arr[0], "whoareyou") == 0)
        {
            console_whoareyou();
        }
    }
}

void console_whoareyou()
{
    uart_send_mes_IT("drives\n");
    console_start();
}