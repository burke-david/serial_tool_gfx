# Serial Tool

Create a simple USB-to-Serial program in C to allow sending and receiving whatever protocol/data you want over serial.
Run on a Linux box or Mac.
Testing done on an Ubuntu VM running in Parallels on a Macbook with Apple silicon.

In order to connect to the serial device, you'll need to run as root (`sudo`), or put the user
in the `dialout` group as follows:

```
sudo usermod -a -G dialout user 
```
`user` is whatever user is currently logged in that you want to run the program with.
Log out and back in again for the command to take...

Connection example:
```
user@some-machine:~/serial_tool$ ./build/serial_tool -s /dev/ttyUSB0

port_name: /dev/ttyUSB0
path: /dev/ttyUSB0 returned 3
port /dev/ttyUSB0 opened successfully
```


