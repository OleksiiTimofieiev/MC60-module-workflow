#ifndef __IIC_PROJECT__
#define __IIC_PROJECT__

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

/* device information */
#include "lis.h"

/* float data type */
#include "math.h"

/* sensitivity constants */
#include "sensitivity_conversion.h"

/*
************************************************** UART ********************************************************
*/

/* input buffer params */
#define SERIAL_RX_BUFFER_LEN  2048
static  u8  m_RxBuf_Uart[SERIAL_RX_BUFFER_LEN];

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

static void CallBack_UART_Hdlr(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void* customizedPara);

/*
************************************************** I2C ********************************************************
*/

u8		lis_RD(u8 reg); // RD data from specified register;
void	lis_WR(u8 reg, u8 data); // configure register

void    xyz_timer_int_and_start(void);
// typedef	struct 	xyz_hardware
// {

// }				xyz_hardware_data

#define STATUS_AUX_321DA 0x08

#endif
