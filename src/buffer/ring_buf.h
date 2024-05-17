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
 * File        ring_buf.h
 * Created by  David Burke
 * Version     1.0
 *
 */

#ifndef RING_BUF_H_
#define RING_BUF_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

typedef struct ring_buf_t {
    void *buf;          /**< Pointer to the buffer */
    size_t size;        /**< Size of the buffer */
    size_t item_size;   /**< Size of each item in the buffer */
    size_t head;        /**< Index of the head of the buffer */
    size_t tail;        /**< Index of the tail of the buffer */
} ring_buf_t;

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/**
 * @brief Initializes a ring buffer object.
 * 
 * @param obj Pointer to the ring buffer object.
 * @param buf Pointer to the buffer memory.
 * @param size Size of the buffer.
 * @param item_size Size of each item in the buffer.
 */
void ring_buf_init(ring_buf_t *obj, void *buf, size_t size, size_t item_size);

/**
 * @brief Pushes an item into the ring buffer.
 * 
 * @param obj Pointer to the ring buffer object.
 * @param item Pointer to the item to be pushed.
 * @return True if the item was successfully pushed, false otherwise.
 */
bool ring_buf_push(ring_buf_t *obj, void *item);

/**
 * @brief Pops an item from the ring buffer.
 * 
 * @param obj Pointer to the ring buffer object.
 * @param item Pointer to store the popped item.
 * @return True if an item was successfully popped, false otherwise.
 */
bool ring_buf_pop(ring_buf_t *obj, void *item);

/**
 * @brief Clears the ring buffer.
 * 
 * @param obj Pointer to the ring buffer object.
 */
void ring_buf_clear(ring_buf_t *obj);

/**
 * @brief Checks if the ring buffer is empty.
 * 
 * @param obj Pointer to the ring buffer object.
 * @return True if the ring buffer is empty, false otherwise.
 */
bool ring_buf_is_empty(ring_buf_t *obj);

/**
 * @brief Checks if the ring buffer is full.
 * 
 * @param obj Pointer to the ring buffer object.
 * @return True if the ring buffer is full, false otherwise.
 */
bool ring_buf_is_full(ring_buf_t *obj);

#ifdef __cplusplus
}
#endif
#endif /* RING_BUF_H_ */