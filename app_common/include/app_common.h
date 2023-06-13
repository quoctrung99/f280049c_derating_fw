#ifndef _APP_COMMON_H_
#define _APP_COMMON_H_

#include <stdint.h>

typedef int16_t ti_err_t;

#define TI_OK        0
#define TI_FAIL     -1

#define CHECK_IF_NULL(x, action)        do {    \
    if (x == NULL) action;                      \
} while (0)

#define CHECK_IF_NOT_NULL(x, action)    do {    \
    if (x != NULL) action;                      \
} while (0)


#endif
