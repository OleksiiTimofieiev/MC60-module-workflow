#include "gnss_general.h"

void	activate_gnss(void)
{
	s32 ret;

	ret = RIL_GPS_Open(1);

	if (ret == RIL_AT_SUCCESS)
	{
		APP_DEBUG("%s\r\n","gnss activated successfully\0");
	}
	else
	{
		APP_DEBUG("%s\r\n","gnss activation failure\0");
	}
}

void	set_hot_start(void)
{
	char	strAT[200];
	s32		ret;

	u8 cmdType = 0;
	u8 *cmdStr  = "$PMTK101*32\0";

	Ql_memset( strAT, 0, sizeof(strAT) );
	Ql_sprintf( strAT, "AT+QGNSSCMD=%d,\"%s\"\r\n", cmdType, cmdStr);

	ret = Ql_RIL_SendATCmd( strAT, Ql_strlen(strAT), NULL, NULL, 0 );

	if (ret == RIL_AT_SUCCESS)
	{
		APP_DEBUG("%s\r\n", "hot start activated\0")
	}
	else
	{
		APP_DEBUG("%s\r\n", "hot start error\0");
	}
}

void	deactivate_gnss(void)
{
	s32 ret;

	ret = RIL_GPS_Open(0);

	if (ret == RIL_AT_SUCCESS)
	{
		APP_DEBUG("%s\r\n","gnss deactivated successfully\0");
	}
	else
	{
		APP_DEBUG("%s\r\n","gnss deactivation failure\0");
	}
}

bool	gnss_read(void)
{
	s32	ret;
	u8	rdBuff[1000] = {"\0"};
    u8	item[10] = {"\0"};

    Ql_strncpy(item, "RMC", 3);

	ret = RIL_GPS_Read(item, rdBuff);

	if (ret == RIL_AT_SUCCESS)
	{
		APP_DEBUG("%s\r\n", rdBuff);

		if (Ql_strstr(rdBuff, "N*\0"))
		{
			return (FALSE);
		}
		else
		{
			return (TRUE);
		}
	}
	else
	{
		return (FALSE);
	}
}

void	init_gnss(void)
{
	activate_gnss();
    set_hot_start();
    timer_register_and_start();
}