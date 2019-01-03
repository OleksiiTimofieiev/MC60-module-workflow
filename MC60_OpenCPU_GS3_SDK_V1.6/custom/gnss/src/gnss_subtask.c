#include "gnss_general.h"

void	proc_subtask1(s32 TaskId)
{
    ST_MSG 	subtask1_msg;

    while (TRUE)
    {    
        Ql_OS_GetMessage(&subtask1_msg);

        switch(subtask1_msg.message)
        {
        	case INITIAL_GNSS:
        	{
        		init_gnss();
        		break ;
        	}
            default:
                break;
        }
    }
}