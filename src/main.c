/**************************************************************
 * Class:: CSC-615-01 Spring 2025
 * Name:: Zachary Howe, Yu-Ming Chen, Aditya Sharma, James Nguyen
 * Student ID:: 923229694, 923313947, 917586584, 922182661
 * Github-Name:: Zhowe1
 * Project:: Assignment 5 - RGB Sensor
 *
 * File:: main.c
 *
 * Description:: Uses our self defined library to read the RGB sensor
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <math.h>

#include "gpio_library/core/pins.h"
#include "gpio_library/core/timer.h"
#include "gpio_library/core/i2c_access.h"
#include "gpio_library/TCS34725/tcs_controller.h"
#include "gpio_library/TCS34725/color_converter.h"

#define BCM2708_PERI_BASE 0x20000000
#define GPIO_BASE (BCM2708_PERI_BASE + 0x200000)

volatile unsigned int *gpio = NULL;
void *gpio_mmap = NULL;
i2c_data *data;

void cleanup(int sig);
void setup_gpio(void);
void prompt_led_toggle(void);
void setup_i2c_sensor(void);
void main_loop(void);

void cleanup(int sig)
{
    write_pin(gpio, 14, 0); // Turn off LED before exit
    clean(gpio_mmap);
    hardware_i2c_clean(data);
    printf("\nThanks for using the RGB sensor...\n");
    exit(0);
}

void setup_gpio(void)
{
    MMap_Config config = {
        .protection = PROT_READ | PROT_WRITE,
        .flags = MAP_SHARED,
        .location = GPIO_BASE,
        .perms = O_RDWR | O_SYNC
    };
    memcpy(config.path, "/dev/gpiomem", 13);

    gpio = init_io(config, &gpio_mmap);
    if (!gpio)
    {
        printf("Failed to map GPIO memory.\n");
        exit(-1);
    }
    set_output(gpio, 14);
}

void prompt_led_toggle(void)
{
    char ch;
    while (1)
    {
        printf("\n ** LED ON or OFF? (Y/N) **\n");
        scanf(" %c", &ch);
        while (getchar() != '\n'); // Clear buffer

        if (ch == 'Y' || ch == 'y')
        {
            write_pin(gpio, 14, 1);
            printf(" LED turned ON \n");
            break;
        }
        else if (ch == 'N' || ch == 'n')
        {
            write_pin(gpio, 14, 0);
            printf(" LED turned OFF \n");
            break;
        }
        else
        {
            printf(" Invalid input! \n");
        }
    }
}

void setup_i2c_sensor(void)
{
    data = i2c_open_driver();
    if (rgb_init(data) < 0)
    {
        printf("i2c failed...\n");
    }
    else
    {
        printf("i2c complete...\n");
    }

    set_timing(data, 250);  // Integration time
    set_gain(data, GAIN_16X);  // Gain level
}

void main_loop(void)
{
    rgb_color color;
    color_result result;

    while (1)
    {
        color = sense_color(data);
        if (color.is_valid > 0)
        {
            result = convert_color(color.red, color.green, color.blue, color.clear, 1);
            printf("Hex: %s\n", result.hex);
            printf("Color Name: %s\n", result.color_name);
            printf("Mix: %u, %u, %u\n", color.red, color.green, color.blue);
            printf("Clear value: %u\n", color.clear);
            printf("Confidence: %.2f%%\n\n", result.confidence * 100);
        }
        else
        {
            printf("Invalid color data\n");
        }

        delay(0, 1000, 0);
    }
}

int main()
{
    signal(SIGINT, cleanup);
    setup_gpio();
    prompt_led_toggle();
    delay(0, 500, 0);
    setup_i2c_sensor();
    main_loop();
    return 0;
}
