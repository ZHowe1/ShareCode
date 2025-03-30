/**************************************************************
* Class:: CSC-615-01 Spring 2025
* Name:: Zachary Howe
* Student ID:: 923229694
* Github-Name:: Zhowe1
* Project:: Assignment 3 -  Start Your Motor
*
* File:: timer.h
*
* Description:: H file to handle timer library
*
**************************************************************/
#pragma once

#include <stdint.h>
#include <time.h>

// Create an accurate delay
void delay(uint64_t seconds, uint64_t milliseconds, uint64_t microseconds);

// Recieve a time stamp to keep track of time
struct timespec get_time();

// Create deltatime frame based calcs
double get_deltatime(struct timespec *start);
