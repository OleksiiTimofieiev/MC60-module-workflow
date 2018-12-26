#include "iic_project.h"

static  u8 lisbuf[2];

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

int 	i2c_Config(u8 ad) // 032 in our case;
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
	// APP_DEBUG("A%d=%d\r\n", (s32)__LINE__, ret);
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

void	lis_WR(u8 reg, u8 data) // configure register;
{
	int ret;

	lisbuf[0] = reg;
	lisbuf[1] = data;
	ret = Ql_IIC_Write(1, LIS_ADDR, lisbuf, 2); //u32 chnnlNo,u8 slaveAddr,u8 *pData,u32 len
	APP_DEBUG("A%d=%d", (s32)__LINE__, ret);
}

void    power_on_via_reg(void) // power register activate;
{
	lis_WR(LIS_CTRL_REG1, 0x67);
}

void    i2c_init_and_config(void)
{
	i2c_Init();
	i2c_Config(0x32);
	power_on_via_reg();
}