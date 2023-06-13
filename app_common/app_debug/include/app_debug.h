#ifndef _APP_DEBUG_H_
#define _APP_DEBUG_H_

#include <stdint.h>

#define LOG_LOCAL_LEVEL  APP_LOG_VERBOSE

#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_BROWN   "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"
#define LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
#define LOG_RESET_COLOR   "\033[0m"
#define LOG_COLOR_E       LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W       LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I       LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V

#define BYTES_PER_LINE      16

static const char *TAG = "APP_MAIN";

#define APP_LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter "[%d][%s, %d]: " format LOG_RESET_COLOR "\n"

typedef enum {
    APP_LOG_NONE,       /*!< No log output */
    APP_LOG_ERROR,      /*!< Critical errors, software module can not recover on its own */
    APP_LOG_WARN,       /*!< Error conditions from which recovery measures have been taken */
    APP_LOG_INFO,       /*!< Information messages which describe normal flow of events */
    APP_LOG_DEBUG,      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    APP_LOG_VERBOSE     /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} app_log_level_t;


#define APP_LOGE( format, ... ) {                                                 \
    if (LOG_LOCAL_LEVEL >= APP_LOG_ERROR) {                                       \
        user_printf(APP_LOG_FORMAT(E, format), TAG, __LINE__, ##__VA_ARGS__);     \
}}

#define APP_LOGW( format, ... ) {                                                 \
    if (LOG_LOCAL_LEVEL >= APP_LOG_WARN) {                                        \
        user_printf(APP_LOG_FORMAT(W, format), TAG, __LINE__, ##__VA_ARGS__);     \
}}

#define APP_LOGI( format, ... )  {                                                \
    if (LOG_LOCAL_LEVEL >= APP_LOG_INFO) {                                        \
        user_printf(APP_LOG_FORMAT(I, format), TAG, __LINE__, ##__VA_ARGS__);     \
}}

#define APP_LOGD( format, ... ) {                                                 \
    if (LOG_LOCAL_LEVEL >= APP_LOG_DEBUG) {                                       \
        user_printf(APP_LOG_FORMAT(D, format), TAG, __LINE__, ##__VA_ARGS__);     \
}}

typedef struct {
    uint32_t                    baurate;
    uint32_t                    lspclk;
    uint16_t                    tx_gpio;
    uint16_t                    rx_gpio;
    uint16_t                    mux_pos;
} app_debug_uart_config_t;

#define APP_DEBUG_UART_INFO() { \
    .baurate = 9600,            \
    .lspclk  = 25 * 1000000,    \
    .tx_gpio = 29,              \
    .rx_gpio = 28,              \
    .mux_pos = 1                \
}

void app_debug_uart_init();
void UARTprintf();
int user_printf(const char *format, ...);
int user_sprintf(char *out, const char *format, ...);

#endif
