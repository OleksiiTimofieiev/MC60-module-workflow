#include "general.h"
#include "project.h"

/* diagnostics timer */

#define	REPEAT_PERIOD			1
#define	DUAL_SIM_TIMER_ID		0x102
static  bool slot_check = FALSE;

void	dual_sim_diagnostics_timer_handler(u32 timerId, void* param);
u32		minutes_to_milliseconds_converter(u32	minutes);

void    init_and_start_dual_sim_diagnostics_timer(void)
{
	s32		ret;
    u32 	repeat_interval = minutes_to_milliseconds_converter(REPEAT_PERIOD);
    
    ret = Ql_Timer_Register(DUAL_SIM_TIMER_ID, dual_sim_diagnostics_timer_handler, NULL);
    if(ret < 0)
    {
        APP_DEBUG("\r\n<--failed!!, Ql_Timer_Register: timer(%d) fail -->\r\n", DUAL_SIM_TIMER_ID);
    }
    APP_DEBUG("\r\n<--Register: timerId=%d\r\n", DUAL_SIM_TIMER_ID); 
 
    ret = Ql_Timer_Start(DUAL_SIM_TIMER_ID, repeat_interval,TRUE);
    if(ret < 0)
    {
        APP_DEBUG("\r\n<--failed!! stack timer Ql_Timer_Start ret=%d-->\r\n",ret);        
    }
    APP_DEBUG("\r\n<--stack timer Ql_Timer_Start(ID=%d,Interval=%d,) ret=%d-->\r\n", DUAL_SIM_TIMER_ID, repeat_interval, ret);
}

void	dual_sim_diagnostics_timer_handler(u32 timerId, void* param)
{
    if (DUAL_SIM_TIMER_ID == timerId)
    {
        APP_DEBUG("<-- stack dual_sim_diagnostics_timer_handler -->\r\n");
        network_test();
  		// get_list_of_supported_slots();
		// get_active_slot();
		if (slot_check == FALSE)
			change_active_slot(1);
		get_active_slot();


        // DUAL_SIM_TIMER_ID repeat 
            // s32 ret;
            // ret = Ql_Timer_Stop(DUAL_SIM_TIMER_ID);
            // if(ret < 0)
            // {
            //       APP_DEBUG("\r\n<--failed!! stack timer Ql_Timer_Stop ret=%d-->\r\n",ret);           
            // }
            // APP_DEBUG("\r\n<--stack timer Ql_Timer_Stop(ID=%d,) ret=%d-->\r\n",DUAL_SIM_TIMER_ID,ret);            
        // }        
    }    
}

u32		minutes_to_milliseconds_converter(u32	minutes)
{
	u32		res;

	res = 60 * 1000 * minutes;

	return (res);
}