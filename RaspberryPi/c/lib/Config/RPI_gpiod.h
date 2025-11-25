/*****************************************************************************
* | File        :   gpiod.h
* | Function    :   Drive GPIO
* | Info        :   Read and write gpio
******************************************************************************/
#ifndef __GPIOD_
#define __GPIOD_

#include <stdio.h>
#include <gpiod.h>

#define GPIOD_IN  0
#define GPIOD_OUT 1

#define GPIOD_LOW  0
#define GPIOD_HIGH 1

#define NUM_MAXBUF  4
#define DIR_MAXSIZ  60

#define GPIOD_DEBUG 0
#if GPIOD_DEBUG 
	#define GPIOD_Debug(__info,...) printf("Debug: " __info,##__VA_ARGS__)
#else
	#define GPIOD_Debug(__info,...)  
#endif 

// BCM GPIO for Jetson nano
#define GPIO4 4 // 7, 4
#define GPIO17 7 // 11, 17
#define GPIO18 18 // 12, 18
#define GPIO27 27 // 13, 27
#define GPIO22 22 // 15, 22
#define GPIO23 23 // 16, 23
#define GPIO24 24 // 18, 24
#define SPI0_MOSI 10 // 19, 10
#define SPI0_MISO 9 // 21, 9
#define GPIO25 28 // 22, 25
#define SPI0_SCK 11 // 23, 11
#define SPI0_CS0 8 // 24, 8
#define SPI0_CS1 7 // 26, 7
#define GPIO5 5 // 29, 5
#define GPIO6 6 // 31, 6
#define GPIO12 12 // 32, 12
#define GPIO13 13 // 33, 13
#define GPIO19 19 // 35, 19
#define GPIO16 16 // 36, 16
#define GPIO26 26 // 37, 26
#define GPIO20 20 // 38, 20
#define GPIO21 21 // 40, 21

extern struct gpiod_chip *gpiochip;
extern struct gpiod_line *gpioline;
extern int ret;

int GPIOD_Export();
int GPIOD_Unexport(int Pin);
int GPIOD_Unexport_GPIO(void);
int GPIOD_Direction(int Pin, int Dir);
int GPIOD_Read(int Pin);
int GPIOD_Write(int Pin, int value);

#endif