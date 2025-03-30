/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Zachary Howe
* Student ID:: 923229694
* Github-Name:: Zhowe1
* Project:: Assignment 3 -  Start Your Motor
*
* File:: motor_config.h
*
* Description:: config for the motor and pca9865
*
**************************************************************/

#pragma once

#include <stdint.h>

#define UBYTE   uint8_t
#define UWORD   uint16_t

/*
* Creates the gpio mmap
*/
int motor_init(void);

/*
* Initialize the GPIO pins
*/
void motor_gpio_mode(UWORD pin, UWORD mode);

/*
* Wrapper for gpio
*/
void motor_write(UWORD pin, UBYTE value);
int motor_read(UWORD pin);
void motor_delay_ms(int milliseconds);

/*
* Wrapper for i2c_access
*/
int motor_i2c_open(UWORD address);
void motor_i2c_write_byte(uint8_t cmd, uint8_t value);
uint8_t motor_i2c_read_byte(UBYTE cmd);
uint16_t motor_i2c_read_word(UBYTE cmd);

/*
* Cleans the driver struct and the gpio mmap
*/
void motor_exit(void);
