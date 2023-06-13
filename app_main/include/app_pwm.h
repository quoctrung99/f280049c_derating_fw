#ifndef _APP_PWM_H_
#define _APP_PWM_H_

#include "driverlib.h"
#include "app_common.h"

#define EPWMCLK         100  // ~100MHz
#define NUM_PWM         2

typedef enum {
    APP_DERATING_PWM_BUCK = 0,
    APP_DERATING_PWM_BOOST,
    APP_DERATING_PWM_MAX
} app_derating_id_pwm_t;

typedef struct {
    uint32_t                            pwm_base;
    uint32_t                            pwm_mux_gpio;
    uint16_t                            pwm_gpio;
    uint16_t                            pwm_freq_khz;
    EPWM_ClockDivider                   pwm_clk_div;
    EPWM_HSClockDivider                 pwm_hsclk_div;
    EPWM_TimeBaseCountMode              pwm_cnt_mode;
    EPWM_CounterCompareModule           pwm_compare;
    EPWM_ActionQualifierOutputModule    pwm_output_mode;
} app_derating_pwm_cfg_t;

#define APP_PWM_DERATING_CFG() {                     \
    {                                                \
        .pwm_base = EPWM8_BASE,                      \
        .pwm_gpio = 15,                              \
        .pwm_mux_gpio = GPIO_15_EPWM8B,              \
        .pwm_freq_khz = 25,                          \
        .pwm_clk_div = EPWM_CLOCK_DIVIDER_1,         \
        .pwm_hsclk_div = EPWM_HSCLOCK_DIVIDER_2,     \
        .pwm_cnt_mode = EPWM_COUNTER_MODE_UP_DOWN,   \
        .pwm_compare = EPWM_COUNTER_COMPARE_A,       \
        .pwm_output_mode = EPWM_AQ_OUTPUT_B,         \
    },                                               \
                                                     \
    {                                                \
        .pwm_base = EPWM8_BASE,                      \
        .pwm_gpio = 14,                              \
        .pwm_mux_gpio = GPIO_14_EPWM8A,              \
        .pwm_freq_khz = 25,                          \
        .pwm_clk_div = EPWM_CLOCK_DIVIDER_1,         \
        .pwm_hsclk_div = EPWM_HSCLOCK_DIVIDER_2,     \
        .pwm_cnt_mode = EPWM_COUNTER_MODE_UP_DOWN,   \
        .pwm_compare = EPWM_COUNTER_COMPARE_B,       \
        .pwm_output_mode = EPWM_AQ_OUTPUT_A,         \
    }                                                \
}

void app_derating_pwm_init();
ti_err_t app_derating_pwm_set_duty(uint16_t duty_percent, app_derating_id_pwm_t id_pwm);

#endif
