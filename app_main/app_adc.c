#include "app_adc.h"
#include "app_timer_sys.h"
#include "app_debug.h"

#define TIMEOUT_ADC_MS          1 * 100

static app_derating_adc_cfg_t app_derating_adc[] = APP_DERATING_ADC_CFG();
static app_derating_adc_event_cb_t app_derating_adc_event_cb = NULL;

static uint32_t tick_derating_adc = 0;

static void app_derating_adc_soc_init(int idx)
{
    ADC_setupSOC(app_derating_adc[idx].adc_base, app_derating_adc[idx].adc_soc_cfg.adc_soc_num,
                 app_derating_adc[idx].adc_soc_cfg.adc_trigger, app_derating_adc[idx].adc_soc_cfg.adc_channel, 10);

    ADC_setInterruptSource(app_derating_adc[idx].adc_base, app_derating_adc[idx].adc_soc_cfg.adc_int_num, app_derating_adc[idx].adc_soc_cfg.adc_soc_num);
    ADC_enableInterrupt(app_derating_adc[idx].adc_base, app_derating_adc[idx].adc_soc_cfg.adc_int_num);
    ADC_clearInterruptStatus(app_derating_adc[idx].adc_base, app_derating_adc[idx].adc_soc_cfg.adc_int_num);
}

void app_derating_adc_init()
{
    uint8_t idx;
    for (idx = 0; idx < NUM_ADC_DERATING; idx++) {
        app_derating_adc_soc_init(idx);
        ADC_setVREF(app_derating_adc[idx].adc_base, app_derating_adc[idx].adc_ref_mode, app_derating_adc[idx].adc_ref);
        ADC_setPrescaler(app_derating_adc[idx].adc_base, app_derating_adc[idx].adc_clk);
        ADC_setInterruptPulseMode(app_derating_adc[idx].adc_base, app_derating_adc[idx].adc_pluse_mode);
        ADC_enableConverter(app_derating_adc[idx].adc_base);
    }
}

static uint16_t *app_derating_adc_get_value()
{
    uint8_t idx, index = 0;
    static uint16_t adc_value[NUM_ADC_DERATING];
    for (idx = 0; idx < NUM_ADC_DERATING; idx++) {
        ADC_forceSOC(app_derating_adc[idx].adc_base, app_derating_adc[idx].adc_soc_cfg.adc_soc_num);
    }
    while (!ADC_getInterruptStatus(app_derating_adc[0].adc_base, app_derating_adc[0].adc_soc_cfg.adc_int_num));
    ADC_clearInterruptStatus(app_derating_adc[0].adc_base, app_derating_adc[0].adc_soc_cfg.adc_int_num);

    for (index = 0; index < NUM_ADC_DERATING; index++) {
        adc_value[index] = ADC_readResult(app_derating_adc[index].adc_result, app_derating_adc[index].adc_soc_cfg.adc_soc_num);
    }

    return adc_value;
}

static uint16_t *app_derating_adc_filter()
{
    uint16_t *adc_min, *adc_max, *adc_temp;
    static uint16_t adc_result[NUM_ADC_DERATING], adc_return[NUM_ADC_DERATING];

    uint8_t i, j, k, index = 0;

    for (k = 0; k < NUM_ADC_DERATING; k++) {
        adc_return[k] = 0;
    }

    for (index = 0; index < NUM_ADC_DERATING; index++) {
        for (i = 0; i < 16; i++) {
            adc_result[index] = 0;
            adc_min = adc_max = app_derating_adc_get_value();
            for (j = 0; j < 8; j++) {
                adc_temp = app_derating_adc_get_value();
                if (adc_temp[index] < adc_min[index]) {
                    adc_result[index] += adc_min[index];
                    adc_min[index] = adc_temp[index];
                } else if (adc_temp[index] > adc_max[index]) {
                    adc_result[index] += adc_max[index];
                    adc_max[index] = adc_temp[index];
                } else {
                    adc_result[index] += adc_temp[index];
                }
            }
            adc_result[index] /= 8;
            adc_return[index] += adc_result[index];
        }
        adc_return[index] /= 16;
    }

    return adc_return;
}

ti_err_t app_derating_adc_register_cb(app_derating_adc_event_cb_t event_cb)
{
    CHECK_IF_NULL(event_cb, return TI_FAIL);
    app_derating_adc_event_cb = event_cb;

    return TI_OK;
}

void app_derating_adc_process()
{
    if (app_tick_get() - tick_derating_adc >= TIMEOUT_ADC_MS) {
        tick_derating_adc = app_tick_get();
        CHECK_IF_NOT_NULL(app_derating_adc_event_cb, app_derating_adc_event_cb(app_derating_adc_filter()));
    }
}
