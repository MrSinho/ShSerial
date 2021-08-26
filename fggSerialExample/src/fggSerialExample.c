#include <fggSerial.h>
#include <stdlib.h>

int main(void) {

  FggSerialHandle handle = {0};
  fggSerialOpen("\\\\.\\COM1", 9600, FGG_SERIAL_READ_BIT | FGG_SERIAL_WRITE_BIT, handle);
  
  char buff[1] = { 'w' };
  fggSerialWriteBuffer(1, buff, handle);

  system("pause");

  return 0;
}
