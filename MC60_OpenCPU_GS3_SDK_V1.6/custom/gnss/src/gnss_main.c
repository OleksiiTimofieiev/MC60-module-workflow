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

				break ;
			}
			default:
				break ;
		}
	}
}

void	proc_subtask1(s32 TaskId)
{
    ST_MSG 	subtask1_msg;
    u32		gnss_status;
	s32		event_wait_status;
	s32		event_send_check;

    // APP_DEBUG("<--proc_subtask1-->\r\n");

	gnss_status = Ql_OS_CreateEvent("gnss_status\0");

    while (TRUE)
    {    
        Ql_OS_GetMessage(&subtask1_msg);

        switch(subtask1_msg.message)
        {
            case GNSS_CHECK:
            {
            	/* trigger GNNS check */
          		event_send_check = Ql_OS_SetEvent(gnss_status, EVENT_FLAG0);
				break ;
          	}
            default:
                break;
        }

        gnss_events_processing(gnss_status, event_wait_status);
    }
}

#endif