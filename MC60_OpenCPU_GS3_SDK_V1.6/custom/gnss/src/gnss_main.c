#ifdef __GNSS_MAIN__

#include "gnss_general.h"

void    proc_main_task(s32 taskId)
{
	ST_MSG  msg;

	// Register & open UART port
	Ql_UART_Register(UART_PORT1, CallBack_UART_Hdlr, NULL);
	Ql_UART_Open(UART_PORT1, 115200, FC_NONE);

	Ql_UART_Register(UART_PORT2, CallBack_UART_Hdlr, NULL);
	Ql_UART_Open(UART_PORT2, 115200, FC_NONE);

	// APP_DEBUG("\r\n<--OpenCPU: GNSS TEST!-->\r\n");

	while (TRUE)
	{
		Ql_OS_GetMessage(&msg);

		switch (msg.message)
		{
			case MSG_ID_RIL_READY:
			{
				// APP_DEBUG("<-- RIL is ready -->\r\n");
				Ql_RIL_Initialize();

				/* trigger the GNNS check task */
				Ql_OS_SendMessage(subtask1_id, GNSS_CHECK, 0, 0); 
				// APP_DEBUG("<-- TEST GNNS MESSAGE has been sent -->\r\n");
				break ;
			}
			default:
				break ;
		}
	}
}

#endif