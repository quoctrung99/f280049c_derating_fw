#ifndef _APP_DERATING_H_
#define _APP_DERATING_H_

#include "app_common.h"

typedef enum {
    APP_DERATING_NTC_BUCK = 0,
    APP_DERATING_NTC_BOOST,
    APP_DERATING_NTC_MAX
} app_derating_ntc_id_t;

typedef enum {
    DERATING_EVENT_NONE = 0,
    DERATING_EVENT_NORMAL,
    DERATING_EVENT_OVER_TEMP
} app_derating_id_event_t;

typedef enum {
    APP_DERATING_CONTROL_LEVEL_NORMAL = 0,
    APP_DERATING_CONTROL_LEVEL_1,
    APP_DERATING_CONTROL_LEVEL_2,
    APP_DERATING_CONTROL_LEVEL_MAX
} app_derating_control_level_t;

typedef struct {
    float               min_temp;
    float               max_temp;
    uint16_t            duty_percent;
} app_derating_control_info_t;

typedef ti_err_t (*app_derating_event_cb_t)(app_derating_id_event_t id_event, float temp, float curr_over, int ntc_id);

ti_err_t app_derating_process(uint16_t adc_val, int idx_ntc);
ti_err_t app_derating_register_cb(app_derating_event_cb_t event_cb);
uint16_t app_derating_get_duty(float temp);


#endif
