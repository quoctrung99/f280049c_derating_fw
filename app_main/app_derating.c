#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "app_debug.h"
#include "app_derating.h"

#define MAX_OVER_TEMP       40.0
#define MIN_OVER_TEMP       30.0
#define DELTA_OVER_TEMP    -1.2

#define MAX_OVER_CURR       12.0
#define MIN_OVER_CURR       0.0

#define TEMP_HEADER_VALUE   0
#define ITEM_NUM(items)     (sizeof(items) / sizeof(items[0]))

static app_derating_event_cb_t app_derating_event_cb = NULL;

static const uint16_t ntc_data[] = {
    980,    1017,   1054,   1093,   1132,   1172,   1213,    1253,   1295,
    1337,   1380,   1423,   1466,   1510,   1554,   1598,    1643,   1688,
    1733,   1777,   1822,   1868,   1913,   1958,   2002,    2048,   2092,
    2136,   2180,   2224,   2267,   2310,   2352,   2394,    2435,   2476,
    2516,   2556,   2595,   2634,   2672,   2709,   2746,    2781,   2817,
    2851,   2885,   2918,   2950,   2982,   3013,   3043,    3072,   3101,
    3129,   3157,   3184,   3209,   3235,   3259,   3283,    3307,   3330,
    3352,   3373,   3394,   3414,   3434,   3453,   3472,    3490,   3507,
    3524,   3540,   3556,   3572,   3587,   3601,   3616,    3629,   3642,
    3655,   3668,   3680,   3692,   3703,   3714,   3724,    3734,   3744,
    3754,   3763,   3772,   3781,   3790,   3798,   3806,    3814,   3822,
    3829,   3836,   3843,   3850,   3856,   3862,   3868,    3874,   3880,
    3886,   3891,   3897,   3902,   3907,   3912,   3917,    3922,   3927,
    3931,   3935,   3940,   3944
};

static const app_derating_control_info_t app_derating_control_info[APP_DERATING_CONTROL_LEVEL_MAX + 1] = {
    [APP_DERATING_CONTROL_LEVEL_NORMAL] = {
        .min_temp = 0.0,    .max_temp = 50.0,    .duty_percent = 40
    },
    [APP_DERATING_CONTROL_LEVEL_1] = {
        .min_temp = 50.0,    .max_temp = 70.0,   .duty_percent = 70
    },
    [APP_DERATING_CONTROL_LEVEL_2] = {
        .min_temp = 70.0,    .max_temp = 90.0,   .duty_percent = 90
    },
    [APP_DERATING_CONTROL_LEVEL_MAX] = {
       .min_temp = 70.0,    .max_temp = 90.0,    .duty_percent = 90
    }
};

uint16_t app_derating_get_duty(float temp)
{
    app_derating_control_level_t idx;
    for (idx = APP_DERATING_CONTROL_LEVEL_NORMAL; idx < APP_DERATING_CONTROL_LEVEL_MAX; idx++) {
        if (temp >= app_derating_control_info[idx].min_temp && temp < app_derating_control_info[idx].max_temp) {
            return app_derating_control_info[idx].duty_percent;
        }
    }
    return app_derating_control_info[APP_DERATING_CONTROL_LEVEL_MAX].duty_percent;
}

static int16_t app_derating_search_midd(const uint16_t *table, uint16_t len, bool is_up, uint16_t adc_val)
{
    uint16_t bot, mid, top;

    if (len == 0) {
        return -1;
    }

    if (is_up) {
        if (adc_val < table[0]) {
            return -1;
        }

        if (adc_val > table[len - 1]) {
            return -1;
        }
    } else {
        if (adc_val > table[0]) {
            return -1;
        }

        if (adc_val < table[len - 1]) {
            return -1;
        }
    }

    bot = 0;
    top = len - 1;

    if (is_up) {
        while (bot < top) {
            mid = top - (top - bot) / 2;
            if (adc_val < table[mid]) {
                top = mid - 1;
            } else {
                bot = mid;
            }
        }
    } else {
        while (bot < top) {
            mid = top - (top - bot) / 2;
            if (adc_val > table[mid]) {
                top = mid - 1;
            } else {
                bot = mid;
            }
        }
    }

    if (adc_val == table[top]) {
        return top;
    }

    if (is_up) {
        if (adc_val > table[top]) {
            return top;
        }
    } else {
        if (adc_val < table[top]) {
            return top;
        }
    }

    return -1;
}

static uint16_t app_derating_get_temp(uint16_t adc_val)
{
    int16_t index = 0;
    uint16_t temperature = 0;

    index = app_derating_search_midd(ntc_data, ITEM_NUM(ntc_data), true, adc_val);

    if (index == 0) {
        temperature = TEMP_HEADER_VALUE * 10;
    } else if (index >= ITEM_NUM(ntc_data)) {
        temperature = 10 * (TEMP_HEADER_VALUE + ITEM_NUM(ntc_data));
    } else {
        temperature = TEMP_HEADER_VALUE + index;
        temperature = (temperature + 1) * 10 - 10.0 * (adc_val - ntc_data[index + 1]) / (ntc_data[index] - ntc_data[index + 1]);
    }

    return temperature;
}

ti_err_t app_derating_process(uint16_t adc_val, int idx_ntc)
{
    float temperature = app_derating_get_temp(adc_val) / 10.0;
    if (temperature < MIN_OVER_TEMP) {
        CHECK_IF_NOT_NULL(app_derating_event_cb, app_derating_event_cb(DERATING_EVENT_NORMAL, temperature, 0, idx_ntc));
    } else {
        float curr_over = DELTA_OVER_TEMP * (temperature - MIN_OVER_TEMP) + MAX_OVER_CURR;
        CHECK_IF_NOT_NULL(app_derating_event_cb, app_derating_event_cb(DERATING_EVENT_OVER_TEMP, temperature, curr_over, idx_ntc));
    }

    return TI_OK;
}

ti_err_t app_derating_register_cb(app_derating_event_cb_t event_cb)
{
    CHECK_IF_NULL(event_cb, return TI_FAIL);
    app_derating_event_cb = event_cb;

    return TI_OK;
}
