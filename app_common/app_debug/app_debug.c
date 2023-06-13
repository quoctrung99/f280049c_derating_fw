#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "F28x_Project.h"
#include "app_debug.h"

#define PAD_RIGHT       1
#define PAD_ZERO        2
#define PRINT_BUF_LEN   12

static app_debug_uart_config_t app_debug_uart_cfg = APP_DEBUG_UART_INFO();

static void app_debug_uart_char(uint16_t c)
{
    while(SciaRegs.SCIFFTX.bit.TXFFST != 0){}
    SciaRegs.SCITXBUF.all = c;
}

void app_debug_uart_init()
{
    GPIO_SetupPinMux(app_debug_uart_cfg.tx_gpio, GPIO_MUX_CPU1, app_debug_uart_cfg.mux_pos);
    GPIO_SetupPinOptions(app_debug_uart_cfg.tx_gpio, GPIO_OUTPUT, GPIO_PULLUP);

    GPIO_SetupPinMux(app_debug_uart_cfg.rx_gpio, GPIO_MUX_CPU1, app_debug_uart_cfg.mux_pos);
    GPIO_SetupPinOptions(app_debug_uart_cfg.rx_gpio, GPIO_INPUT, GPIO_ASYNC);

    SciaRegs.SCICCR.all = 0x0007;
    SciaRegs.SCICTL1.all = 0x0003;

    SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

    SciaRegs.SCIHBAUD.all = ((app_debug_uart_cfg.lspclk /(8 * app_debug_uart_cfg.baurate)) - 1) >> 8;
    SciaRegs.SCILBAUD.all = ((app_debug_uart_cfg.lspclk /(8 * app_debug_uart_cfg.baurate)) - 1) & 0x00FF;

    // Initialize the SCI FIFO
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFCT.all = 0x0;

    SciaRegs.SCICTL1.all = 0x0023; // Relinquish SCI from Reset

    SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
    ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;

    SciaRegs.SCICTL1.bit.RXENA = 1;
}

void UARTprintf(unsigned char *msg)
{
    int i = 0;
    while (msg[i] != '\0') {
        app_debug_uart_char(msg[i]);
        i++;
    }
}

static void print_char(char **str, int c)
{
    if (str) {
        **str = c;
        ++(*str);
    } else {
        app_debug_uart_char(c);
    }
}

static int prints(char **out, const char *string, int width, int pad)
{
    register int pc = 0, padchar = ' ';

    if (width > 0) {
        register int len = 0;
        register const char *ptr;
        for (ptr = string; *ptr; ++ptr)
            ++len;
        if (len >= width)
            width = 0;
        else
            width -= len;
        if (pad & PAD_ZERO)
            padchar = '0';
    }

    if (!(pad & PAD_RIGHT)) {
        for (; width > 0; --width) {
            print_char(out, padchar);
            ++pc;
        }
    }

    for (; *string; ++string) {
        print_char(out, *string);
        ++pc;
    }
    for (; width > 0; --width) {
        print_char(out, padchar);
        ++pc;
    }

    return pc;
}

static int printi(char **out, int i, int b, int sg, int width, int pad, int letbase)
{
    char print_buf[PRINT_BUF_LEN];
    register char *s;
    register int t, neg = 0, pc = 0;
    register unsigned int u = i;

    if (i == 0) {
        print_buf[0] = '0';
        print_buf[1] = '\0';
        return prints(out, print_buf, width, pad);
    }

    if (sg && b == 10 && i < 0) {
        neg = 1;
        u = -i;
    }

    s = print_buf + PRINT_BUF_LEN - 1;
    *s = '\0';

    while (u) {
        t = u % b;
        if (t >= 10) {
            t += letbase - '0' - 10;
        }

        *--s = t + '0';
        u /= b;
    }

    if (neg) {
        if (width && (pad & PAD_ZERO)) {
            print_char(out, '-');
            ++pc;
            --width;
        } else {
            *--s = '-';
        }
    }

    return pc + prints(out, s, width, pad);
}

static int print(char **out, const char *format, va_list args)
{
    register int width, pad;
    register int pc = 0;
    char scr[2];

    for (; *format != 0; ++format) {
            if (*format == '%') {
                ++format;
                width = pad = 0;
                if (*format == '\0')
                    break;
                if (*format == '%')
                    goto out;
                if (*format == '-') {
                    ++format;
                    pad = PAD_RIGHT;
                }
                while (*format == '0') {
                    ++format;
                    pad |= PAD_ZERO;
                }
                for (; *format >= '0' && *format <= '9'; ++format) {
                    width *= 10;
                    width += *format - '0';
                }
                if (*format == 's') {
                    register char *s = (char *) va_arg( args, int );
                    pc += prints(out, s ? s : "(null)", width, pad);
                    continue;
                }
                if (*format == 'd') {
                    pc += printi(out, va_arg( args, int ), 10, 1, width, pad, 'a');
                    continue;
                }
                if (*format == 'x') {
                    pc += printi(out, va_arg( args, int ), 16, 0, width, pad, 'a');
                    continue;
                }
                if (*format == 'X') {
                    pc += printi(out, va_arg( args, int ), 16, 0, width, pad, 'A');
                    continue;
                }
                if (*format == 'u') {
                    pc += printi(out, va_arg( args, int ), 10, 0, width, pad, 'a');
                    continue;
                }
                if (*format == 'c') {
                    /* char are converted to int then pushed on the stack */
                    scr[0] = (char) va_arg( args, int );
                    scr[1] = '\0';
                    pc += prints(out, scr, width, pad);
                    continue;
                }
            } else {
                out: print_char(out, *format);
                ++pc;
            }
        }
        if (out)
            **out = '\0';
        va_end( args );
        return pc;
}

int user_printf(const char *format, ...)
{
    static char my_printf_buff[512] = {0};
    char *out = &my_printf_buff[0];

    va_list args;
    va_start(args, format );
    print(&out, format, args);
    UARTprintf(my_printf_buff);
}

int user_sprintf(char *out, const char *format, ...)
{
    va_list args;
    va_start( args, format );
    return print(&out, format, args);
}
