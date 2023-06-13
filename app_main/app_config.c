#include "app_config.h"
#include "app_debug.h"

void cfg_print()
{
    user_printf("\n\n");
    user_printf("================================================================\n");
    user_printf("=\tHardware Version:\t\t\t%s          =\n", HARDWARE_VERSION);
    user_printf("=\tMANUFACTUTER:\t\t\t%s               =\n", DEFAULT_MANUFACTUTER);
    user_printf("================================================================\n");
    user_printf("\n\n");
}
