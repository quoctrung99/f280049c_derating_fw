#ifndef _APP_ADC_H_
#define _APP_ADC_H_

#include "driverlib.h"
#include "app_common.h"

#define NUM_ADC_DERATING    2

typedef struct {
    ADC_SOCNumber           adc_soc_num;
    ADC_Channel             adc_channel;
    ADC_Trigger             adc_trigger;
    ADC_IntNumber           adc_int_num;
} app_adc_soc_cfg_t;

typedef struct {
    uint32_t                adc_base;
    uint32_t                adc_result;
    ADC_PulseMode           adc_pluse_mode;
    ADC_ClkPrescale         adc_clk;
    ADC_ReferenceMode       adc_ref_mode;
    ADC_ReferenceVoltage    adc_ref;
    app_adc_soc_cfg_t       adc_soc_cfg;
} app_derating_adc_cfg_t;

typedef ti_err_t (*app_derating_adc_event_cb_t)(uint16_t *adc_value);

#define APP_DERATING_ADC_CFG() {                    \
    {                                               \
        .adc_base = ADCA_BASE,                      \
        .adc_result = ADCARESULT_BASE,              \
        .adc_pluse_mode = ADC_PULSE_END_OF_CONV,    \
        .adc_clk = ADC_CLK_DIV_4_0,                 \
        .adc_ref_mode = ADC_REFERENCE_INTERNAL,     \
        .adc_ref = ADC_REFERENCE_3_3V,              \
        .adc_soc_cfg = {                            \
            .adc_soc_num = ADC_SOC_NUMBER1,         \
            .adc_channel = ADC_CH_ADCIN1,           \
            .adc_trigger = ADC_TRIGGER_SW_ONLY,     \
            .adc_int_num = ADC_INT_NUMBER1          \
        }                                           \
    },                                              \
                                                    \
    {                                               \
        .adc_base = ADCA_BASE,                      \
        .adc_result = ADCARESULT_BASE,              \
        .adc_pluse_mode = ADC_PULSE_END_OF_CONV,    \
        .adc_clk = ADC_CLK_DIV_4_0,                 \
        .adc_ref_mode = ADC_REFERENCE_INTERNAL,     \
        .adc_ref = ADC_REFERENCE_3_3V,              \
        .adc_soc_cfg = {                            \
            .adc_soc_num = ADC_SOC_NUMBER0,         \
            .adc_channel = ADC_CH_ADCIN0,           \
            .adc_trigger = ADC_TRIGGER_SW_ONLY,     \
            .adc_int_num = ADC_INT_NUMBER1          \
        }                                           \
    }                                               \
}

void app_derating_adc_init();
void app_derating_adc_process();
ti_err_t app_derating_adc_register_cb(app_derating_adc_event_cb_t event_cb);


#endif
