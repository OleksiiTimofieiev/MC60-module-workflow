#ifdef __GNSS_MAIN__

#include "gnss.h"

void    proc_main_task(s32 taskId)
{
	s32     ret;
	ST_MSG  msg;

	// Register & open UART port
	Ql_UART_Register(UART_PORT1, CallBack_UART_Hdlr, NULL);
	Ql_UART_Open(UART_PORT1, 115200, FC_NONE);

	Ql_UART_Register(UART_PORT2, CallBack_UART_Hdlr, NULL);
	Ql_UART_Open(UART_PORT2, 115200, FC_NONE);

	APP_DEBUG("\r\n<--OpenCPU: IIC TEST!-->\r\n"); 

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
			default:
				break ;
		}
	}
}


#endif