#include "general.h"

/* input buffer params */

#define SERIAL_RX_BUFFER_LEN  2048
static  u8  m_RxBuf_Uart[SERIAL_RX_BUFFER_LEN];

u8    *ft_strstr(const u8 *haystack, const u8 *needle)
{
    int i;
    int j;
    int length;

    i = 0;
    if (needle[i] == '\0')
        return ((u8 *)haystack);
    j = 0;
    length = Ql_strlen(needle);
    while (haystack[i])
    {
        while (needle[j] == haystack[i + j])
        {
            if (j == length - 1)
                return ((u8 *)haystack + i);
            j++;
        }
        j = 0;
        i++;
    }
    return (NULL);
}

s32		response_callback(char* line, u32 len, void* userData) // el costello in func;
{
    // APP_DEBUG("Write to the port\r\n");
    Ql_UART_Write(UART_PORT1, (u8*)line, len);

    if (ft_strstr(line, "QDSIM") && ft_strstr(line, "0"))
         *(s32 *)userData = 0;
     else if (ft_strstr(line, "QDSIM") && ft_strstr(line, "1"))
         *(s32 *)userData = 1;


    // APP_DEBUG("line in callback -> %s\r\n", line);
    // APP_DEBUG("input AT -> %d\r\n", *(s32 *)userData);

    if (Ql_RIL_FindLine(line, len, "OK"))
    {  
        return  RIL_ATRSP_SUCCESS;
    }
    // else if (Ql_RIL_FindLine(line, len, "QDSIM"))
    // {
    //     APP_DEBUG("QDSIM found here\r\n");

    //     if (Ql_RIL_FindLine(line, len, "1"))
    //     {
    //         APP_DEBUG("here1\r\n");
    //         *(s32 *)userData = 1;
    //     }
    //     else if (Ql_RIL_FindLine(line, len, "0"))
    //     {
    //         APP_DEBUG("here0\r\n");
    //         *(s32 *)userData = 0;
    //     }
    //      return  RIL_ATRSP_CONTINUE;
    // }
    else if (Ql_RIL_FindLine(line, len, "ERROR"))
    {  
        return  RIL_ATRSP_FAILED;
    }
    else if (Ql_RIL_FindString(line, len, "+CME ERROR"))
    {
        return  RIL_ATRSP_FAILED;
    }
    else if (Ql_RIL_FindString(line, len, "+CMS ERROR:"))
    {
        return  RIL_ATRSP_FAILED;
    }
    return RIL_ATRSP_CONTINUE; //continue wait
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
