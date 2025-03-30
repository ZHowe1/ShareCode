/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Zachary Howe
* Student ID:: 923229694
* Github-Name:: Zhowe1
* Project:: Assignment 3 -  Start Your Motor
*
* File:: pins.h
*
* Description:: H file for the gpio pin connection
**************************************************************/
#pragma once

typedef struct 
{
    int protection;
    int flags;
    char path[100];
    int location;
    int perms;
} MMap_Config;


// Start the mmap
volatile unsigned int* init_io(MMap_Config config, void** gpio_map);

// Set pins to input or output
int set_output(volatile unsigned int* gpio, int pin);
int set_input(volatile unsigned int* gpio, int pin);


/* 
*  Set the pin(s) from on to off
*  or vice versa. (write)
*/

int write_pins(volatile unsigned int* gpio, int* pins, int num_pins, int state);
int write_pin(volatile unsigned int* gpio, int pin, int state);

/* 
*  Get the pin(s) data. (read) 
*/

int* read_pins(volatile unsigned int* gpio, int* pins_val ,int* pins, int num_pins);
int read_pin(volatile unsigned int* gpio, int pin);

/*
*  clean and unmmap
*/

int clean(void* gpio_mmap);

/*
* Set up default signals for cleanup
*/

int set_signals();

