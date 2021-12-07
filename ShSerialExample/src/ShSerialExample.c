#include <stdio.h>
#include <shSerial.h>
#include <stdlib.h>

#include <stdio.h>

int main(void) {

  printf("connecting to serial port\n");
  ShSerialHandle handle = {0};
#ifdef _WIN32
  shSerialOpen("COM3", 9600, 100, SH_SERIAL_READ_WRITE, &handle);
#else
  shSerialOpen("/dev/ttyACM0", 9600, 100, SH_SERIAL_READ_WRITE, &handle);
#endif  

  //print read data
  printf("waiting for incoming data...\n");
  float dst[1];
  for (;;) {
    unsigned long bytes_read = 0;
    if (!shSerialReadBuffer(4, dst, &bytes_read, &handle)) { break; }
    printf("voltage: %f\n", dst[0]);
    shSerialSleep(5);
  }
  
  shSerialClose(&handle);

#ifdef _WIN32
  system("pause");
#endif
  return 0;
}
