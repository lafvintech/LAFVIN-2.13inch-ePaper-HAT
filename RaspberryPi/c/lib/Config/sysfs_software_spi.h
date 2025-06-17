/*****************************************************************************
* | File        :   sysfs_software_spi.h
* | Function    :   Read and write /sys/class/gpio, software spi
******************************************************************************/
#ifndef __SYSFS_SOFTWARE_SPI_
#define __SYSFS_SOFTWARE_SPI_

#include "sysfs_gpio.h"
#include <stdint.h>
#include <stdio.h>

#define SYSFS_SOFTWARE_SPI_DEBUG 1
#if SYSFS_SOFTWARE_SPI_DEBUG
#define SYSFS_SOFTWARE_SPI_Debug(__info,...) printf("Debug: " __info,##__VA_ARGS__)
#else
#define SYSFS_SOFTWARE_SPI_Debug(__info,...)
#endif

/**
 * SPI communication mode
**/
typedef enum {
    SOFTWARE_SPI_Mode0,   /* Clock Polarity is 0 and Clock Phase is 0 */
    SOFTWARE_SPI_Mode1,   /* Clock Polarity is 0 and Clock Phase is 1 */
    SOFTWARE_SPI_Mode2,   /* Clock Polarity is 1 and Clock Phase is 0 */
    SOFTWARE_SPI_Mode3,   /* Clock Polarity is 1 and Clock Phase is 1 */
} SOFTWARE_SPI_Mode;

/**
 * SPI clock(div)
**/
typedef enum {
    SOFTWARE_SPI_CLOCK_DIV2,
    SOFTWARE_SPI_CLOCK_DIV4,
    SOFTWARE_SPI_CLOCK_DIV8,
    SOFTWARE_SPI_CLOCK_DIV16,
    SOFTWARE_SPI_CLOCK_DIV32,
    SOFTWARE_SPI_CLOCK_DIV64,
    SOFTWARE_SPI_CLOCK_DIV128,
} SOFTWARE_SPI_Clock;

/**
 * Define SPI type
**/
typedef enum {
    SOFTWARE_SPI_Master,
    SOFTWARE_SPI_Slave,
} SOFTWARE_SPI_Type;

/**
 * Define SPI order
**/
typedef enum {    
    SOFTWARE_SPI_LSBFIRST,
    SOFTWARE_SPI_MSBFIRST,
} SOFTWARE_SPI_Order;

/**
 * Define SPI attribute
**/
typedef struct SPIStruct {
    //GPIO
    uint16_t SCLK_PIN;
    uint16_t MOSI_PIN;
    uint16_t MISO_PIN;
    uint16_t CS_PIN;
    
    //Mode
    SOFTWARE_SPI_Mode Mode;
    uint8_t CPOL;
    uint8_t CPHA;

    SOFTWARE_SPI_Clock Delay;
    SOFTWARE_SPI_Type Type;
    SOFTWARE_SPI_Order Order;
} SOFTWARE_SPI;

void SYSFS_software_spi_begin(void);
void SYSFS_software_spi_end(void);
void SYSFS_software_spi_setBitOrder(uint8_t order);
void SYSFS_software_spi_setDataMode(uint8_t mode);
void SYSFS_software_spi_setClockDivider(uint8_t div);
uint8_t SYSFS_software_spi_transfer(uint8_t value);

#endif