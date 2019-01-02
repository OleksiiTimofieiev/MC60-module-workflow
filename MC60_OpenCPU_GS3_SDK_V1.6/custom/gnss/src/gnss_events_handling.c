#include "gnss_general.h"

// typedef enum {
// 	EVENT_FLAG0 = 0x00000001, <-> start timer for the required interval;
// 	EVENT_FLAG1 = 0x00000002, 
// 	EVENT_FLAG2 = 0x00000004,
// 	EVENT_FLAG3 = 0x00000008,
// 	EVENT_FLAG4 = 0x00000010,
// 	EVENT_FLAG5 = 0x00000020,
// 	EVENT_FLAG6 = 0x00000040,
// 	EVENT_FLAG7 = 0x00000080,
// 	EVENT_FLAG8 = 0x00000100,
// 	EVENT_FLAG9 = 0x00000200,
// 	EVENT_FLAG_END
// }Enum_EventFlag;

void	gnss_events_processing(u32	gnss_status)
{
	s32		event_wait_status;

	if (!(event_wait_status = Ql_OS_WaitEvent(gnss_status, EVENT_FLAG0)))
   	{
   		// APP_DEBUG("start timer\r\n");
   		timer_GNSS_check_start();
   	}
}