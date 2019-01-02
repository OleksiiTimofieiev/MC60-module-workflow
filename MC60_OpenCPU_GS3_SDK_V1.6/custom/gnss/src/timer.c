// #include "gnss_general.h"

// // #define	REPEAT          	1000 // conversion procedure;
// #define	GNSS_check_timer	0x105
// // #define GNSS_protocol_check 0x106

// #define	HOURS 				0
// #define	MINUTES 			1

// u64		set_repeat_period(u8 hours, u8 minutes)
// {
// 	u64		total_seconds = hours * 3600 + minutes * 60;
// 	u64		milliseconds = total_seconds * 1000;

// 	return (milliseconds);
// }

// void	gnss_check(u32 timerId, void* param)
// {
//     bool    check_result = FALSE;

//     if (timerId == GNSS_check_timer)
//     {
//         activate_gnss();

//         while(!check_result) // separate timer;
//         {
//             check_result = gnss_read();
//             Ql_Sleep(1000);
//         }
//         Ql_OS_SetEvent(*((u32 *)param), EVENT_FLAG1);
//     }
// }

// void    timer_GNSS_check_start(u32  gnss_status)
// {
// 	s32		ret;
//     u32 	repeat_interval = 1000 /* set_repeat_period(HOURS, MINUTES) */;
    
//     ret = Ql_Timer_Register(GNSS_check_timer, gnss_check, &gnss_status);
//     if(ret < 0)
//     {
//         ;// APP_DEBUG("<--failed!!, Ql_Timer_Register: timer(%d) fail -->\r\n", GNSS_check_timer);
//     }
//     // APP_DEBUG("<--Register: timerId\r\n"); 
 
//     ret = Ql_Timer_Start(GNSS_check_timer, repeat_interval, TRUE);
//     if(ret < 0)
//     {
//         ;// APP_DEBUG("<--failed!! gnss timer Ql_Timer_Start ret=%d-->\r\n",ret);        
//     }
//     // APP_DEBUG("<--gnss timer start\r\n");
// }

// void    timer_GNSS_check_stop(void)
// {
//     APP_DEBUG("%s\r\n", "stop timer\0");

//     s32 ret;

//     ret = Ql_Timer_Stop(GNSS_check_timer);

//     if (ret < 0)
//     {
//         APP_DEBUG("\r\n<--failed!! stack timer Ql_Timer_Stop ret=%d-->\r\n",ret);           
//     }
//     APP_DEBUG("\r\n<--stack timer Ql_Timer_Stop(ID=%d,) ret=%d-->\r\n",GNSS_check_timer,ret);  

//     deactivate_gnss();
// }