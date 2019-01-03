#include "gnss_general.h"

static  bool gnss_activation;

void    timer_GNSS_check_data(u32 timerId, void *param)
{
    APP_DEBUG("%s\r\n", "data timer\0");

    bool    check_result = FALSE;

    check_result = gnss_read();

    if (check_result)
    {
        gnss_activation = FALSE;

        Ql_OS_SendMessage(subtask1_id, GNSS_TIMER_STOP, 0, 0);

        Ql_Timer_Stop(GNSS_check_data); 
    }
}

void    timer_GNSS_check_general(u32 timerId, void *param)
{
    APP_DEBUG("%s\r\n", "general timer\0");

    if (!gnss_activation)
    {
        activate_gnss();
        gnss_activation = TRUE;
    }

    if (gnss_activation)
    {
        s32 ret;

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
}

void    timer_GNSS_register_timers(void)
{
    gnss_activation = FALSE;

    s32 ret;
    
    ret = Ql_Timer_Register(GNSS_check_general, timer_GNSS_check_general, NULL);

    if (ret < 0)
            APP_DEBUG("%s\r\n", "GNSS_check_general register failure");
    APP_DEBUG("%s\r\n", "GNSS_check_general register success");
    
    ret = Ql_Timer_Register(GNSS_check_data, timer_GNSS_check_data, NULL);

     if (ret < 0)
            APP_DEBUG("%s\r\n", "GNSS_check_data register failure");
    APP_DEBUG("%s\r\n", "GNSS_check_data register success");

    Ql_Timer_Start(GNSS_check_general, GNSS_check_general_repeat, TRUE);
}
