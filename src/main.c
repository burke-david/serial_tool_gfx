/*
 * MIT License
 * 
 * Copyright (c) 2024 David Burke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * File        main.c
 * Created by  David Burke
 * Version     1.0
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include "app/app.h"
#include "app/app_cli.h"


/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Variables
 *****************************************************************************/

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Print the help message showing how to use this tool.
 * 
 */
static void show_help_message();

/*****************************************************************************
 * Functions
 *****************************************************************************/

/**
 * @brief Call the program with a serial port argument.
 * 
 * Example: serial_tool -s /dev/ttyUSB0
 * 
 * Note: needs to be run as root or on linux, run the following command to allow the
 *       the user to run the program without sudo:
 *       sudo usermod -a -G dialout $USER (where $USER is the user current user)
 *       Log out and back in again for the command to take...
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    char c;

    bool keep_running = true;

    /* OPTION VARIABLES */
    int opt = 0;
    char *port_name = NULL;

    /* PROCESS OPTIONS */
    while ((opt = getopt(argc, argv, "s:h")) != -1) 
    {
        switch(opt) 
        {
        case 's':
            port_name = optarg;
            printf("\nport_name: %s\n", port_name);
            break;  
        case 'h':
            show_help_message();
            
            break;
        default:
            show_help_message();
            break;
        }
    }

    if(port_name == NULL)
    {
        printf("\nSelect a serial port to use the program. (Try \"ls /dev\" to find possible ports)\n\n");
        show_help_message();
        return 0;
    }

    if (!app_init(port_name)) {
        printf("APP failed initialization\n");
        return 0;
    }

    if(!app_cli_init(&keep_running))
    {
        printf("CLI failed initialization\n");
        return 0;
    }

    do {
        /* Call the app task handler */
        app_task_handler();

        /* Periodically process the CLI */
        app_cli_process();

    /* Cntrl-C to end process or change the while statement to end after a period of time... or some other condition */
    } while(keep_running);   //  CLI command to quit, exit, q, stop, will change this to false.

    app_cli_deinit();

    app_deinit();

    return 0;
}


static void show_help_message()
{
    printf("serial_tool - C-based serial development tool\n");
    printf("-------------------------------------------------------------------\n");
    printf("-s <port_name> : select the attached USB-to-serial cable as enumerated in /dev (ie. /dev/ttyUSB0)\n");
    printf("-h : show help\n\n");
    printf("Usage: serial_tool -s <port_name>\n");
    printf("Example: \n");
    printf("         serial_tool -s /dev/ttyUSB0\n");
    printf("         * \"-s /dev/ttyUSB0\" Select USB-to-serial cable at /dev/ttyUSB0\n");

}
