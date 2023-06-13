#include "app_pwm.h"
#include "app_debug.h"

static app_derating_pwm_cfg_t app_derating_pwm_cfg[] = APP_PWM_DERATING_CFG();

typedef struct {
    uint16_t                    actual_div[2];
    EPWM_ClockDivider           clk_div;
    EPWM_HSClockDivider         hsclk_div;
} app_pwm_clk_div_info_t;

static const app_pwm_clk_div_info_t app_pwm_clk_div_pattern[] = {
    {.clk_div = EPWM_CLOCK_DIVIDER_1,   .hsclk_div = EPWM_HSCLOCK_DIVIDER_1,  .actual_div = {1, 1}},
    {.clk_div = EPWM_CLOCK_DIVIDER_2,   .hsclk_div = EPWM_HSCLOCK_DIVIDER_2,  .actual_div = {2, 2}},
    {.clk_div = EPWM_CLOCK_DIVIDER_4,   .hsclk_div = EPWM_HSCLOCK_DIVIDER_4,  .actual_div = {4, 4}},
    {.clk_div = EPWM_CLOCK_DIVIDER_8,   .hsclk_div = EPWM_HSCLOCK_DIVIDER_6,  .actual_div = {8, 6}},
    {.clk_div = EPWM_CLOCK_DIVIDER_16,  .hsclk_div = EPWM_HSCLOCK_DIVIDER_8,  .actual_div = {16, 8}},
    {.clk_div = EPWM_CLOCK_DIVIDER_32,  .hsclk_div = EPWM_HSCLOCK_DIVIDER_10, .actual_div = {32, 10}},
    {.clk_div = EPWM_CLOCK_DIVIDER_64,  .hsclk_div = EPWM_HSCLOCK_DIVIDER_12, .actual_div = {64, 12}},
    {.clk_div = EPWM_CLOCK_DIVIDER_128, .hsclk_div = EPWM_HSCLOCK_DIVIDER_14, .actual_div = {128, 14}},
};

static uint16_t app_derating_get_clk_div(EPWM_ClockDivider clk_div)
{
    return app_pwm_clk_div_pattern[clk_div].actual_div[0];
}

static uint16_t app_derating_get_hsclk_div(EPWM_HSClockDivider hsclk_div)
{
    return app_pwm_clk_div_pattern[hsclk_div].actual_div[1];
}

void app_derating_pwm_init()
{
    int idx = 0;
    for (idx = 0; idx < NUM_PWM; idx++) {
        GPIO_setPadConfig(app_derating_pwm_cfg[idx].pwm_gpio, GPIO_PIN_TYPE_STD);
        GPIO_setPinConfig(app_derating_pwm_cfg[idx].pwm_mux_gpio);

        uint16_t t_tbclk = 1000 / (EPWMCLK / (app_derating_get_clk_div(app_derating_pwm_cfg[idx].pwm_clk_div) * app_derating_get_hsclk_div(app_derating_pwm_cfg[idx].pwm_hsclk_div)));
        uint32_t t_pwm = 1000000 / app_derating_pwm_cfg[idx].pwm_freq_khz;

        EPWM_setTimeBasePeriod(app_derating_pwm_cfg[idx].pwm_base, (t_pwm) / (2 * t_tbclk));
        EPWM_setPhaseShift(app_derating_pwm_cfg[idx].pwm_base, 0U);
        EPWM_setTimeBaseCounter(app_derating_pwm_cfg[idx].pwm_base, 0U);

        EPWM_setTimeBaseCounterMode(app_derating_pwm_cfg[idx].pwm_base, app_derating_pwm_cfg[idx].pwm_cnt_mode);
        EPWM_disablePhaseShiftLoad(app_derating_pwm_cfg[idx].pwm_base);
        EPWM_setClockPrescaler(app_derating_pwm_cfg[idx].pwm_base, app_derating_pwm_cfg[idx].pwm_clk_div, app_derating_pwm_cfg[idx].pwm_hsclk_div);

        EPWM_setCounterCompareShadowLoadMode(app_derating_pwm_cfg[idx].pwm_base, app_derating_pwm_cfg[idx].pwm_compare, EPWM_COMP_LOAD_ON_CNTR_ZERO);

        EPWM_setActionQualifierAction(app_derating_pwm_cfg[idx].pwm_base,
                                      app_derating_pwm_cfg[idx].pwm_output_mode,
                                      EPWM_AQ_OUTPUT_LOW,
                                      (app_derating_pwm_cfg[idx].pwm_compare == EPWM_COUNTER_COMPARE_A) ? EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO
                                                                                                        : EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

        EPWM_setActionQualifierAction(app_derating_pwm_cfg[idx].pwm_base,
                                      app_derating_pwm_cfg[idx].pwm_output_mode,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      (app_derating_pwm_cfg[idx].pwm_compare == EPWM_COUNTER_COMPARE_A) ? EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA
                                                                                                        : EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
        EPWM_setActionQualifierAction(app_derating_pwm_cfg[idx].pwm_base,
                                      app_derating_pwm_cfg[idx].pwm_output_mode,
                                      EPWM_AQ_OUTPUT_LOW,
                                      (app_derating_pwm_cfg[idx].pwm_compare == EPWM_COUNTER_COMPARE_A) ? EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA
                                                                                                        : EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);
    }
}

ti_err_t app_derating_pwm_set_duty(uint16_t duty_percent, app_derating_id_pwm_t id_pwm)
{
    if (id_pwm  >= NUM_PWM) {
        return TI_FAIL;
    }
    EPWM_setCounterCompareValue(app_derating_pwm_cfg[id_pwm].pwm_base, app_derating_pwm_cfg[id_pwm].pwm_compare,
                                ((10 - (duty_percent / 10)) * EPWM_getTimeBasePeriod(app_derating_pwm_cfg[id_pwm].pwm_base)) / 10);

    return TI_OK;
}
