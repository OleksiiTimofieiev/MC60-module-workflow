#ifdef __IIC_MAIN__

#include "iic_project.h"

void	proc_main_task(s32 taskId)
{
	s32     ret;
	ST_MSG  msg;

	// Register & open UART port
	Ql_UART_Register(UART_PORT1, CallBack_UART_Hdlr, NULL);
	Ql_UART_Open(UART_PORT1, 115200, FC_NONE);

	Ql_UART_Register(UART_PORT2, CallBack_UART_Hdlr, NULL);
	Ql_UART_Open(UART_PORT2, 115200, FC_NONE);

	APP_DEBUG("\r\n<--OpenCPU: IIC TEST!-->\r\n"); 

	while (TRUE)
	{
		Ql_OS_GetMessage(&msg);

		switch (msg.message)
		{
			case MSG_ID_RIL_READY:
			{
				APP_DEBUG("<-- RIL is ready -->\r\n");
				Ql_RIL_Initialize();
				
				i2c_init_and_config();
				xyz_timer_int_and_start();
				break ;
			}
			default:
				break ;
		}
	}
}

s32 	ReadSerialPort(Enum_SerialPort port, /*[out]*/u8* pBuffer, /*[in]*/u32 bufLen)
{
	s32 rdLen = 0;
	s32 rdTotalLen = 0;
	if (NULL == pBuffer || 0 == bufLen)
	{
		return -1;
	}
	Ql_memset(pBuffer, 0x0, bufLen);
	while (1)
	{
		rdLen = Ql_UART_Read(port, pBuffer + rdTotalLen, bufLen - rdTotalLen);
		if (rdLen <= 0)  // All data is read out, or Serial Port Error!
		{
			break;
		}
		rdTotalLen += rdLen;
		// Continue to read...
	}
	
	// APP_DEBUG("Input to the port -> %s\r\n", pBuffer);

	if (rdLen < 0) // Serial Port Error!
	{
		APP_DEBUG("<--Fail to read from port[%d]-->\r\n", port);
		return -99;
	}
	return rdTotalLen;
}

void 	CallBack_UART_Hdlr(Enum_SerialPort port, Enum_UARTEventType msg, bool level, void* customizedPara)
{
	switch (msg)
	{
	case EVENT_UART_READY_TO_READ:
		{
		   s32 totalBytes = ReadSerialPort(port, m_RxBuf_Uart, sizeof(m_RxBuf_Uart));
		   break;
		}
	case EVENT_UART_READY_TO_WRITE:
		break;
	default:
		break;
	}
}

#endif
