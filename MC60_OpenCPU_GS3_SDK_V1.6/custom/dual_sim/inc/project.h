#ifndef __PROJECT_H__
#define __PROJECT_H__

/* core funcs of the project */

bool    network_test(void);

void    init_and_start_dual_sim_diagnostics_timer(void);
void    get_list_of_supported_slots(void);
u8	    get_active_slot(void);
void    change_active_slot(u8 slot);
void    get_SIM_state(void);

void	CallBack_UART_Hdlr(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void* customizedPara);
s32		ReadSerialPort(Enum_SerialPort port, /*[out]*/u8* pBuffer, /*[in]*/u32 bufLen);
s32		response_callback(char* line, u32 len, void* userData);

#endif