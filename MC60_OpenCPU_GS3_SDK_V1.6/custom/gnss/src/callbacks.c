#include "gnss_general.h"

#define SERIAL_RX_BUFFER_LEN  2048
static  u8  m_RxBuf_Uart[SERIAL_RX_BUFFER_LEN];

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
		   /*s32 totalBytes = */ReadSerialPort(port, m_RxBuf_Uart, sizeof(m_RxBuf_Uart));
		   break;
		}
	case EVENT_UART_READY_TO_WRITE:
		break;
	default:
		break;
	}
}