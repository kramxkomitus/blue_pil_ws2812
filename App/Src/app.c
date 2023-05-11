#include "app.h"

#define LEDS 8
#define PACKAGE_LEN LEDS * 3

static uint8_t led_buf[PACKEGE_LEN] = {};

void app()
{
    uint8_t RGB[3] = {100, 100, 100};
    // struct led_strp led;
    // ws2812_init(&led, led_buf, LEDS, &htim1, TIM_CHANNEL_1, &hdma_tim1_ch1);
    // ws2812_set_LED(1, RGB);
    while (1)
    {
        /* code */
    }
    
}

// // /*uint32_t answer = 0;
// // uint8_t sim = 0;
// // uint8_t console_flag = 0;
// // uint8_t console_buff[100] = {};

// // int main(void)
// // {
// //   /* USER CODE BEGIN 1 */

// //   /* USER CODE END 1 */

// //   /* MCU Configuration--------------------------------------------------------*/

// //   /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
// //   HAL_Init();

// //   /* USER CODE BEGIN Init */

// //   /* USER CODE END Init */

// //   /* Configure the system clock */
// //   SystemClock_Config();

// //   /* USER CODE BEGIN SysInit */

// //   /* USER CODE END SysInit */

// //   /* Initialize all configured peripherals */
// //   MX_GPIO_Init();
// //   MX_DMA_Init();
// //   MX_TIM1_Init();
// //   MX_TIM4_Init();
// //   MX_USART1_UART_Init();
// //   /* USER CODE BEGIN 2 */

// //   /* USER CODE END 2 */

// //   /* Infinite loop */
// //   /* USER CODE BEGIN WHILE */

// //   HAL_TIM_Base_Start_IT(&htim4);
// //   HAL_UART_Receive_IT(&huart1, &sim, 1);

// //   uint8_t test = 0;
// //   HAL_UART_Transmit(&huart1, "start\n", 8, 100);
// //   HAL_Delay(100);
// //   ws2812_clean();
// //   uint8_t color[3] = {};
// //   uint8_t *color_str[3] = {};
// //   while (1)
// //   {
// //     if (console_flag)
// //     {
// //       uint8_t j = 0;
// //       uint8_t flag = 0;
// //       console_flag = 0;
// //       if (strcmp(console_buff, "whoareyou") == 0)
// //       {
// //         HAL_UART_Transmit(&huart1, "devices\n", 8, 100);
// //       }
// //       if (*console_buff == 'l')
// //       {
// //         for (int i = 1; i < strlen(console_buff); i++)
// //         {
// //           if (console_buff[i] != ' ')
// //           {
// //             if (!flag)
// //             {
// //               color_str[j++] = &console_buff[i];
// //               flag = 1;
// //             }
// //           }
// //           else
// //             flag = 0;
// //         }
// //         color[0] = atoi(color_str[0]);
// //         color[1] = atoi(color_str[1]);
// //         color[2] = atoi(color_str[2]);
// //         // printf("dick --> R:%d; G:%d, B:%d.\r\n", color[0], color[1], color[2]);
// //       }
// //     }

// //     for (uint16_t i = 0; i < 22; i++)
// //       ws2812_pixel_set(color[0], color[1], color[2], i);
// //     ws2812_pixel_show();

// //     HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
// //     HAL_Delay(100);

// //     /* USER CODE END WHILE */

// //     /* USER CODE BEGIN 3 */
// //   }
// //   /* USER CODE END 3 */
// // }

// // int _write(int file, char *ptr, int len)
// // {
// //   for (int i = 0; i < len; i++)
// //     HAL_UART_Transmit(&huart1, (uint8_t *)ptr++, 1, 100);
// //   return len;
// // }
// // */