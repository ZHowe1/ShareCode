/**************************************************************
 * Class:: CSC-615-01 Spring 2025
 * Name:: Zachary Howe, Yu-Ming Chen, Aditya Sharma, James Nguyen
 * Student ID:: 923229694, 923313947, 917586584, 922182661
 * Github-Name:: Zhowe1
 * Project:: Assignment 5 - RGB Sensor
 *
 * File:: pins.h
 *
 * Description:: H file for the gpio pin connection
 * 
 **************************************************************/
#ifndef PINS_H
#define PINS_H

typedef struct
{
    int protection;
    int flags;
    char path[100];
    int location;
    int perms;
} MMap_Config;

/**
 * @brief Initialize the mmap
 *
 * @param config MMap_Config struct
 * @param gpio_map void** pointer to the gpio map
 * @return volatile unsigned int* pointer to the gpio map
 */
volatile unsigned int *init_io(MMap_Config config, void **gpio_map);

/**
 * @brief Set pins to input or output
 *
 * @param gpio volatile unsigned int* pointer to the gpio map
 * @param pin int pin number
 * @return int 0 if successful, -1 if failed
 */
int set_output(volatile unsigned int *gpio, int pin);
int set_input(volatile unsigned int *gpio, int pin);

/**
 * @brief Write to the pins
 *
 * @note write_pins is used to write to multiple pins at once.
 *
 * @param gpio volatile unsigned int* pointer to the gpio map
 * @param pins int* pointer to the pins
 * @param num_pins int number of pins
 * @param state int state
 * @return 0 if successful, -1 if failed
 */
int write_pins(volatile unsigned int *gpio, int *pins, int num_pins, int state);
int write_pin(volatile unsigned int *gpio, int pin, int state);

/**
 * @brief Read the pins
 *
 * @note read_pins is used to read the state of multiple pins at once.
 *
 * @param gpio volatile unsigned int* pointer to the gpio map
 * @param pins_val int* pointer to the pins values
 * @param pins int* pointer to the pins
 * @param num_pins int number of pins
 * @return 0 if successful, -1 if failed
 */
int *read_pins(volatile unsigned int *gpio, int *pins_val, int *pins, int num_pins);
int read_pin(volatile unsigned int *gpio, int pin);

/**
 * @brief Clean and unmmap
 *
 * @param gpio_mmap void* pointer to the gpio map
 * @return int 0 if successful, -1 if failed
 */
int clean(void *gpio_mmap);

/**
 * @note ***This function is not used in the project.***
 *
 * @brief Set up default signals for cleanup
 *
 * @return int 0 if successful, -1 if failed
 */
int set_signals();

#endif // PINS_H