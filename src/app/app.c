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

/****************************************************************************
 * Functions
 *****************************************************************************/

void app_process_data(uint8_t data)
{
    // Process the data
    dump_byte_as_hex(data);
}

void app_task_handler(void)
{
    // Anything that needs to be done periodically that's application related.
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