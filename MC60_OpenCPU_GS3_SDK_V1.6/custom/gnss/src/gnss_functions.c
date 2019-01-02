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

void	deactivate_gnss(void)
{
	s32 ret;

	ret = RIL_GPS_Open(0);

	if (ret == RIL_AT_SUCCESS)
	{
		APP_DEBUG("%s\r\n","gnss deactivated successfull\0");
	}
	else
	{
		APP_DEBUG("%s\r\n","gnss deactivation failure\0");
	}
}

bool	gnss_read(void)
{
	s32	ret;
	u8	rdBuff[1000];
    u8	item[10];

    Ql_memset(rdBuff, 0x0, sizeof(rdBuff));
    Ql_sprintf(item, "%s", "RMC\0");

	ret = RIL_GPS_Read(item, rdBuff);

	if (ret == QL_RET_OK)
	{
		APP_DEBUG("GNSS data -> %s\r\n", rdBuff);
		return (TRUE);
	}
	else
	{
		APP_DEBUG("%s\r\n", "gnss data failure\0");
		return (FALSE);
	}
}