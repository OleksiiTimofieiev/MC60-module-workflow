#include "gnss_general.h"

// typedef enum {
// 	EVENT_FLAG0 = 0x00000001, <-> start timer for the required interval;
// 	EVENT_FLAG1 = 0x00000002, 
// 	EVENT_FLAG2 = 0x00000004,
// 	EVENT_FLAG3 = 0x00000008,
// 	EVENT_FLAG4 = 0x00000010,
// 	EVENT_FLAG5 = 0x00000020,
// 	EVENT_FLAG6 = 0x00000040,
// 	EVENT_FLAG7 = 0x00000080,
// 	EVENT_FLAG8 = 0x00000100,
// 	EVENT_FLAG9 = 0x00000200,
// 	EVENT_FLAG_END
// }Enum_EventFlag;

#define	GNSS_check_timer	0x105

void	gnss_check(u32 timerId, void* param)
{
    bool    check_result = FALSE;

    if (timerId == GNSS_check_timer)
    {
        activate_gnss();

        while(!check_result) // separate timer;
        {
            check_result = gnss_read();
            Ql_Sleep(1000);
        }
        // Ql_OS_SetEvent(*((u32 *)param), EVENT_FLAG1);
    }
}

void    timer_GNSS_check_start(u32	gnss_status)
{
	s32		ret;
    u32 	repeat_interval = 1000 /* set_repeat_period(HOURS, MINUTES) */;
    
    ret = Ql_Timer_Register(GNSS_check_timer, gnss_check, &gnss_status);
    if(ret < 0)
    {
        ;// APP_DEBUG("<--failed!!, Ql_Timer_Register: timer(%d) fail -->\r\n", GNSS_check_timer);
    }
    // APP_DEBUG("<--Register: timerId\r\n"); 
 
    ret = Ql_Timer_Start(GNSS_check_timer, repeat_interval, TRUE);
    if(ret < 0)
    {
        ;// APP_DEBUG("<--failed!! gnss timer Ql_Timer_Start ret=%d-->\r\n",ret);        
    }
    // APP_DEBUG("<--gnss timer start\r\n");
}

void    timer_GNSS_check_stop(void)
{
    APP_DEBUG("%s\r\n", "stop timer\0");

    s32 ret;

    ret = Ql_Timer_Stop(GNSS_check_timer);

    if (ret < 0)
    {
        APP_DEBUG("\r\n<--failed!! stack timer Ql_Timer_Stop ret=%d-->\r\n",ret);           
    }
    APP_DEBUG("\r\n<--stack timer Ql_Timer_Stop(ID=%d,) ret=%d-->\r\n",GNSS_check_timer,ret);  

    deactivate_gnss();
}

void	gnss_events_processing(u32 gnss_status)
{
	if (!(Ql_OS_WaitEvent(gnss_status, EVENT_FLAG0)))
   	{
   		APP_DEBUG("start timer\r\n");
   		timer_GNSS_check_start(gnss_status);
   	}
   	else if (!(Ql_OS_WaitEvent(gnss_status, EVENT_FLAG1)))
   	{
   		APP_DEBUG("%s\r\n", "stop timer cmd\0");
   		timer_GNSS_check_stop();
   	}
}


void	proc_subtask1(s32 TaskId) /* needs more memory ? */ //check in the end of the development
{
    ST_MSG 	subtask1_msg;

    // APP_DEBUG("<--proc_subtask1-->\r\n");
	u32 gnss_status = Ql_OS_CreateEvent("gnss_status\0");

    while (TRUE)
    {    
        Ql_OS_GetMessage(&subtask1_msg);

        switch(subtask1_msg.message)
        {
            case GNSS_CHECK:
            {
            	/* trigger GNNS check */
          		Ql_OS_SetEvent(gnss_status, EVENT_FLAG0);
				break ;
          	}
            default:
                break;
        }
        gnss_events_processing(gnss_status);
    }
}