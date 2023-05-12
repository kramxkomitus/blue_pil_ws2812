#ifndef INC_WS2812_H_
#define INC_WS2812_H_

#include "main.h"
#include "tim.h"
#include "dma.h"
#include "stdbool.h"
#include "stm32f1xx_hal_dma.h"

#define PACKEGE_LEN LEDS * 24

struct led_strp
{
    uint8_t *buf;

    enum
    {
        WAIT,
        ACTIVE
    } state;

    TIM_HandleTypeDef *tim;
    uint32_t tim_chanel;
    DMA_HandleTypeDef *dma;
};

// bool ws2812_set_LED(uint8_t led_No, uint8_t *RGB_arr);
// bool ws2812_set_LED_arr(uint8_t **i_arr, uint8_t start_LED_No, uint8_t amount);
// void ws2812_send();

struct led_strp ws2812_init(
    struct led_strp *led,
    uint8_t *buf,
    uint16_t leds,
    TIM_HandleTypeDef *tim,
    uint32_t tim_chanel,
    DMA_HandleTypeDef *dma);


bool ws2812_set_LED(struct led_strp *S, uint8_t led_No, uint8_t *RGB_arr);

void ws2812_CallBack(DMA_HandleTypeDef *_hdma);

#endif /* INC_WS2812_H_ */
