#ifdef __IIC_MAIN__

#include "iic_project.h"

static u8 lisbuf[2];

int		i2c_Init(void)
{
	int ret;

	//u32 chnnlNo,PinName pinSCL,PinName pinSDA, u32 IICtype=HW
	ret = Ql_IIC_Init(1, PINNAME_RI, PINNAME_DCD, 1);
	// APP_DEBUG("A%d=%d\n", (s32)__LINE__, ret); 
    if (ret == QL_RET_OK)
    {
        APP_DEBUG("Init success\r\n") 
    }
    else
    {
        APP_DEBUG("Init failure\r\n");
    }
	return ret;
}

int 	i2c_Config(u8 ad) // 032
{
    int ret;

    //u32 chnnlNo, bool isHost, u8 slaveAddr, u32 speed
    ret = Ql_IIC_Config(1, TRUE, ad, 10);
    // APP_DEBUG("A%d=%d\n", (s32)__LINE__, ret);
    if (ret == QL_RET_OK)
    {
        APP_DEBUG("Config success\r\n") 
    }
    else
    {
        APP_DEBUG("Config failure\r\n");
    }
    return ret;
}

u8		lis_RD(u8 reg) // RD data from specified register;
{
	int ret;

	//ret = Ql_IIC_Read(1, LIS_ADDR, lisbuf, 1); //u32 chnnlNo,u8 slaveAddr,u8 *pBuffer,u32 len
	lisbuf[0] = 0;
	// s32 Ql_IIC_Write_Read(u32 chnnlNo,u8 slaveAddr,u8 * pData,u32 wrtLen,u8 * pBuffer,u32 rdLen)
	ret = Ql_IIC_Write_Read(1, LIS_ADDR, &reg, 1, lisbuf, 1); 
	APP_DEBUG("A%d=%d", (s32)__LINE__, ret);
    if (ret == 1)
    {
        APP_DEBUG("RD success\r\n") 
    }
    else
    {
        APP_DEBUG("RD failure\r\n");
    }
	return lisbuf[0];
}

void	lis_WR(u8 reg, u8 data) // configure register
{
	int ret;

	lisbuf[0] = reg;
	lisbuf[1] = data;
	ret = Ql_IIC_Write(1, LIS_ADDR, lisbuf, 2); //u32 chnnlNo,u8 slaveAddr,u8 *pData,u32 len
	APP_DEBUG("A%d=%d", (s32)__LINE__, ret);
}

void    i2c_init_and_config(void)
{
    i2c_Init();
    i2c_Config(0x32);
}

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
                APP_DEBUG("reg value ->%x\n", lis_RD(LIS_WHO_AM_I));
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
