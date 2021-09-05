#include <fggSerial.h>
#include <stdlib.h>

#include <stdio.h>

int main(void) {

  FggSerialHandle handle = {0};
  fggSerialOpen("COM8", 9600, 8, 100, 500, FGG_SERIAL_READ_BIT | FGG_SERIAL_WRITE_BIT, &handle);
  Sleep(500);

  fggSerialSetReceiveMask(&handle, FGG_SERIAL_EV_RXCHAR);

  char dst[4];
  unsigned long bytes_read = 0;
  fggSerialReadBuffer(3, dst, &bytes_read, handle);
  printf("read %i bytes\n", bytes_read);
  dst[3] = '\0';
  printf("%s", dst);
  printf("\n");
  Sleep(20);
  

  fggSerialClose(&handle);

  system("pause");

  return 0;
}
