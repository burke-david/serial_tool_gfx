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
 * File        ring_buf.c
 * Created by  David Burke
 * Version     1.0
 * 
 */


#include "ring_buf.h"

/****************************************************************************
 * Definitions
 *****************************************************************************/

/****************************************************************************
 * Variables
 *****************************************************************************/

/****************************************************************************
 * Prototypes
 *****************************************************************************/

/****************************************************************************
 * Functions
 *****************************************************************************/


void ring_buf_init(ring_buf_t *obj, void *buf, size_t size, size_t item_size)
{
    // Return if obj or buf is NULL
    if (obj == NULL || buf == NULL) {
        return;
    }

    // Initialize the ring buffer object
    obj->buf = buf;
    obj->size = size;
    obj->item_size = item_size;
    obj->head = 0;
    obj->tail = 0;
}

void ring_buf_clear(ring_buf_t *obj)
{
    // Return if obj is NULL
    if (obj == NULL) {
        return;
    }

    // Reset the head and tail indices
    obj->head = 0;
    obj->tail = 0;
}

bool ring_buf_is_empty(ring_buf_t *obj)
{
    // Return true if obj is NULL
    if (obj == NULL) {
        return true;
    }

    // Return true if the head and tail indices are the same
    return obj->head == obj->tail;
}

bool ring_buf_is_full(ring_buf_t *obj)
{
    // Return false if obj is NULL
    if (obj == NULL) {
        return false;
    }

    // Calculate the next head index
    size_t next_head = (obj->head + 1) % obj->size;

    // Return true if the next head index is the same as the tail index
    return next_head == obj->tail;
}

bool ring_buf_push(ring_buf_t *obj, void *item)
{
    // Return false if obj or item is NULL
    if (obj == NULL || item == NULL) {
        return false;
    }

    // Return false if the ring buffer is full
    if (ring_buf_is_full(obj)) {
        return false;
    }

    // Copy the item into the buffer
    memcpy((uint8_t *)obj->buf + obj->head * obj->item_size, item, obj->item_size);

    // Update the head index
    obj->head = (obj->head + 1) % obj->size;

    return true;
}

bool ring_buf_pop(ring_buf_t *obj, void *item)
{
    // Return false if obj or item is NULL
    if (obj == NULL || item == NULL) {
        return false;
    }

    // Return false if the ring buffer is empty
    if (ring_buf_is_empty(obj)) {
        return false;
    }

    // Copy the item from the buffer
    memcpy(item, (uint8_t *)obj->buf + obj->tail * obj->item_size, obj->item_size);

    // Update the tail index
    obj->tail = (obj->tail + 1) % obj->size;

    return true;
}