#include <fggSerial.h>
#include <stdlib.h>

#include <stdio.h>

int main(void) {

  FggSerialHandle handle = {0};
  fggSerialOpen("COM8", 9600, 8, 100, 500, FGG_SERIAL_READ_BIT | FGG_SERIAL_WRITE_BIT, &handle);
  Sleep(500);

  fggSerialSetReceiveMask(&handle, FGG_SERIAL_EV_RXCHAR);



  //print read data
  char dst[1];
  for (;;) {
    unsigned long bytes_read = 0;
    fggSerialReadBuffer(1, dst, &bytes_read, handle);
    printf("%c", dst[0]);
    Sleep(10);
  }
  
  

  fggSerialClose(&handle);

  system("pause");

  return 0;
}
