# shserial

## [Build status](https://github.com/MrSinho/PlyImporter/.ShCI)

A simple Windows and Unix serial communication library using the win32 api and posix, written in C.

[![linux_badge](.ShCI/linux-status.svg)](https://github.com/MrSinho/ShSerial/tree/main/.ShCI/linux-log.md)
[![windows_badge](.ShCI/windows-status.svg)](https://github.com/MrSinho/ShSerial/tree/main/.ShCI/windows-log.md)

## Getting started

```bash
git clone https://github.com/MrSinho/ShSerial.git
mkdir build 
cd build
cmake -DSH_SERIAL_BUILD_EXAMPLE=ON ..
cmake --build .
```

## Example:

See the example [here](ShSerialExample/src/ShSerialExample.c)

```c
#include <ShSerial.h>

#include <stdio.h>

int main(void) {

  printf("connecting to serial port\n");
  ShSerialHandle handle = {0};

  shSerialOpen("/dev/ttyACM0", 9600, 100, SH_SERIAL_READ_WRITE, &handle);

  //read and print data
  printf("waiting for incoming data...\n");
  float dst[1];
  for (;;) {
    unsigned long bytes_read = 0;
    if (!shSerialReadBuffer(4, dst, &bytes_read, &handle)) { 
    	break; 
    }
    printf("voltage: %f\n", dst[0]);
    shSerialSleep(5);
  }
  
  shSerialClose(&handle);

  return 0;
}
```
