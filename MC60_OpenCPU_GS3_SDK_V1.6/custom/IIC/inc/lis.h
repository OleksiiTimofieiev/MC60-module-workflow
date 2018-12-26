#ifndef __LIS_H__
#define __LIS_H__

/* LIS3DH Register Map (Please refer to LIS3DH Specifications) */
#define LIS_STATUS_REG_AUX 0x07
#define LIS_OUT_ADC1_L 0x08 
#define LIS_OUT_ADC1_H 0x09
#define LIS_OUT_ADC2_L 0x0A
#define LIS_OUT_ADC2_H 0x0B
#define LIS_OUT_ADC3_L 0x0C
#define LIS_OUT_ADC3_H 0x0D

#define LIS_INT_COUNTER_REG 0x0E
#define LIS_WHO_AM_I 0x0F // id of device
#define LIS_TEMP_CFG_REG 0x1F
#define LIS_CTRL_REG1 0x20 // XYZ enable by default;
#define LIS_CTRL_REG2 0x21 // filtering
#define LIS_CTRL_REG3 0x22 // interrupt configuration
#define LIS_CTRL_REG4 0x23 // block data update, endian,  
#define LIS_CTRL_REG5 0x24 // FIFO enable, default -> disable (bypass mode);
#define LIS_CTRL_REG6 0x25 // additional interrupts;
#define LIS_REFERENCE 0x26 // maybe used for magic number ;)
#define LIS_STATUS_REG2 0x27 // ZYXDA, ZDA, YDA;
#define LIS_OUT_X_L 0x28 // read address for any digital block type
#define LIS_OUT_X_H 0x29 // read address for any digital block type
#define LIS_OUT_Y_L 0x2A // read address for any digital block type
#define LIS_OUT_Y_H 0x2B // read address for any digital block type
#define LIS_OUT_Z_L 0x2C // read address for any digital block type
#define LIS_OUT_Z_H 0x2D // read address for any digital block type
#define LIS_FIFO_CTRL_REG 0x2E // FIFO mode selection
#define LIS_FIFO_SRC_REG 0x2F // FIFO status read register;
#define LIS_INT1_CFG 0x30 // low/high recognition config;
#define LIS_INT1_SOURCE 0x31 // low / high read;
#define LIS_INT1_THS 0x32
#define LIS_INT1_DURATION 0x33

#define LIS_CLICK_CFG 0x38
#define LIS_CLICK_SRC 0x39
#define LIS_CLICK_THS 0x3A
#define LIS_TIME_LIMIT 0x3B
#define LIS_TIME_LATENCY 0x3C
#define LIS_TIME_WINDOW 0x3D


#define INT_YES 0x10  //int1 or int2 interupt always active (for reg3, reg6)
#define INT_NO 0x00  //int1 or int2 disable(for reg3, reg6)
#define INT_LOW 0x02 //interupt int1+int2 active low (for reg6)
#define INT_WAKE 0x40 //wake interupt on int1 or int2 (for reg3, reg6)
#define INT_LATCH 0x08 //interupt latched (for reg5)

/* device address */
#define LIS_ADDR 0x32

#endif
