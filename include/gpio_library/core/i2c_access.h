/**************************************************************
 * Class:: CSC-615-01 Spring 2025
 * Name:: Zachary Howe, Yu-Ming Chen, Aditya Sharma, James Nguyen
 * Student ID:: 923229694, 923313947, 917586584, 922182661
 * Github-Name:: Zhowe1
 * Project:: Assignment 5 - RGB Sensor
 *
 * File:: i2c_access.h
 *
 * Description:: Connecting the i2c to the library
 * 
 **************************************************************/
#ifndef I2C_ACCESS_H
#define I2C_ACCESS_H

#include <stdint.h>

#define DEV_HARDWARE_I2C_DEBUG 0
#if DEV_HARDWARE_I2C_DEBUG
#define DEV_HARDWARE_I2C_Debug(__info, ...) printf("Debug: " __info, ##__VA_ARGS__)
#else
#define DEV_HARDWARE_I2C_Debug(__info, ...)
#endif

/**
 * @brief Struct for storing i2c data
 */
typedef struct i2c_data
{
    int fd;
    uint16_t address;
} i2c_data;

/**
 * @brief Struct for storing i2c path
 */
typedef struct i2c_path
{
    char i2c_driver_path[255];
    int perms;
} i2c_path;

/**
 * @brief Gain access to the i2c driver
 *
 * @return i2c_data* struct
 */
i2c_data *i2c_open_driver(void);

/**
 * @brief Sets address for the TCS34725 RGB sensor.
 *
 * @param address uint8_t address
 * @param data i2c_data* struct
 * @return 0 if successful, -1 if failed
 */
int i2c_set_target_address(uint8_t address, i2c_data *data);

/**
 * @brief Write to the TCS34725 RGB sensor via i2c.
 *
 * @param buf buffer to be written
 * @param len length of buffer
 * @param data i2c_data* struct
 * @return 0 if successful, -1 if failed
 */
int i2c_write(const char *buf, uint32_t len, i2c_data *data);

/**
 * @brief Read from the TCS34725 RGB sensor via i2c.
 *
 * @param reg register to be read
 * @param buf buffer to be read into
 * @param len length of buffer
 * @param data i2c_data* struct
 * @return 0 if successful, -1 if failed
 */
int i2c_read(uint8_t reg, char *buf, uint32_t len, i2c_data *data);

/**
 * @brief Close access & cleanup of i2c driver
 *
 * @param data i2c_data* struct to be cleaned
 */
void hardware_i2c_clean(i2c_data *data);

#endif // I2C_ACCESS_H