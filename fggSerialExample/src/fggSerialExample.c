#include <fggSerial.h>
#include <stdlib.h>

#include <stdio.h>

int main(void) {

  int result = 0;

  FggSerialHandle handle = {0};
  result = fggSerialOpen("COM8", 9600, 8, 100, 500, FGG_SERIAL_READ_BIT | FGG_SERIAL_WRITE_BIT, &handle);
  if (!result) { system("pause"); }
  
  Sleep(500);
  result = fggSerialSetReceiveMask(FGG_SERIAL_EV_RXCHAR, &handle);
  if (!result) { system("pause"); }

  //print read data
  char dst[1];
  for (;;) {
    unsigned long bytes_read = 0;
    result = fggSerialReadBuffer(1, dst, &bytes_read, &handle);
    if (!result) { system("pause"); }
    
    printf("%c", dst[0]);
    Sleep(10);
  }
  
  
  result = fggSerialClose(&handle);
  if (!result) { system("pause"); }

  system("pause");

  return 0;
}
