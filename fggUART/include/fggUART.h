#ifndef FGG_UART_H
#define FGG_UART_H

#ifdef _WIN32
  #include <windows.h>
#endif

#include <stdint.h>


typedef enum FggSerialFlags {

#ifdef _WIN32
  FGG_SERIAL_READ_BIT  = GENERIC_READ,
  FGG_SERIAL_WRITE_BIT = GENERIC_WRITE
#endif

} FggSerialFlags;


typedef struct FggSerialHandle {

#ifdef _WIN32
  HANDLE _handle;
#endif

} FggSerialHandle;


extern void fggSerialOpen(const char* port, const FggSerialFlags flags, FggSerialHandle handle);

extern void fggSerialClose(FggSerialHandle handle);

extern void fggSerialWriteBuffer(const uint32_t size, const void* src, FggSerialHandle handle);

extern void fggSerialReadBuffer(const uint32_t size, void* dst, FggSerialHandle handle);

#endif // FGG_UART_H
