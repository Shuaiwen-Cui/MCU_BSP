#ifndef __IMPU6050_H
#define __IMPU6050_H
#include "main.h"
#include "i2c.h"

 
#define MPU6050_I2C      		hi2c1
#define MPU6050_ADDR     		0xD0   
#define I2C_TimeOut  			100

/* MPU6050 internal register addresses */
#define MPU_SAMPLE_RATE_REG		0X19	// Sample rate divider
#define MPU_GYRO_CFG_REG		0X1B	// Gyroscope configuration register
#define MPU_ACCEL_CFG_REG		0X1C	// Accelerometer configuration register
#define MPU_ACCEL_XOUTH_REG		0X3B	// Accelerometer value, X-axis high byte register
#define MPU_TEMP_OUTH_REG		0X41	// Temperature value high byte register
#define MPU_GYRO_XOUTH_REG		0X43	// Gyroscope value, X-axis high byte register
#define MPU_PWR_MGMT1_REG		0X6B	// Power management register 1
#define MPU_DEVICE_ID_REG		0X75	// Device ID register

uint8_t MPU6050_Init(I2C_HandleTypeDef *I2Cx);
float MPU_Get_Temperature(void);
uint8_t MPU_Get_RAW_Gyroscope(int16_t *gx,int16_t *gy,int16_t *gz);
uint8_t MPU_Get_RAW_Accelerometer(int16_t *ax,int16_t *ay,int16_t *az);

/*
MPU6050 internal register addresses
#define MPU_SELF_TESTX_REG		0X0D	// Self-test register X
#define MPU_SELF_TESTY_REG		0X0E	// Self-test register Y
#define MPU_SELF_TESTZ_REG		0X0F	// Self-test register Z
#define MPU_SELF_TESTA_REG		0X10	// Self-test register A
#define MPU_SAMPLE_RATE_REG		0X19	// Sample rate divider
#define MPU_CFG_REG				0X1A	// Configuration register
#define MPU_GYRO_CFG_REG		0X1B	// Gyroscope configuration register
#define MPU_ACCEL_CFG_REG		0X1C	// Accelerometer configuration register
#define MPU_MOTION_DET_REG		0X1F	// Motion detection threshold setting register
#define MPU_FIFO_EN_REG			0X23	// FIFO enable register
#define MPU_I2CMST_CTRL_REG		0X24	// I2C master control register
#define MPU_I2CSLV0_ADDR_REG	0X25	// I2C slave 0 device address register
#define MPU_I2CSLV0_REG			0X26	// I2C slave 0 data address register
#define MPU_I2CSLV0_CTRL_REG	0X27	// I2C slave 0 control register
#define MPU_I2CSLV1_ADDR_REG	0X28	// I2C slave 1 device address register
#define MPU_I2CSLV1_REG			0X29	// I2C slave 1 data address register
#define MPU_I2CSLV1_CTRL_REG	0X2A	// I2C slave 1 control register
#define MPU_I2CSLV2_ADDR_REG	0X2B	// I2C slave 2 device address register
#define MPU_I2CSLV2_REG			0X2C	// I2C slave 2 data address register
#define MPU_I2CSLV2_CTRL_REG	0X2D	// I2C slave 2 control register
#define MPU_I2CSLV3_ADDR_REG	0X2E	// I2C slave 3 device address register
#define MPU_I2CSLV3_REG			0X2F	// I2C slave 3 data address register
#define MPU_I2CSLV3_CTRL_REG	0X30	// I2C slave 3 control register
#define MPU_I2CSLV4_ADDR_REG	0X31	// I2C slave 4 device address register
#define MPU_I2CSLV4_REG			0X32	// I2C slave 4 data address register
#define MPU_I2CSLV4_DO_REG		0X33	// I2C slave 4 write data register
#define MPU_I2CSLV4_CTRL_REG	0X34	// I2C slave 4 control register
#define MPU_I2CSLV4_DI_REG		0X35	// I2C slave 4 read data register
#define MPU_I2CMST_STA_REG		0X36	// I2C master status register
#define MPU_INTBP_CFG_REG		0X37	// Interrupt/bypass setting register
#define MPU_INT_EN_REG			0X38	// Interrupt enable register
#define MPU_INT_STA_REG			0X3A	// Interrupt status register
#define MPU_ACCEL_XOUTH_REG		0X3B	// Accelerometer value, X-axis high byte register
#define MPU_ACCEL_XOUTL_REG		0X3C	// Accelerometer value, X-axis low byte register
#define MPU_ACCEL_YOUTH_REG		0X3D	// Accelerometer value, Y-axis high byte register
#define MPU_ACCEL_YOUTL_REG		0X3E	// Accelerometer value, Y-axis low byte register
#define MPU_ACCEL_ZOUTH_REG		0X3F	// Accelerometer value, Z-axis high byte register
#define MPU_ACCEL_ZOUTL_REG		0X40	// Accelerometer value, Z-axis low byte register
#define MPU_TEMP_OUTH_REG		0X41	// Temperature value high byte register
#define MPU_TEMP_OUTL_REG		0X42	// Temperature value low byte register
#define MPU_GYRO_XOUTH_REG		0X43	// Gyroscope value, X-axis high byte register
#define MPU_GYRO_XOUTL_REG		0X44	// Gyroscope value, X-axis low byte register
#define MPU_GYRO_YOUTH_REG		0X45	// Gyroscope value, Y-axis high byte register
#define MPU_GYRO_YOUTL_REG		0X46	// Gyroscope value, Y-axis low byte register
#define MPU_GYRO_ZOUTH_REG		0X47	// Gyroscope value, Z-axis high byte register
#define MPU_GYRO_ZOUTL_REG		0X48	// Gyroscope value, Z-axis low byte register
#define MPU_I2CSLV0_DO_REG		0X63	// I2C slave 0 data register
#define MPU_I2CSLV1_DO_REG		0X64	// I2C slave 1 data register
#define MPU_I2CSLV2_DO_REG		0X65	// I2C slave 2 data register
#define MPU_I2CSLV3_DO_REG		0X66	// I2C slave 3 data register
#define MPU_I2CMST_DELAY_REG	0X67	// I2C master delay management register
#define MPU_SIGPATH_RST_REG		0X68	// Signal path reset register
#define MPU_MDETECT_CTRL_REG	0X69	// Motion detection control register
#define MPU_USER_CTRL_REG		0X6A	// User control register
#define MPU_PWR_MGMT1_REG		0X6B	// Power management register 1
#define MPU_PWR_MGMT2_REG		0X6C	// Power management register 2
#define MPU_FIFO_CNTH_REG		0X72	// FIFO count register high byte
#define MPU_FIFO_CNTL_REG		0X73	// FIFO count register low byte
#define MPU_FIFO_RW_REG			0X74	// FIFO read/write register
#define MPU_DEVICE_ID_REG		0X75	// Device ID register
*/


#endif /* __IMPU6050_H */