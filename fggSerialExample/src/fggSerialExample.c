#include <stdio.h>
#include <fggSerial.h>
#include <stdlib.h>

#include <stdio.h>

int main(void) {

  printf("connecting to serial port\n");
  FggSerialHandle handle = {0};
#ifdef _WIN32
  fggSerialOpen("COM3", 9600, 100, FGG_SERIAL_READ_WRITE, &handle);
#else
  fggSerialOpen("/dev/ttyACM0", 9600, 100, FGG_SERIAL_READ_WRITE, &handle);
#endif  

  //print read data
  printf("waiting for incoming data...\n");
  float dst[1];
  for (;;) {
    unsigned long bytes_read = 0;
    if (!fggSerialReadBuffer(4, dst, &bytes_read, &handle)) { break; }
    printf("voltage: %f\n", dst[0]);
    fggSerialSleep(5);
  }
  
  fggSerialClose(&handle);

#ifdef _WIN32
  system("pause");
#endif
  return 0;
}
