#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

#define HARDWARE_VERSION        "1.0.0"
#define DEFAULT_MANUFACTUTER    "Red&Blue"

#include <stdio.h>
#include <stdint.h>

#include "F28x_Project.h"
#include "driverlib.h"
#include "device.h"

#include "app_debug.h"
#include "app_timer_sys.h"
#include "app_derating.h"
#include "app_pwm.h"
#include "app_adc.h"

void cfg_print();


#endif
