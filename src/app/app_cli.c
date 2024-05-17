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
 * File        app_cli.c
 * Created by  David Burke
 * Version     1.0
 * 
 */

#include "app_cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>

#include "../cli/cli.h"
#include "../time_funcs/time_funcs.h"
#include "../buffer/ring_buf.h"


/****************************************************************************
 * Definitions
 *****************************************************************************/

#define CLI_INPUT_BUF_LENGTH (1024U)

/****************************************************************************
 * Variables
 *****************************************************************************/

static pthread_t cli_input_thread;
static pthread_mutex_t lock; 

static ring_buf_t cli_input_buf;
static char cli_input_data[CLI_INPUT_BUF_LENGTH];

static uint8_t cli_buffer[CLI_INPUT_BUF_LENGTH] = {0};

static cli_t cli;
static cli_status_t rslt = CLI_OK;

static bool *keep_running = NULL;

/****************************************************************************
 * Prototypes
 *****************************************************************************/

static bool put_cli_buf_data(char c);
static bool pop_cli_buf_data(char *c);
static bool cli_buf_is_empty(void);

static void user_println(const char * format, ...);

static void* get_input(void* arg);

static cli_status_t help_func(int argc, char **argv);
static cli_status_t exit_func(int argc, char **argv);


cmd_t cmd_tbl[8] = {
    {
        .cmd = "help",
        .func = help_func
    },
    {
        .cmd = "quit",
        .func = exit_func
    },
    {
        .cmd = "exit",
        .func = exit_func
    },
    {
        .cmd = "stop",
        .func = exit_func
    },
    {
        .cmd = "q",
        .func = exit_func
    },

};

/****************************************************************************
 * Functions
 *****************************************************************************/

bool app_cli_init(bool *shutdown_flag)
{
    keep_running = shutdown_flag;

    if(NULL == keep_running){
        printf("The shutdown flag cannot be NULL\n");
        return false;
    }

    if(*keep_running == false)
    {
        printf("Initialize the shutdown_flag to true or the keyboard input won't run\n");
        return false;
    }

    cli.println = user_println;
    cli.cmd_tbl = cmd_tbl;
    cli.cmd_cnt = sizeof(cmd_tbl)/sizeof(cmd_t);

    /* initialize the cli api */
    if((rslt = cli_init(&cli, cli_buffer, sizeof(cli_buffer))) != CLI_OK)
    {
        printf("CLI: Failed to initialise");
        return false;
    }

    /* Initialize a buffer to hold data from the keyboard input thread */
    ring_buf_init(&cli_input_buf, cli_input_data, CLI_INPUT_BUF_LENGTH, sizeof(char));

    /* create a mutex for shared keyboard input data between threads */
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return false; 
    } 

    /* Create the keyboard input thread */
    int error = pthread_create(&cli_input_thread, NULL, &get_input, NULL); 
    if (error != 0) 
    {
        printf("\nThread can't be created :[%s]", strerror(error)); 
        return false;
    }

    /* detach the cli input thread */
    pthread_detach(cli_input_thread);

    return true;
}

void app_cli_deinit()
{
    pthread_mutex_destroy(&lock); 
}

void app_cli_process()
{
    char c;

    if(cli_buf_is_empty()){
        return;
    }

    do
    {
        if(pop_cli_buf_data(&c))
        {
            cli_put(&cli, c);
            cli_process(&cli);
        }
    } while (!cli_buf_is_empty());
}

static void* get_input(void* arg) 
{ 
    char c;
    (void)arg;

    do
    {
        /* wait for a character from stdin */
        c = fgetc(stdin);

        /* Got the char. Put it in the buffer */
        put_cli_buf_data(c);

    } while (true == *keep_running);

    return NULL; 
} 

static void user_println(const char * format, ...)
{
    va_list args;
    va_start (args, format);
    vprintf (format, args);
    va_end (args);
}

static cli_status_t help_func(int argc, char **argv)
{
    cli_status_t ok = CLI_OK;
    (void)argc;
    (void)argv;
    cli.println("[cli] CLI HELP. Available commands:\n");
    cli.println("  quit, exit, stop, q - Exit the Program\n"); 
    return ok;
}

static cli_status_t exit_func(int argc, char **argv)
{
    cli_status_t ok = CLI_OK;
    (void)argc;
    (void)argv; 

    if(NULL != keep_running){
        *keep_running = false;
    }

    return ok;
}

static bool put_cli_buf_data(char c)
{
    bool put_success;
    pthread_mutex_lock(&lock); 
    put_success = ring_buf_push(&cli_input_buf, &c);
    pthread_mutex_unlock(&lock);  
    return put_success;  
}

static bool pop_cli_buf_data(char *c)
{
    bool pop_success;
    if(c == NULL) return false;
    pthread_mutex_lock(&lock); 
    pop_success = ring_buf_pop(&cli_input_buf, c);
    pthread_mutex_unlock(&lock);  
    return pop_success;
}

static bool cli_buf_is_empty(void)
{
    return ring_buf_is_empty(&cli_input_buf);
}