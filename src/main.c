#include "gpio_library/core/pins.h"
#include "gpio_library/core/timer.h"

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

#define BCM2708_PERI_BASE  0x20000000
#define GPIO_BASE      (BCM2708_PERI_BASE + 0x200000)

#define AIN1  1
#define AIN2  2
#define PWMA  0

typedef struct {
    _Atomic int* sensor;
    volatile unsigned int* gpio;
    uint8_t pin;
} sensor_data;

jmp_buf close_buf; 

volatile unsigned int* gpio = NULL;
void* gpio_mmap = NULL;

_Atomic int is_sensing = 1;
_Atomic int thread_count = 0;

void signal_handler(int sig)
{
  longjmp(close_buf, sig);  
}

void* sensor(void* data)
{
    // Make the data readable
    sensor_data* thread_data = (sensor_data*) data;
    int pin_data = 0;
    while(is_sensing)
    {
        delay(0,10,0);

        pin_data = read_pin(thread_data->gpio, thread_data->pin);
        atomic_store(thread_data->sensor, pin_data);
    }

    atomic_fetch_add(&thread_count, 1);

    return NULL;
}

int main()
{
    // Set up atomic sening data
    _Atomic int ir_sensor = 0;
    _Atomic int line_sensor = 0;


    // Set up gpio mmap
    MMap_Config config;
    config.protection = PROT_READ | PROT_WRITE;
    config.flags = MAP_SHARED;
    memcpy(config.path, "/dev/gpiomem", 13);
    config.location = GPIO_BASE;
    config.perms = O_RDWR|O_SYNC;

    gpio = init_io(config, &gpio_mmap);
    if(!gpio)
    {
        printf("Failed to map GPIO memory.\n");
        return -1;
    }

    if(set_input(gpio, 27) != 0)
    {
        printf("Failed to get pin 27!\n");
        clean(gpio_mmap);
        return -1;
    }

    if(set_input(gpio, 4) != 0)
    {
        printf("Failed to get pin 4!\n");
        clean(gpio_mmap);
        return -1;
    }

    // Set up signals
    signal(SIGINT, signal_handler);

    sensor_data line_data = {
        .sensor = &line_sensor,
        .gpio = gpio,
        .pin = 27
    };

    sensor_data ir_data = {
        .sensor = &ir_sensor,
        .gpio = gpio,
        .pin = 4
    };

    pthread_t ir_thread;
    pthread_t line_thread;

    pthread_create(&ir_thread, NULL, sensor, &ir_data);
    pthread_create(&line_thread, NULL, sensor, &line_data);

    if (setjmp(close_buf) == 0) 
    {
	// Zero means on and anything else means off.
        while(1)
        {
            delay(1,500,0);
            if(atomic_load(&ir_sensor) > 0)
            {
                printf("Ir sensor is off!\n");
            }
            else
            {
                printf("Ir sensor is on!\n");
            }

            if(atomic_load(&line_sensor) > 0)
            {
                printf("Line sensor is off!\n");
            }
            else
            {
                printf("Line sensor is on!\n");
            }
        }
    }

    atomic_store(&is_sensing, 0);

    printf("\nCleaning threads...\n");
    while (atomic_load(&thread_count) < 2);

    pthread_join(ir_thread, NULL);
    pthread_join(line_thread, NULL);

    printf("Threads cleaned!\n");
    clean(gpio_mmap);
    return 0;
}
