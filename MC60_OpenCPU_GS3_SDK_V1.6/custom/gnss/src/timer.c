#include "gnss_general.h"

void    timer_GNSS_check_data(u32 timerId, void *param)
{
    bool    check_result = FALSE;

    check_result = gnss_read();

    if (check_result)
    {
        Ql_Timer_Stop(GNSS_check_data); 
    }
}

void    timer_register_and_start(void)
{
    s32 ret;
       
    ret = Ql_Timer_Register(GNSS_check_data, timer_GNSS_check_data, NULL);

    if (ret < 0)
            APP_DEBUG("%s\r\n", "GNSS_check_data register failure");
    APP_DEBUG("%s\r\n", "GNSS_check_data register success");
    
    ret = Ql_Timer_Start(GNSS_check_data, GNSS_check_data_repeat, TRUE);

    if (ret < 0)
    {
        APP_DEBUG("%s\r\n", "GNSS_check_data start failure\0");
    }
    else
    {
        APP_DEBUG("%s\r\n", "GNSS_check_data start success\0");
    }
}
