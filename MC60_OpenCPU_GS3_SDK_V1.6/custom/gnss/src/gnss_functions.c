#include "gnss_general.h"

void	activate_gnss(void)
{
	s32 ret;

	ret = RIL_GPS_Open(1);

	if (ret == RIL_AT_SUCCESS)
	{
		APP_DEBUG("%s\r\n","gnss activated successfully");
	}
	else
	{
		APP_DEBUG("%s\r\n","gnss activation failure");
	}
}

void	deactivate_gnss(void)
{
	s32 ret;

	ret = RIL_GPS_Open(0);

	if (ret == RIL_AT_SUCCESS)
	{
		APP_DEBUG("%s\r\n","gnss deactivated successfull");
	}
	else
	{
		APP_DEBUG("%s\r\n","gnss deactivation failure");
	}
}

void	gnss_read(void)
{
	// APP_DEBUG("%s\r\n", "In gnss_read 1");
	s32	ret;
	u8	rdBuff[1000];
    u8	item[10];

	// APP_DEBUG("%s\r\n", "In gnss_read 2");


    Ql_memset(rdBuff, 0x0, sizeof(rdBuff));
    Ql_sprintf(item, "%s", "RMC");

	// APP_DEBUG("%s\r\n", "In gnss_read 3");

    // APP_DEBUG("%s\r\n", item);

    Ql_Sleep(1000); /* necessary to have the GNSS infrastructure fully activated */

	ret = RIL_GPS_Read(item, rdBuff);

	// APP_DEBUG("ret -> %d\r\n", ret);
	// APP_DEBUG("%s\r\n", "In gnss_read 4");

	if (ret == RIL_AT_SUCCESS)
	{
		// APP_DEBUG("%s\r\n", "gnss data received");

		APP_DEBUG("GNSS data -> %s\r\n", rdBuff);

		// APP_DEBUG("%s\r\n", "In gnss_read 5");
	}
	else
	{
		APP_DEBUG("%s\r\n", "gnss data failure");
		// APP_DEBUG("%s\r\n", "In gnss_read 6");

	}
		// APP_DEBUG("%s\r\n", "In gnss_read7");

}