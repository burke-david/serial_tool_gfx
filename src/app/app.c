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
 * File        app.c
 * Created by  David Burke
 * Version     1.0
 * 
 */

#include "app.h"
#include "../gui/gui.h"
#include "../serial/serial.h"
#include <stdio.h>

/****************************************************************************
 * Definitions
 *****************************************************************************/

/****************************************************************************
 * Variables
 *****************************************************************************/

/****************************************************************************
 * Prototypes
 *****************************************************************************/


/**
 * @brief Dumps a byte as hexadecimal.
 *
 * This function takes a byte as input and prints its hexadecimal representation.
 *
 * @param byte The byte to be dumped.
 */
static void dump_byte_as_hex(uint8_t byte);

/**
 * @brief Processes the given data.
 *
 * This function is responsible for processing the provided data.
 * It takes a uint8_t data as input and performs the necessary operations.
 *
 * @param data The data to be processed.
 */
static void process_data(uint8_t data);

/****************************************************************************
 * Functions
 *****************************************************************************/

bool app_init(const char *serial_port_path)
{   
    bool result = false;

    result = serial_init(serial_port_path);
    if (!result) {
        serial_close();
        printf("port %s INVALID\n", serial_port_path);
        return false;
    }

    printf("port %s opened successfully\n", serial_port_path);

    return gui_init(5);
}

void app_deinit(void)
{
    serial_close();
}

void app_task_handler(void)
{
    char c;

    /* Call the serial task periodically or as fast as is reasonable */
    serial_task();

    /* Do something with any data currently in the RX buffer */
    if (!serial_rx_buf_is_empty()) {
        do {   
            if (serial_rx_buf_pop((uint8_t*)&c)) {
                process_data((uint8_t)c);
            }
        } while (!serial_rx_buf_is_empty());
    } 

    gui_task();   
}


static void process_data(uint8_t data)
{
    // Process the data
    dump_byte_as_hex(data);
    gui_process_byte(data);
}

static void dump_byte_as_hex(uint8_t byte)
{
    static int count = 0;
    printf("%02X ", byte);
    count++;
    if (count == 16)
    {
        printf("\n");
        count = 0;
    }
    fflush(stdout);
}