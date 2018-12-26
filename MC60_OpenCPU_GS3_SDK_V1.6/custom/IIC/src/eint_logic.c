// #include "iic_project.h"

// #define PIN_INTR    PINNAME_DTR

// void    callback_eint_handle(Enum_PinName eintPinName, Enum_PinLevel pinLevel, void* customParam);

// double  get_magnitude(float *processed_data)
// {
//     double     sum = 0;
//     double     result = 0;
//     u8         i = 0;

//     while (i < 3)
//         sum += pow(processed_data[i++], 2);
//     result = sqrt(sum);
//     return (result);
// }

// void    xyz(void) // use FIFO ?
// {
//     u8      raw_data[6] = {0};
//     s16     pre_processed_data[3] = {0};
//     float   processed_data[3] = {0};

//     u8      aux_status = lis_RD(0x27);

//  //   if (aux_status & 0x05)
//   //  {
//         raw_data[0] = lis_RD(LIS_OUT_X_H);
//         raw_data[1] = lis_RD(LIS_OUT_X_L);

//         raw_data[2] = lis_RD(LIS_OUT_Y_H);
//         raw_data[3] = lis_RD(LIS_OUT_Y_L);
        
//         raw_data[4] = lis_RD(LIS_OUT_Z_H);
//         raw_data[5] = lis_RD(LIS_OUT_Z_L);

//         pre_processed_data[0] = (( ((s16) ( (raw_data[0]) << 8) | raw_data[1]) ) /* >> 4 */);
//         pre_processed_data[1] = (( ((s16) ( (raw_data[2]) << 8) | raw_data[3]) ) /* >> 4 */);
//         pre_processed_data[2] = (( ((s16) ( (raw_data[4]) << 8) | raw_data[5]) ) /* >> 4 */);

//         u8  i = 0;

//         while (i < 3)
//         {
//             processed_data[i] = pre_processed_data[i] * LA_So_2g;
//             i++;
//         }

//         APP_DEBUG("processed_data[0] -> %f\r\n", processed_data[0]);
//         APP_DEBUG("processed_data[1] -> %f\r\n", processed_data[1]);
//         APP_DEBUG("processed_data[2] -> %f\r\n", processed_data[2]);

//         APP_DEBUG("square root -> %f\r\n", get_magnitude(processed_data));

//         lis_RD(0x31); // why ?
//     //}
// }

// void    register_and_init_EINT(void)
// {   
//     s32 ret;

//     ret = Ql_EINT_Register(PIN_INTR, callback_eint_handle, NULL);    
//     if(ret != 0)
//     {
//         APP_DEBUG("<--OpenCPU: Ql_EINT_RegisterFast fail.-->\r\n"); 
//         return;    
//     }
//     APP_DEBUG("<--OpenCPU: Ql_EINT_RegisterFast OK.-->\r\n"); 
        
//     ret = Ql_EINT_Init(PIN_INTR, EINT_LEVEL_TRIGGERED, 0, 5, 1); // ?: automask
//     if(ret != 0)
//     {
//         APP_DEBUG("<--OpenCPU: Ql_EINT_Init fail.-->\r\n");
//         return ;
//     }
//     APP_DEBUG("<--OpenCPU: Ql_EINT_Init OK.-->\r\n"); 
// }

// void    callback_eint_handle(Enum_PinName eintPinName, Enum_PinLevel pinLevel, void* customParam)
// {
//     s32 ret;

//     //mask the specified EINT pin.
//     Ql_EINT_Mask(PIN_INTR); // mask level;
    
//     APP_DEBUG("<--Eint callback: pin(%d), levle(%d)-->\r\n", eintPinName, pinLevel);

//     ret = Ql_EINT_GetLevel(eintPinName);

//     //if (ret == 0)
//         xyz();
//     APP_DEBUG("<--Get Level, pin(%d), levle(%d)-->\r\n", eintPinName, ret);
    
//     //unmask the specified EINT pin
//     Ql_EINT_Unmask(PIN_INTR);
// }
