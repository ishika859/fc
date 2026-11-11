
#include "main.h"
#include <stdint.h>

extern SPI_HandleTypeDef hspi1;
extern I2C_HandleTypeDef hi2c1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;

#define IMU_CS_PORT GPIOA
#define IMU_CS_PIN  GPIO_PIN_4

#define LED0_PORT GPIOB
#define LED0_PIN  GPIO_PIN_5
#define LED1_PORT GPIOB
#define LED1_PIN  GPIO_PIN_4
#define BUZZER_PORT GPIOC
#define BUZZER_PIN  GPIO_PIN_13

#define M1_PORT GPIOB
#define M1_PIN  GPIO_PIN_0
#define M2_PORT GPIOB
#define M2_PIN  GPIO_PIN_1
#define M3_PORT GPIOA
#define M3_PIN  GPIO_PIN_3
#define M4_PORT GPIOA
#define M4_PIN  GPIO_PIN_2

static volatile uint8_t armed = 0;

static void motors_all_off(void)
{
    HAL_GPIO_WritePin(M1_PORT, M1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(M2_PORT, M2_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(M3_PORT, M3_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(M4_PORT, M4_PIN, GPIO_PIN_RESET);
    armed = 0;
}

static void status_led_task(void)
{
    static uint32_t last_tick = 0;
    if ((HAL_GetTick() - last_tick) >= 500U) {
        last_tick = HAL_GetTick();
        HAL_GPIO_TogglePin(LED0_PORT, LED0_PIN);
    }
}

static uint16_t read_adc_channel(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10U);
    uint16_t value = (uint16_t)HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return value;
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_ADC1_Init();
    MX_I2C1_Init();
    MX_SPI1_Init();
    MX_TIM3_Init();

    HAL_GPIO_WritePin(IMU_CS_PORT, IMU_CS_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
    motors_all_off();

    for (;;) {
        (void)read_adc_channel();
        motors_all_off();
        status_led_task();
        HAL_Delay(2U);
    }
}
