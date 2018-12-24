#ifdef __DUAL_SIM__

/* libs and debug */
#include "general.h"
#include "project.h"

/* system information */
void    get_core(void);
void    get_SDK(void);

/* simultaneously works only with one slot */
void    proc_main_task(s32 taskId)
{
    ST_MSG  msg;

	APP_DEBUG("\n<--Open Debug Session.-->\r\n\0");

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
				break ;
            }
            case MSG_ID_URC_INDICATION:
            {
                switch(msg.param1)
                {
                    case URC_GPRS_NW_STATE_IND:
                    {
                   //     APP_DEBUG("<-- GPRS Network Status: waiting for the connection -->\r\n\0");
                        if (msg.param2 == NW_STAT_REGISTERED)
                        {
                            // APP_DEBUG("<-- GPRS Network Registered:%d -->\r\n\0", msg.param2);
                            init_and_start_dual_sim_diagnostics_timer();
                        }
                        break ;
                    }
                    default:
                        break ;
                }
            }
            default:
                break ;
		}
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

#endif // __CUSTOMER_CODE__
