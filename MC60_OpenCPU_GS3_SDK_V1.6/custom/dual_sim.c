
/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of Quectel Co., Ltd. 2013
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *   main.c
 *
 * Project:
 * --------
 *   OpenCPU
 *
 * Description:
 * ------------
 *   This app demonstrates how to send AT command with RIL API, and transparently
 *   transfer the response through MAIN UART. And how to use UART port.
 *   Developer can program the application based on this example.
 * 
 ****************************************************************************/
#ifdef __DUAL_SIM__

#include "custom_feature_def.h"
#include "ql_stdlib.h"
#include "ql_common.h"
#include "ql_type.h"
#include "ql_trace.h"
#include "ql_error.h"
#include "ql_uart.h"
#include "ql_gprs.h"
#include "ql_socket.h"
#include "ql_timer.h"
#include "ril_sim.h"
#include "ril_network.h"
#include "ril.h"
#include "ril_util.h"
#include "ril_telephony.h"
#include "ql_spi.h"
#include "ql_system.h"
#include "ql_gpio.h"

#define DEBUG_ENABLE 1
#if DEBUG_ENABLE > 0
#define DEBUG_PORT UART_PORT1
#define DBG_BUF_LEN 528
static char DBG_BUFFER[DBG_BUF_LEN];

#define APP_DEBUG(FORMAT, ...)                                                                                       \
{                                                                                                                \
    Ql_memset(DBG_BUFFER, 0, DBG_BUF_LEN);                                                                       \
    Ql_sprintf(DBG_BUFFER, FORMAT, ##__VA_ARGS__);                                                               \
    if (UART_PORT2 == (DEBUG_PORT))                                                                              \
    {                                                                                                            \
        Ql_Debug_Trace(DBG_BUFFER);                                                                              \
    }                                                                                                            \
    else                                                                                                         \
    {                                                                                                            \
        Ql_UART_Write((Enum_SerialPort)(DEBUG_PORT), (u8 *)(DBG_BUFFER), Ql_strlen((const char *)(DBG_BUFFER))); \
    }                                                                                                            \
}
#else
#define APP_DEBUG(FORMAT, ...)
#endif

/* input buffer params */
#define SERIAL_RX_BUFFER_LEN  2048
static  u8  m_RxBuf_Uart[SERIAL_RX_BUFFER_LEN];

/* send_AT_cmd */
void    dianostics(s32 code_of_error);
s32		response_callback(char* line, u32 len, void* userData);

/* UART callback routines */
void	CallBack_UART_Hdlr(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void* customizedPara);
s32		ReadSerialPort(Enum_SerialPort port, /*[out]*/u8* pBuffer, /*[in]*/u32 bufLen);

/* slot manipulations */
void    get_list_of_supported_slots(void);
void    get_active_slot(void);
void    change_active_slot(u8 slot);
void    get_SIM_state(void);


/* simultaneously works only with one slot */
void    proc_main_task(s32 taskId)
{
    ST_MSG  msg;
    s32     ret;

	APP_DEBUG("\n<--Open Debug Session.-->\r\n");

    Ql_UART_Register(UART_PORT1, CallBack_UART_Hdlr, NULL);
    Ql_UART_Open(UART_PORT1, 115200, FC_NONE);

    // ret = Ql_UART_Register(VIRTUAL_PORT1, CallBack_UART_Hdlr, NULL);
    // if (ret < QL_RET_OK)
    // {
    //     Ql_Debug_Trace("Fail to register virtual port[%d], ret=%d\r\n", UART_PORT1, ret);
    // }

    // ret = Ql_UART_Open(VIRTUAL_PORT1, 115200, FC_NONE);
    // if (ret < QL_RET_OK)
    // {
    //     Ql_Debug_Trace("Fail to open virtual port[%d], ret=%d\r\n", UART_PORT1, ret);
    // }

    /* system information */
    get_core();
    get_SDK();

	while (TRUE)
	{
        Ql_OS_GetMessage(&msg);

		switch (msg.message)
		{
			case MSG_ID_RIL_READY:
            {
				APP_DEBUG("<-- RIL is ready -->\r\n");

                Ql_RIL_Initialize();




                get_list_of_supported_slots();


                APP_DEBUG("SIM state:\r\n");
                get_SIM_state();

                get_active_slot();

                change_active_slot(1);
                get_active_slot();

                change_active_slot(0);
                get_active_slot();
                APP_DEBUG("SIM state:\r\n");
                get_SIM_state();

				break ;
            }
            // case MSG_ID_URC_INDICATION:
            // {
            //     switch(msg.param1)
            //     {
            //         case URC_GPRS_NW_STATE_IND:
            //         {
            //             APP_DEBUG("<-- GPRS Network Status: waiting for the connection -->\r\n");

            //             if (msg.param2 == NW_STAT_REGISTERED)
            //             {
            //                 APP_DEBUG("<-- GPRS Network Registered:%d -->\r\n", msg.param2);
                            
            //             }
            //             break ;
            //         }
            //         default:
            //             break ;
            //     }
            // }
            default:
                break ;
		}
    }
}

void	dianostics(s32 code_of_error)
{
	if (code_of_error == RIL_AT_FAILED)
	{
		APP_DEBUG("RIL_AT_FAILED\r\n");
	}
	else if (code_of_error == RIL_AT_TIMEOUT)
	{
		APP_DEBUG("RIL_AT_TIMEOUT\r\n");
	}
	else if (code_of_error == RIL_AT_BUSY)
	{
		APP_DEBUG("RIL_AT_BUSY\r\n");
	}
	else if (code_of_error == RIL_AT_INVALID_PARAM)
	{
		APP_DEBUG("RIL_AT_INVALID_PARAM\r\n");
	}
	else if (code_of_error == RIL_AT_UNINITIALIZED)
	{
		APP_DEBUG("RIL_AT_UNINITIALIZED\r\n");
	}
}

s32		response_callback(char* line, u32 len, void* userData) // el costello in func;
{
    Ql_UART_Write(UART_PORT1, (u8*)line, len);

    // APP_DEBUG("line in callback -> %s\r\n", line);
    
    if (Ql_RIL_FindLine(line, len, "OK"))
    {  
        return  RIL_ATRSP_SUCCESS;
    }
    else if (Ql_RIL_FindLine(line, len, "ERROR"))
    {  
        return  RIL_ATRSP_FAILED;
    }
    else if (Ql_RIL_FindString(line, len, "+CME ERROR"))
    {
        return  RIL_ATRSP_FAILED;
    }
    else if (Ql_RIL_FindString(line, len, "+CMS ERROR:"))
    {
        return  RIL_ATRSP_FAILED;
    }
    return RIL_ATRSP_CONTINUE; //continue wait
    // return  RIL_ATRSP_SUCCESS;
}

s32 	ReadSerialPort(Enum_SerialPort port, /*[out]*/u8* pBuffer, /*[in]*/u32 bufLen)
{
    s32 rdLen = 0;
    s32 rdTotalLen = 0;
    if (NULL == pBuffer || 0 == bufLen)
    {
        return -1;
    }
    Ql_memset(pBuffer, 0x0, bufLen);
    while (1)
    {
        rdLen = Ql_UART_Read(port, pBuffer + rdTotalLen, bufLen - rdTotalLen);
        if (rdLen <= 0)  // All data is read out, or Serial Port Error!
        {
            break;
        }
        rdTotalLen += rdLen;
        // Continue to read...
    }
    
    // APP_DEBUG("Input to the port -> %s\r\n", pBuffer);

    if (rdLen < 0) // Serial Port Error!
    {
        APP_DEBUG("<--Fail to read from port[%d]-->\r\n", port);
        return -99;
    }
    return rdTotalLen;
}

void 	CallBack_UART_Hdlr(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void* customizedPara)
{
    switch (msg)
    {
    case EVENT_UART_READY_TO_READ:
        {
           s32 totalBytes = ReadSerialPort(port, m_RxBuf_Uart, sizeof(m_RxBuf_Uart));
           break;
        }
    case EVENT_UART_READY_TO_WRITE:
        break;
    default:
        break;
    }
}

void    get_core(void)
{
    s32 ret;
    u8 tmpbuf[100];
    
    Ql_memset(tmpbuf, 0x0, sizeof(tmpbuf));
    ret = Ql_GetCoreVer((u8*)tmpbuf, sizeof(tmpbuf));
    if(ret > 0)
    {
        APP_DEBUG("<--Core Version:%s-->\r\n", tmpbuf);
    }
    else
    {
        APP_DEBUG("<--Get Core Version Failure.-->\r\n");
    }
}

void    get_SDK(void)
{
    s32 ret;
    u8 tmpbuf[100];
    
    Ql_memset(tmpbuf, 0, sizeof(tmpbuf));
    ret = Ql_GetSDKVer((u8*)tmpbuf, sizeof(tmpbuf));
    if(ret > 0)
    {
        APP_DEBUG("<--SDK Version:%s.-->\r\n", tmpbuf);
    }else
    {
        APP_DEBUG("<--Get SDK Version Failure.-->\r\n");
    }
}

s32     send_AT_cmd(u8 *cmd, s32 *fun)
{
    *fun = 0;
    return Ql_RIL_SendATCmd(cmd, Ql_strlen(cmd), response_callback, NULL, 0);
}

void    get_list_of_supported_slots(void)
{
    s32     func_result = RIL_AT_FAILED;

    APP_DEBUG("List of supported slots:\r\n");
    if ((func_result = send_AT_cmd("AT+QDSIM=?\0", &func_result)) != RIL_AT_SUCCESS)
    {
        dianostics(func_result);
    }
}

void    get_active_slot(void)
{
    s32     func_result = RIL_AT_FAILED;

    APP_DEBUG("Active slot:\r\n");
    if ((func_result = send_AT_cmd("AT+QDSIM?\0", &func_result)) != RIL_AT_SUCCESS)
    {
        dianostics(func_result);
    }
}

void    change_active_slot(u8 slot)
{
    s32     func_result = RIL_AT_FAILED;

    u8  cmd[14];

    Ql_memset(cmd, '\0', Ql_strlen(cmd));
    Ql_sprintf(cmd, "AT+QDSIM=%d\0", slot);

    APP_DEBUG("Change active slot to -> %d\r\n", slot);
    if ((func_result = send_AT_cmd(cmd, &func_result)) != RIL_AT_SUCCESS)
    {
        dianostics(func_result);
    }
}

void    get_SIM_state(void)
{
    s32 ret = RIL_AT_FAILED;
    s32 state = 0;
    
    /* only for debug -> needs to be removed */
    while (ret != RIL_AT_SUCCESS)
    {
        ret = RIL_SIM_GetSimState(&state);
        APP_DEBUG("Error\r\n");
        dianostics(ret);
        Ql_Sleep(500);
    }

    if (state == SIM_STAT_NOT_INSERTED)
    {
        APP_DEBUG("SIM_STAT_NOT_INSERTED\r\n");
    }
    else if (state == SIM_STAT_READY)
    {
        APP_DEBUG("SIM_STAT_READY\r\n");
    }
    else if (state == SIM_STAT_PIN_REQ)
    {
        APP_DEBUG("SIM_STAT_PIN_REQ\r\n");
    }
    else if (state == SIM_STAT_PUK_REQ)
    {
        APP_DEBUG("SIM_STAT_PUK_REQ\r\n");
    }
    else if (state == SIM_STAT_PIN2_REQ)
    {
        APP_DEBUG("SIM_STAT_PIN2_REQ\r\n");
    }
    else if (state == SIM_STAT_PUK2_REQ)
    {
        APP_DEBUG("SIM_STAT_PUK2_REQ\r\n");
    }
    else if (state == SIM_STAT_BUSY)
    {
        APP_DEBUG("SIM_STAT_BUSY\r\n");
    }
    else if (state == SIM_STAT_NOT_READY)
    {
        APP_DEBUG("SIM_STAT_NOT_READY\r\n");
    }
    else if (state == SIM_STAT_UNSPECIFIED)
    {
        APP_DEBUG("SIM_STAT_UNSPECIFIED\r\n");
    }
    else
    {
        APP_DEBUG("UNKNOWN BUG\r\n");
    }
}

#endif // __CUSTOMER_CODE__
