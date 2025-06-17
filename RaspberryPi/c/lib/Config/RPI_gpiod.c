/*****************************************************************************
* | File        :   RPI_GPIOD.c
* | Function    :   Drive GPIO
* | Info        :   Read and write gpio
******************************************************************************/
#include "RPI_gpiod.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gpiod.h>

struct gpiod_chip *gpiochip;
struct gpiod_line *gpioline;
int ret;

int GPIOD_Export()
{   
    char buffer[NUM_MAXBUF];
    FILE *fp;

    fp = popen("cat /proc/cpuinfo | grep 'Raspberry Pi 5'", "r");
    if (fp == NULL) {
        GPIOD_Debug("It is not possible to determine the model of the Raspberry PI\n");
        return -1;
    }

    if(fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        gpiochip = gpiod_chip_open("/dev/gpiochip4");
        if (gpiochip == NULL)
        {
            GPIOD_Debug( "gpiochip4 Export Failed\n");
            return -1;
        }
    }
    else
    {
        gpiochip = gpiod_chip_open("/dev/gpiochip0");
        if (gpiochip == NULL)
        {
            GPIOD_Debug( "gpiochip0 Export Failed\n");
            return -1;
        }
    }

        
    return 0;
}

int GPIOD_Unexport(int Pin)
{
    gpioline = gpiod_chip_get_line(gpiochip, Pin);
    if (gpioline == NULL)
    {
        GPIOD_Debug( "Export Failed: Pin%d\n", Pin);
        return -1;
    }

    gpiod_line_release(gpioline);
    
    GPIOD_Debug( "Unexport: Pin%d\r\n", Pin);
    
    return 0;
}

int GPIOD_Unexport_GPIO(void)
{
    gpiod_line_release(gpioline);
    gpiod_chip_close(gpiochip);

    return 0;
}

int GPIOD_Direction(int Pin, int Dir)
{
    gpioline = gpiod_chip_get_line(gpiochip, Pin);
    if (gpioline == NULL)
    {
        GPIOD_Debug( "Export Failed: Pin%d\n", Pin);
        return -1;
    }

    if(Dir == GPIOD_IN)
    {
        ret = gpiod_line_request_input(gpioline, "gpio");
        if (ret != 0)
        {
            GPIOD_Debug( "Export Failed: Pin%d\n", Pin);
            return -1;
        }        
        GPIOD_Debug("Pin%d:intput\r\n", Pin);
    }
    else
    {
        ret = gpiod_line_request_output(gpioline, "gpio", 0);
        if (ret != 0)
        {
            GPIOD_Debug( "Export Failed: Pin%d\n", Pin);
            return -1;
        }        
        GPIOD_Debug("Pin%d:Output\r\n", Pin);
    }
    return 0;
}

int GPIOD_Read(int Pin)
{
    gpioline = gpiod_chip_get_line(gpiochip, Pin);
    if (gpioline == NULL)
    {
        GPIOD_Debug( "Export Failed: Pin%d\n", Pin);
        return -1;
    }

    ret = gpiod_line_get_value(gpioline);
    if (ret < 0)
    {
        GPIOD_Debug( "failed to read value!\n");
        return -1;
    }

    return(ret);
}

int GPIOD_Write(int Pin, int value)
{
    gpioline = gpiod_chip_get_line(gpiochip, Pin);
    if (gpioline == NULL)
    {
        GPIOD_Debug( "Export Failed: Pin%d\n", Pin);
        return -1;
    }     

    ret = gpiod_line_set_value(gpioline, value);
    if (ret != 0)
    {
        GPIOD_Debug( "failed to write value! : Pin%d\n", Pin);
        return -1;
    }
    return 0;
}
