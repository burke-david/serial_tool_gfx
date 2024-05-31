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
 * File        serial.c
 * Created by  David Burke
 * Version     1.0
 * 
 */

/*
 * References:
 * https://github.com/HowieXue/Linux_Gateway-ioT/blob/aa851c0b3ac8677970abd88889db4efd911101ca/pthread_transfer.c#L7
 * https://github.com/hexavik/Serial-Terminal/blob/main/serial_terminal.c
 * https://en.wikibooks.org/wiki/Serial_Programming/termios
 * 
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>		// Contains file controls like O_RDWR
#include <errno.h>		// Error integer and strerror() function
#include <termios.h>	// Contains POSIX terminal control definitions
#include <unistd.h>		// write(), read(), close()
#endif

#include "../buffer/ring_buf.h"
#include "serial.h"


/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*
 * Change the Baudrate in accordance with your requirement
 */
#ifdef _WIN32
#define BAUD_RATE	CBR_115200
#else
#define BAUD_RATE	B115200
#endif

#define SERIAL_RX_BUF_LENGTH 1024U * 10U
#define SERIAL_TX_BUF_LENGTH 1024U * 10U

/*****************************************************************************
 * Variables
 *****************************************************************************/

#ifdef _WIN32
static HANDLE serial_port = INVALID_HANDLE_VALUE;
#else
static int serial_port = -1;
#endif

static ring_buf_t rx_buf, tx_buf;
static uint8_t rx_data[SERIAL_RX_BUF_LENGTH];
static uint8_t tx_data[SERIAL_TX_BUF_LENGTH];

/*****************************************************************************
 * Prototypes
 *****************************************************************************/

/*****************************************************************************
 * Functions
 *****************************************************************************/

bool serial_init(const char *path)
{

#ifdef _WIN32

    serial_port = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (serial_port == INVALID_HANDLE_VALUE) {
        printf("Error opening serial port %s\n", path);
        return false;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(serial_port, &dcbSerialParams)) {
        printf("Error getting serial port state\n");
        return false;
    }

    dcbSerialParams.BaudRate = BAUD_RATE;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(serial_port, &dcbSerialParams)) {
        printf("Error setting serial port state\n");
        return false;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(serial_port, &timeouts)) {
        printf("Error setting serial port timeouts\n");
        return false;
    }
#else
    struct termios tio;
    /*
        https://man7.org/linux/man-pages/man2/open.2.html
        The return value of open() is a file descriptor, a small,
       nonnegative integer that is an index to an entry in the process's
       table of open file descriptors.  The file descriptor is used in
       subsequent system calls (read(2), write(2), lseek(2), fcntl(2),
       etc.) to refer to the open file.  The file descriptor returned by
       a successful call will be the lowest-numbered file descriptor not
       currently open for the process.

       By default, the new file descriptor is set to remain open across
       an execve(2) (i.e., the FD_CLOEXEC file descriptor flag described
       in fcntl(2) is initially disabled); the O_CLOEXEC flag, described
       below, can be used to change this default.  The file offset is
       set to the beginning of the file (see lseek(2)).

       A call to open() creates a new open file description, an entry in
       the system-wide table of open files.  The open file description
       records the file offset and the file status flags (see below).  A
       file descriptor is a reference to an open file description; this
       reference is unaffected if pathname is subsequently removed or
       modified to refer to a different file.  For further details on
       open file descriptions, see NOTES
    */
    serial_port = open(path, O_RDWR | O_NONBLOCK); // O_NONBLOCK might override VMIN and VTIME, so read() may return immediately.

    printf("path: %s returned %d\n", path, serial_port);

    if(serial_port <= 0)
    {
        return false;
    }

    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    cfsetospeed(&tio,BAUD_RATE);            // 115200 baud
    cfsetispeed(&tio,BAUD_RATE);            // 115200 baud

    tcsetattr(serial_port,TCSANOW,&tio); 

#endif

    /* Initialize rx and tx buffers */
    ring_buf_init(&rx_buf, rx_data, SERIAL_RX_BUF_LENGTH, sizeof(uint8_t));
    ring_buf_init(&tx_buf, tx_data, SERIAL_TX_BUF_LENGTH, sizeof(uint8_t));

    return true;
}

void serial_close()
{
#ifdef _WIN32
    if (serial_port != INVALID_HANDLE_VALUE) {
        CloseHandle(serial_port);
        printf("serial_port closed\n");
    } else {
        printf("No port opened\n");
    }
    serial_port = INVALID_HANDLE_VALUE;
#else
    if (serial_port > 0) {
        close(serial_port);
        printf("serial_port: %d closed\n", serial_port);
    } else {
        printf("No port opened\n");
    }
    serial_port = -1;
#endif
}

void serial_task()
{
    unsigned char c;


#ifdef _WIN32
    DWORD bytes_written;
    DWORD bytesRead;
    if (serial_port == INVALID_HANDLE_VALUE) return;

    if (ReadFile(serial_port, &c, 1, &bytesRead, NULL) && bytesRead > 0) {
        ring_buf_push(&rx_buf, &c);
    }

    if (!ring_buf_is_empty(&tx_buf)) {
        do {
            if (ring_buf_pop(&tx_buf, &c)) {
                if (!WriteFile(serial_port, &c, 1, &bytes_written, NULL) || bytes_written != 1) {
                    fprintf(stderr, "write failed\n");
                }
            }
        } while (!ring_buf_is_empty(&tx_buf));
    }
#else
    int bytes_written;

    if (serial_port <= 0) return;

    if (read(serial_port, &c, 1) > 0) {
        ring_buf_push(&rx_buf, &c);
    }

    if (!ring_buf_is_empty(&tx_buf)) {
        do {
            if (ring_buf_pop(&tx_buf, &c)) {
                bytes_written = write(serial_port, &c, 1);
                if (1 != bytes_written) {
                    fprintf(stderr, "write failed\n");
                }
            }
        } while (!ring_buf_is_empty(&tx_buf));
    }
#endif
}

bool serial_rx_buf_is_empty()
{
    return ring_buf_is_empty(&rx_buf);
}

bool serial_rx_buf_is_full()
{
    return ring_buf_is_full(&rx_buf);
}

void serial_rx_buf_clear()
{
    ring_buf_clear(&rx_buf);
}

bool serial_rx_buf_pop(uint8_t *data)
{
    return ring_buf_pop(&rx_buf, data);
}


bool serial_tx_buf_is_empty()
{
    return ring_buf_is_empty(&tx_buf);
}

bool serial_tx_buf_is_full()
{
    return ring_buf_is_full(&tx_buf);
}

void serial_tx_buf_clear()
{
    ring_buf_clear(&tx_buf);
}

bool serial_tx_buf_push(const uint8_t *data)
{
    return ring_buf_push(&tx_buf, (void*)data);
}

