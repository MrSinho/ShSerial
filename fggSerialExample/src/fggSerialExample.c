#include <stdio.h>
#include <fggSerial.h>
#include <stdlib.h>

#include <stdio.h>

int main(void) {

  int result = 0;

  printf("connecting to serial port\n");
  FggSerialHandle handle = {0};
  result = fggSerialOpen("/dev/tty/ACM0", 9600, 8, 100, 500, FGG_SERIAL_READ_BIT | FGG_SERIAL_WRITE_BIT, &handle);
  
  //print read data
  printf("waiting for incoming data...\n");
  float dst[1];
  for (;;) {
    unsigned long bytes_read = 0;
    fggSerialReadBuffer(4, dst, &bytes_read, &handle);
    printf("voltage: %f\n", dst[0]);
  }
  
  result = fggSerialClose(&handle);

  return 0;
}
