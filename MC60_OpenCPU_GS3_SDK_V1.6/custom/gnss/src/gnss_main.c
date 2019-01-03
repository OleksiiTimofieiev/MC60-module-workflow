#ifdef __GNSS_MAIN__

#include "gnss_general.h"

void    proc_main_task(s32 taskId)
{
	ST_MSG  msg;

	Ql_UART_Register(UART_PORT1, CallBack_UART_Hdlr, NULL);
	Ql_UART_Open(UART_PORT1, 115200, FC_NONE);

	Ql_UART_Register(UART_PORT2, CallBack_UART_Hdlr, NULL);
	Ql_UART_Open(UART_PORT2, 115200, FC_NONE);

	while (TRUE)
	{
		Ql_OS_GetMessage(&msg);

		switch (msg.message)
		{
			case MSG_ID_RIL_READY:
			{
				Ql_RIL_Initialize();

				/* trigger the GNNS check task */
				Ql_OS_SendMessage(subtask1_id, INITIAL_GNSS, 0, 0); 
				break ;
			}
			default:
				break ;
		}
	}
}

#endif