#include <fggSerial.h>
#include <stdlib.h>

#include <stdio.h>

int main(void) {

  FggSerialHandle handle = {0};
  fggSerialOpen("COM8", 9600, 8, 100, 500, FGG_SERIAL_READ_BIT | FGG_SERIAL_WRITE_BIT, &handle);
  Sleep(500);
  //char buff[1] = { 'w' };
  //fggSerialWriteBuffer(1, buff, handle);

  char dst[4];
  fggSerialReadBuffer(3, dst, handle);
  dst[3] = '\0';
  printf("%s", dst);
  printf("\n");

  fggSerialClose(&handle);

  system("pause");

  return 0;
}
