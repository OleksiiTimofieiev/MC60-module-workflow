#include "gnss_general.h"

void	proc_subtask1(s32 TaskId)
{
    ST_MSG 	subtask1_msg;

    while (TRUE)
    {    
        Ql_OS_GetMessage(&subtask1_msg);

        switch(subtask1_msg.message)
        {
            case GNSS_CHECK:
            {
   				timer_GNSS_register_timers();
				break ;
          	}
          	case GNSS_TIMER_STOP:
          	{
          		Ql_Sleep(1000);
        		deactivate_gnss();
          		APP_DEBUG("%s\r\n", "timer has been stopped\0");
          		break ;
          	}
            default:
                break;
        }
    }
}