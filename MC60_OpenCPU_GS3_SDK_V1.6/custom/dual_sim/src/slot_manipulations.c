#include "general.h"
#include "project.h"

/* slot manipulations */

void    dianostics(s32 code_of_error);
void    get_list_of_supported_slots(void);
void    get_active_slot(void);
void    change_active_slot(u8 slot);
void    get_SIM_state(void);


void	dianostics(s32 code_of_error)
{
	if (code_of_error == RIL_AT_FAILED)
	{
		APP_DEBUG("RIL_AT_FAILED\r\n");
	}
	else if (code_of_error == RIL_AT_TIMEOUT)
	{
		APP_DEBUG("RIL_AT_TIMEOUT\r\n");
	}
	else if (code_of_error == RIL_AT_BUSY)
	{
		APP_DEBUG("RIL_AT_BUSY\r\n");
	}
	else if (code_of_error == RIL_AT_INVALID_PARAM)
	{
		APP_DEBUG("RIL_AT_INVALID_PARAM\r\n");
	}
	else if (code_of_error == RIL_AT_UNINITIALIZED)
	{
		APP_DEBUG("RIL_AT_UNINITIALIZED\r\n");
	}
}

s32     send_AT_cmd(u8 *cmd, s32 *fun)
{
    *fun = 0;
    return Ql_RIL_SendATCmd(cmd, Ql_strlen(cmd), response_callback, NULL, 0);
}

void    get_list_of_supported_slots(void)
{
    s32     func_result = RIL_AT_FAILED;

    APP_DEBUG("List of supported slots:\r\n");
    if ((func_result = send_AT_cmd("AT+QDSIM=?\0", &func_result)) != RIL_AT_SUCCESS)
    {
        dianostics(func_result);
    }
}

void    get_active_slot(void)
{
    s32     func_result = RIL_AT_FAILED;

    APP_DEBUG("Active slot:\r\n");
    if ((func_result = send_AT_cmd("AT+QDSIM?\0", &func_result)) != RIL_AT_SUCCESS)
    {
        dianostics(func_result);
    }
}

void    change_active_slot(u8 slot)
{
    s32     func_result = RIL_AT_FAILED;

    u8  cmd[14];

    Ql_memset(cmd, '\0', Ql_strlen(cmd));
    Ql_sprintf(cmd, "AT+QDSIM=%d\0", slot);

    APP_DEBUG("Change active slot to -> %d\r\n", slot);
    if ((func_result = send_AT_cmd(cmd, &func_result)) != RIL_AT_SUCCESS)
    {
        dianostics(func_result);
    }
}

void    get_SIM_state(void)
{
    s32 ret = RIL_AT_FAILED;
    s32 state = 0;
    
    /* only for debug -> needs to be removed */
    while (ret != RIL_AT_SUCCESS)
    {
        ret = RIL_SIM_GetSimState(&state);
        APP_DEBUG("Error\r\n");
        dianostics(ret);
        Ql_Sleep(500);
    }

    if (state == SIM_STAT_NOT_INSERTED)
    {
        APP_DEBUG("SIM_STAT_NOT_INSERTED\r\n");
    }
    else if (state == SIM_STAT_READY)
    {
        APP_DEBUG("SIM_STAT_READY\r\n");
    }
    else if (state == SIM_STAT_PIN_REQ)
    {
        APP_DEBUG("SIM_STAT_PIN_REQ\r\n");
    }
    else if (state == SIM_STAT_PUK_REQ)
    {
        APP_DEBUG("SIM_STAT_PUK_REQ\r\n");
    }
    else if (state == SIM_STAT_PIN2_REQ)
    {
        APP_DEBUG("SIM_STAT_PIN2_REQ\r\n");
    }
    else if (state == SIM_STAT_PUK2_REQ)
    {
        APP_DEBUG("SIM_STAT_PUK2_REQ\r\n");
    }
    else if (state == SIM_STAT_BUSY)
    {
        APP_DEBUG("SIM_STAT_BUSY\r\n");
    }
    else if (state == SIM_STAT_NOT_READY)
    {
        APP_DEBUG("SIM_STAT_NOT_READY\r\n");
    }
    else if (state == SIM_STAT_UNSPECIFIED)
    {
        APP_DEBUG("SIM_STAT_UNSPECIFIED\r\n");
    }
    else
    {
        APP_DEBUG("UNKNOWN BUG\r\n");
    }
}