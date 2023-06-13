//#############################################################################
//
// FILE:   driverlib.h
//
// TITLE:  C28x Driverlib Header File
//
//#############################################################################
// $TI Release: TIDM_DC_DC_BUCK v2.01.05.00 $
// $Release Date: Thu Jan 26 15:57:54 CST 2023 $
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
//
// ALL RIGHTS RESERVED
// $
//#############################################################################
#ifndef DRIVERLIB_H
#define DRIVERLIB_H

#include "inc/hw_memmap.h"

#include "adc.h"
#include "asysctl.h"

#ifndef __TMS320C28XX_CLA__

#include "can.h"
#include "cla.h"

#include "cpu.h"
#include "cputimer.h"

#endif

#include "clapromcrc.h"

#include "cmpss.h"

#ifndef __TMS320C28XX_CLA__
#include "dac.h"
#include "dcsm.h"
#include "debug.h"
#include "dma.h"
#endif

#include "dcc.h"

#include "ecap.h"

#include "epwm.h"

#ifndef __TMS320C28XX_CLA__
#include "eqep.h"
#include "flash.h"
#include "fsi.h"
#endif

#include "gpio.h"

#include "hrcap.h"

#ifndef __TMS320C28XX_CLA__
#include "hrpwm.h"
#include "i2c.h"
#include "interrupt.h"
#endif

#include "pin_map.h"
#include "pin_map_legacy.h"

#include "sdfm.h"
#include "version.h"
#include "xbar.h"

#ifndef __TMS320C28XX_CLA__

#include "memcfg.h"
#include "sysctl.h"

#include "sci.h"
#include "spi.h"
#include "lin.h"
#include "pga.h"
#include "pmbus.h"
#endif

#endif  // end of DRIVERLIB_H definition
