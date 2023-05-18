#ifndef INC_WS2812_H_
#define INC_WS2812_H_

#include "main.h"
#include "tim.h"
#include "dma.h"
#include "stdbool.h"
#include "stm32f1xx_hal_dma.h"

#define PACKEGE_LEN LEDS * 24

struct led_strp_t
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

void ws2812_init(
    struct led_strp_t *led,
    uint8_t *buf,
    uint16_t leds,
    TIM_HandleTypeDef *tim,
    uint32_t tim_chanel,
    DMA_HandleTypeDef *dma);

bool ws2812_set_LED(struct led_strp_t *S, uint8_t led_No, uint8_t *RGB_arr);

void ws2812_CallBack(DMA_HandleTypeDef *_hdma);
// void ws2812_CallBack(DMA_HandleTypeDef *hdma);


#define WS2812_INIT(struct_name, tim, tim_chanel, dma, leds) \
    struct led_strp_t struct_name;                           \
    uint8_t buf_##struct_name[24 * (leds)];                  \
    ws2812_init(&struct_name, buf_##struct_name, leds, tim, tim_chanel, dma)


#endif /* INC_WS2812_H_ */
