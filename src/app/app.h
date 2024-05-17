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
 * File        app.h
 * Created by  David Burke
 * Version     1.0
 *
 */

#ifndef APP_H_
#define APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/****************************************************************************
 * Definitions
 *****************************************************************************/

/****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/****************************************************************************
 * Function Prototypes
 *****************************************************************************/


/**
 * @brief Processes the given data.
 *
 * This function is responsible for processing the provided data.
 * It takes a uint8_t data as input and performs the necessary operations.
 *
 * @param data The data to be processed.
 */
void app_process_data(uint8_t data);

/**
 * @brief Handles the application task.
 * 
 * This function is responsible for handling the application task.
 * It should be called periodically to perform the necessary operations
 * for the application.
 */
void app_task_handler(void);

#ifdef __cplusplus
}
#endif
#endif /* APP_H_ */