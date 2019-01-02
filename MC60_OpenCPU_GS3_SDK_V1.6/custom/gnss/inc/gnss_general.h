#ifndef __GNSS_GENERAL_H__
#define __GNSS_GENERAL_H__

/*
************************************************** libs ********************************************************
*/

#include "ql_type.h"
#include "ql_stdlib.h"
#include "ql_trace.h"
#include "ql_gpio.h"
#include "ql_uart.h"
#include "ql_iic.h"
#include "ql_error.h"
#include "ril.h"
#include "ril_util.h"
#include "ql_system.h"
#include "ril_gps.h"
#include "ql_gnss.h"
#include "nema_pro.h"
#include "ql_timer.h"

/*
************************************************** GNSS ********************************************************
*/

#include "project.h"

/*
************************************************** UART ********************************************************
*/

/* input buffer params */
#define DEBUG_ENABLE 1
#if DEBUG_ENABLE > 0
#define DEBUG_PORT  UART_PORT1
#define DBG_BUF_LEN   512
static char DBG_BUFFER[DBG_BUF_LEN];
#define APP_DEBUG(FORMAT,...) {\
    Ql_memset(DBG_BUFFER, 0, DBG_BUF_LEN);\
    Ql_sprintf(DBG_BUFFER,FORMAT,##__VA_ARGS__); \
    if (UART_PORT2 == (DEBUG_PORT)) \
    {\
        Ql_Debug_Trace(DBG_BUFFER);\
    } else {\
        Ql_UART_Write((Enum_SerialPort)(DEBUG_PORT), (u8*)(DBG_BUFFER), Ql_strlen((const char *)(DBG_BUFFER)));\
    }\
}
#else
#define APP_DEBUG(FORMAT,...) 
#endif

void CallBack_UART_Hdlr(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void* customizedPara);

#endif
