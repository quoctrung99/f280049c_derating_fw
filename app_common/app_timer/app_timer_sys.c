#include <stdint.h>
#include "F28x_Project.h"
#include "app_timer_sys.h"

static __interrupt void app_timer_isr(void)
{
    CpuTimer0.InterruptCount++;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

void app_timer_sys_init()
{
    EALLOW;
    PieVectTable.TIMER0_INT = &app_timer_isr;
    EDIS;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 100, 1 * 1000); // ~1ms

    CpuTimer0Regs.TCR.all = 0x4000;
    IER |= PIEACK_GROUP1;

    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
}

uint32_t app_tick_get()
{
    return CpuTimer0.InterruptCount;
}
