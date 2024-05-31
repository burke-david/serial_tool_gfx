# Serial Tool

Create a simple USB-to-Serial program in C to allow sending and receiving whatever protocol/data you want over serial.
Run on Linux, Windows, or Mac.

Testing has been done on an Ubuntu VM running in Parallels on a Macbook with Apple silicon, a Windows machine running Windows 11, and an x86 Ubuntu machine.

In order to connect to the serial device on Linux, you'll need to run as root (`sudo`), or put the user
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

If running on Windows, the command might look something like this:
```
PS C:\Users\user\Documents\_code\serial_tool\build> .\serial_tool.exe -s COM5

port_name: COM5
port COM5 opened successfully
```

### Searching for serial devices.

On Linux and MacOS, the serial devices can be found in the `/dev` directory.
```
ls /dev
```

On Windows, from the command line you can use the following command:
```
mode | findstr "COM"
```
This should return something like
```
Status for device COM6:
Status for device COM5:
```
where COM5 and COM6 are serial devices connected to the computer. Instead of `/dev/ttyUSB0` for the path on Linux, you would use `COM5` or `COM6` on Windows.


## Build the project

This project is built with `gcc`. On Windows, you can install `MinGW`.

The build system is CMake. 

On Windows,
- Download and run [Windows x64 Installer](https://cmake.org/download/)
- Add CMake to the PATH variable
- As of this documentation, the CMake version is 3.29.3

On MacOS, CMake can be installed using brew. On Linux, 
```
sudo apt install cmake
```

On a Linux system, the bare minimum is required to build the project
```
    sudo apt update
    sudo apt install build-essential
    sudo apt install git
    sudo apt install cmake
    sudo apt install gdb
```

### Run CMake and Build

From the project directory `.../serial_tool/` create a `build` directory and change into it.
```
mkdir build
cd build
```

Then run CMake followed by `make` to build
```
cmake ..
make
```

### Unit Testing

#### Mac / Linux

* Install ceedling
    ```
    sudo gem install ceedling
    ```
* Reference file `project.yml` and add your source files here.
* Unit tests are added to the `tests` directory
* Naming should be `test_<your_module_to_test>.c`
* Run tests by running
    ```
    ceedling test:all
    ```
* "Clean" ceedling files by running
    ```
    ceedling clobber
    ```

#### Windows

* Don't fuss with it. Just unit test on a Linux VM or Mac.