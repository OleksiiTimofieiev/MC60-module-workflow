// #include "general.h"

// void    init_and_start_timer(void)
// {
//     ret = Ql_Timer_Register(Stack_timer, Timer_handler, &m_param1);
//     if(ret <0)
//     {
//         APP_DEBUG("\r\n<--failed!!, Ql_Timer_Register: timer(%d) fail ,ret = %d -->\r\n",Stack_timer,ret);
//     }
//     APP_DEBUG("\r\n<--Register: timerId=%d, param = %d,ret = %d -->\r\n", Stack_timer ,m_param1,ret); 
 
//     ret = Ql_Timer_Start(Stack_timer,ST_Interval,TRUE);
//     if(ret < 0)
//     {
//         APP_DEBUG("\r\n<--failed!! stack timer Ql_Timer_Start ret=%d-->\r\n",ret);        
//     }
//     APP_DEBUG("\r\n<--stack timer Ql_Timer_Start(ID=%d,Interval=%d,) ret=%d-->\r\n",Stack_timer,ST_Interval,ret);
// }