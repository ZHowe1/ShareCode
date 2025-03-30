/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Zachary Howe
* Student ID:: 923229694
* Github-Name:: Zhowe1
* Project:: Assignment 3 -  Start Your Motor
*
* File:: i2c_access.h
*
* Description:: Connecting the i2c to the library
*
**************************************************************/

#pragma once

#include <stdint.h>


#define DEV_HARDWARE_I2C_DEBUG 0
#if DEV_HARDWARE_I2C_DEBUG
#define DEV_HARDWARE_I2C_Debug(__info,...) printf("Debug: " __info,##__VA_ARGS__)
#else
#define DEV_HARDWARE_I2C_Debug(__info,...)
#endif

/*
* Used to keep track of pca or other devices 
* Multiple at a time with threading.
*/
typedef struct i2c_data 
{
    int fd;
    uint16_t address;
} i2c_data;

/*
* Path required to open driver
* with permissions.
*/
typedef struct i2c_path
{
    char i2c_driver_path[255];
    int perms;
}i2c_path;

/*
* Gain access to the i2c driver
*/
i2c_data* i2c_open_driver(void);

/*
* Sets address for the particular chip.
* allows multiple targets to be set for one
* controller.
*/
int i2c_set_target_address(uint8_t address, i2c_data* data);

// Write and read pins via the driver
int i2c_write(const char* buf, uint32_t len, i2c_data* data);
int i2c_read(uint8_t reg, char* buf, uint32_t len, i2c_data* data);

/*
* Close access to i2c driver
*/
void hardware_i2c_clean(i2c_data* data);
