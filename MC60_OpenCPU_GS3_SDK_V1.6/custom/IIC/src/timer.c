#include "iic_project.h"

#define	REPEAT          25
#define	XYZ		        0x104

void    xyz(u32 timerId, void* param) // use FIFO ?
{
    u8      raw_data[6] = {0};
    s16     pre_processed_data[3] = {0};
    float   processed_data[3] = {0};

    u8      aux_status = lis_RD(LIS_STATUS_REG_AUX);

    if (aux_status & STATUS_AUX_321DA)
    {
        raw_data[0] = lis_RD(LIS_OUT_X_H);
        raw_data[1] = lis_RD(LIS_OUT_X_L);

        raw_data[2] = lis_RD(LIS_OUT_Y_H);
        raw_data[3] = lis_RD(LIS_OUT_Y_L);
        
        raw_data[4] = lis_RD(LIS_OUT_Z_H);
        raw_data[5] = lis_RD(LIS_OUT_Z_L);

        pre_processed_data[0] = (( ((s16) ( (raw_data[0]) << 8) | raw_data[1]) ) /* >> 4 */);
        pre_processed_data[1] = (( ((s16) ( (raw_data[2]) << 8) | raw_data[3]) ) /* >> 4 */);
        pre_processed_data[2] = (( ((s16) ( (raw_data[4]) << 8) | raw_data[5]) ) /* >> 4 */);

        u8  i = 0;

        while (i < 3)
        {
            processed_data[i] = pre_processed_data[i] * LA_So_2g;
            i++;
        }

        APP_DEBUG("processed_data[0] -> %f\r\n", processed_data[0]);
        APP_DEBUG("processed_data[1] -> %f\r\n", processed_data[1]);
        APP_DEBUG("processed_data[2] -> %f\r\n", processed_data[2]);
    }
}

void    xyz_timer_int_and_start(void)
{
	s32		ret;
    // u32 	repeat_interval =  minutes_to_milliseconds_converter(REPEAT_PERIOD);
    
    ret = Ql_Timer_Register(XYZ, xyz, NULL);
    if(ret < 0)
    {
        APP_DEBUG("<--failed!!, Ql_Timer_Register: timer(%d) fail -->\r\n", XYZ);
    }
    APP_DEBUG("<--Register: timerId\r\n"); 
 
    ret = Ql_Timer_Start(XYZ, REPEAT, TRUE);
    if(ret < 0)
    {
        APP_DEBUG("<--failed!! stack timer Ql_Timer_Start ret=%d-->\r\n",ret);        
    }
    APP_DEBUG("<--dual_sim timer start\r\n");
}
