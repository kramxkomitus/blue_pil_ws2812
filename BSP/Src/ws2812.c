#include "ws2812.h"
#include "string.h"

// WS2812B
//  ___________
// _| 0.4 mks |_______0.85mks_ --> 0 code
//  __________________
// _|    0.85 mks    |_0.4mks_ --> 1 code
// RESET - >50mks.
// Counter period = 3, 1 tic = 400ns --> 2.5 Mhz
// my timer - 72Mhz, Prescaler = 29 - 1.
// RESET = 125 tic

#define TX_ARR_SIZE LEDS

#define BIT_IS_SET(byte, bitNo) ((byte & (1 << bitNo)) != 0) // check is that bit == 1

void ws2812_init(
    struct led_strp_t *led,
    uint8_t *buf,
    uint16_t leds,
    TIM_HandleTypeDef *tim,
    uint32_t tim_chanel,
    DMA_HandleTypeDef *dma)
{
    led->buf = buf;
    led->state = WAIT;
    led->tim = tim;
    led->tim_chanel = tim_chanel;
    led->dma = dma;
    led->leds = leds;
    HAL_DMA_RegisterCallback(dma, HAL_DMA_XFER_CPLT_CB_ID, ws2812_CallBack);
    memset(led->buf, 0, led->leds * 24);
}

void ws2812_CallBack(DMA_HandleTypeDef *_hdma)
{
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

bool ws2812_set_LED(struct led_strp_t *S, uint8_t led_No, uint8_t *RGB_arr)
// функция получает указатель на структуру ленты, номер диода, и указатель на
// массив из 3х элементов

{
    // uint8_t A = RGB[0];
    if (S->leds > led_No)
    {
        uint8_t *led_ptr = S->buf + led_No * 24;
        for (uint8_t i = 0; i < 3; i++)
        {
            for (int8_t j = 7; j >= 0; j--)
            {
                if (BIT_IS_SET(*RGB_arr, j))
                    *led_ptr = 2;
                else
                    *led_ptr = 1;
                led_ptr++;
            }
            RGB_arr++;
        }
        return true;
    }
    else
        return false;
}

// bool ws2812_set_LED_arr(uint8_t **i_arr, uint8_t start_LED_No, uint8_t amount)
// {
//     for (uint8_t i = 0; i < amount; i++)
//     {
//         ws2812_set_LED(start_LED_No + i, *i_arr);
//         i_arr++;
//     }
// }

void ws2812_send(struct led_strp_t *S)
{
    HAL_TIM_PWM_Start_DMA(&S->tim, S->tim_chanel, S->buf, 8);
}

// void ws2812_complt_receive()
// {
// }
