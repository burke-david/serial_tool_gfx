/*
 * MIT License
 *
 * Copyright (c) 2024 David Burke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the 'Software'), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * File        serial.h
 * Created by  David Burke
 * Version     1.0
 *
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "../buffer/ring_buf.h"

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief Initialize the serial port.
 * In Linux it is specified as ttyUSB* or ttyACM*
 * In MacOS it is specified as cu.usbmodem* or cu.usbserial-*
 * 
 * @param path COM port path name
 * @return true if open was successful
 * @return false 
 */
bool serial_init(const char *path);

/**
 * @brief If the serial_port was opened successfully, this will properly close it.
 * 
 */
void serial_close();

/**
 * @brief Until a thread is created to handle serial processing,... call this periodically.
 * 
 */
void serial_task();

/**
 * @brief Returns if the RX buffer is empty
 * 
 * @return true 
 * @return false 
 */
bool serial_rx_buf_is_empty();

/**
 * @brief Returns if the RX buffer is full
 * 
 * @return true 
 * @return false 
 */
bool serial_rx_buf_is_full();

/**
 * @brief Clear the RX buffer
 * 
 */
void serial_rx_buf_clear();

/**
 * @brief Get a data byte off of the buffer. Returns T if successful.
 * 
 * @param data pointer to variable data will be stored at.
 * @return true 
 * @return false 
 */
bool serial_rx_buf_pop(uint8_t *data);

/**
 * @brief Returns if the TX buffer is empty
 * 
 * @return true 
 * @return false 
 */
bool serial_tx_buf_is_empty();

/**
 * @brief Returns if the TX buffer is full
 * 
 * @return true 
 * @return false 
 */
bool serial_tx_buf_is_full();

/**
 * @brief Clear the TX buffer
 * 
 */
void serial_tx_buf_clear();

/**
 * @brief Load a data byte into the TX buffer. Returns T if successful.
 * 
 * @param data reference to the data that will be loaded into buffer
 * @return true 
 * @return false 
 */
bool serial_tx_buf_push(const uint8_t *data);

#ifdef __cplusplus
}
#endif
#endif /* SERIAL_H_ */