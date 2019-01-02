#include "gnss_general.h"

// #define	REPEAT          	1000 // conversion procedure;
#define	GNSS_check_timer	0x105
// #define GNSS_protocol_check 0x106

#define	HOURS 				0
#define	MINUTES 			1

u64		set_repeat_period(u8 hours, u8 minutes)
{
	u64		total_seconds = hours * 3600 + minutes * 60;
	u64		milliseconds = total_seconds * 1000;

	return (milliseconds);
}

void	gnss_check(u32 timerId, void* param)
{
    if (timerId == GNSS_check_timer)
    {
	   // APP_DEBUG("Timer works\r\n");
       activate_gnss();
       
       gnss_read();
       // deactivate_gnss();
    }
}

void    timer_GNSS_check_start(void)
{
	s32		ret;
    u32 	repeat_interval = 500 /* set_repeat_period(HOURS, MINUTES) */;
    
    ret = Ql_Timer_Register(GNSS_check_timer, gnss_check, NULL);
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
