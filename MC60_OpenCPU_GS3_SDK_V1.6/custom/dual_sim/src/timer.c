#include "general.h"
#include "project.h"

/* diagnostics timer */

#define	REPEAT_PERIOD			1
#define	DUAL_SIM_TIMER_ID		0x102

u32		minutes_to_milliseconds_converter(u32	minutes);
void	dual_sim_diagnostics_timer_handler(u32 timerId, void* param);

void    init_and_start_dual_sim_diagnostics_timer(void)
{
	s32		ret;
    u32 	repeat_interval =  minutes_to_milliseconds_converter(REPEAT_PERIOD);
    
    ret = Ql_Timer_Register(DUAL_SIM_TIMER_ID, dual_sim_diagnostics_timer_handler, NULL);
    if(ret < 0)
    {
        APP_DEBUG("<--failed!!, Ql_Timer_Register: timer(%d) fail -->\r\n", DUAL_SIM_TIMER_ID);
    }
    APP_DEBUG("<--Register: timerId\r\n"); 
 
    ret = Ql_Timer_Start(DUAL_SIM_TIMER_ID, repeat_interval,TRUE);
    if(ret < 0)
    {
        APP_DEBUG("<--failed!! stack timer Ql_Timer_Start ret=%d-->\r\n",ret);        
    }
    APP_DEBUG("<--dual_sim timer start\r\n");
}

void	dual_sim_diagnostics_timer_handler(u32 timerId, void* param)
{
	s32	active_slot;

    if (DUAL_SIM_TIMER_ID == timerId)
    {
        network_test(); // add if bad network logic;

        active_slot = get_active_slot();

    	APP_DEBUG("slot_number -> %d\r\n", active_slot);
	
		if (active_slot == 0)
			change_active_slot(1);
		else if (active_slot == 1)
			change_active_slot(0);    
    }    
}

u32		minutes_to_milliseconds_converter(u32	minutes)
{
	u32		res;

	res = 60 * 1000 * minutes;

	return (res);
}