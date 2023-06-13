#include "app_config.h"

static ti_err_t app_derating_event_cb(app_derating_id_event_t id_event, float temp, float curr_over, int ntc_id)
{
    APP_LOGI("temperature: %d - [%d]", (uint16_t)(temp), ntc_id);
    switch (id_event) {
        case DERATING_EVENT_NORMAL:
            break;
        case DERATING_EVENT_OVER_TEMP:
            APP_LOGI("current over: %d", (uint16_t)(curr_over));
            break;
    }

    if (ntc_id == APP_DERATING_PWM_BUCK) {
        app_derating_pwm_set_duty(app_derating_get_duty(temp), APP_DERATING_PWM_BUCK);
    } else if (ntc_id == APP_DERATING_PWM_BOOST) {
        app_derating_pwm_set_duty(app_derating_get_duty(temp), APP_DERATING_PWM_BOOST);
    }

    return TI_OK;
}

static ti_err_t app_derating_adc_cb(uint16_t *adc_value)
{
    uint8_t index = 0;
    for (index = 0; index < NUM_ADC_DERATING; index++) {
        app_derating_process(adc_value[index], index);
    }

    return TI_OK;
}

void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    app_debug_uart_init();
    app_timer_sys_init();
    app_derating_pwm_init();
    app_derating_adc_init();

    app_derating_register_cb(&app_derating_event_cb);
    app_derating_adc_register_cb(&app_derating_adc_cb);

    EINT;
    ERTM;

    APP_LOGI("Start project");

    while (1) {
        //app_derating_adc_process();
        app_derating_pwm_set_duty(50, APP_DERATING_PWM_BUCK);
        app_derating_pwm_set_duty(50, APP_DERATING_PWM_BOOST);
    }
}
