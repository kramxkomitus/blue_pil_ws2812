#include "ws2812.h"
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

#define bit_is_set(byte, bitNo) ((byte & (1 << bitNo)) != 0) // check is that bit == 1

struct led_strp ws2812_init(
    struct led_strp *led,
    uint8_t *buf,
    uint16_t leds,
    TIM_HandleTypeDef *tim,
    uint32_t tim_chanel,
    DMA_HandleTypeDef *dma)
{
    led->buf = buf;
    led->state = FREE;
    led->tim = tim;
    led->tim_chanel = tim_chanel;
    led->dma = dma;
    HAL_DMA_RegisterCallback(dma, HAL_DMA_XFER_CPLT_CB_ID, ws2812_CallBack);
}

void ws2812_CallBack(DMA_HandleTypeDef *_hdma)
{
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}
bool ws2812_set_LED(uint8_t led_No, uint8_t *RGB_arr)
{
    uint8_t *o_ptr = led_buf + led_No * 24;
    for (uint8_t i = 0; i < 3; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if (bit_is_set(*RGB_arr, j))
                *o_ptr = 2;
            else
                *o_ptr = 1;
            o_ptr++;
        }
        RGB_arr++;
    }
}

// bool ws2812_set_LED_arr(uint8_t **i_arr, uint8_t start_LED_No, uint8_t amount)
// {
//     for (uint8_t i = 0; i < amount; i++)
//     {
//         ws2812_set_LED(start_LED_No + i, *i_arr);
//         i_arr++;
//     }
// }

void ws2812_send(struct led_strp *S)
{
    HAL_TIM_PWM_Start_DMA(&S->tim, S->tim_chanel, S->buf, 8);
}

// void ws2812_complt_receive()
// {
// }
