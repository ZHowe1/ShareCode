/**************************************************************
 * Class:: CSC-615-01 Spring 2025
 * Name:: Zachary Howe, Yu-Ming Chen, Aditya Sharma, James Nguyen
 * Student ID:: 923229694, 923313947, 917586584, 922182661
 * Github-Name:: Zhowe1
 * Project:: Assignment 5 - RGB Sensor
 *
 * File:: timer.h
 *
 * Description:: H file to handle timer library
 * 
 **************************************************************/
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <time.h>

/**
 * @brief Delay function
 *
 * @param seconds seconds to delay
 * @param milliseconds milliseconds to delay
 * @param microseconds microseconds to delay
 */
void delay(uint64_t seconds, uint64_t milliseconds, uint64_t microseconds);

/**
 * @brief Get the time
 *
 * @return struct timespec time
 */
struct timespec get_time();

/**
 * @brief Get the deltatime
 *
 * @note *** This function is not used in the project. ***
 *
 * @param start start time
 * @return pretty obvious
 */
double get_deltatime(struct timespec *start);
#endif // TIMER_H