#ifndef FGG_SERIAL_H
#define FGG_SERIAL_H

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef __linux__
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif // UNIX

#include <stdint.h>


typedef enum FggSerialFlags {

#ifdef _WIN32
  FGG_SERIAL_READ_BIT  = GENERIC_READ,
  FGG_SERIAL_WRITE_BIT = GENERIC_WRITE,
#endif // _WIN32

#ifdef __linux__
  FGG_SERIAL_READ_BIT   = 0b00001,
  FGG_SERIAL_WRITE_BIT  = 0b00010,
#endif // UNIX


} FggSerialFlags;


typedef struct FggSerialHandle {

#ifdef _WIN32
  HANDLE _handle;
#endif

#ifdef __linux__
  int descriptor;
#endif // UNIX

} FggSerialHandle;


extern void fggSerialOpen(const char* port, const uint16_t baud_rate, const uint32_t n_bits_x_call, const uint32_t max_byte_interval, const uint32_t max_timeout, const FggSerialFlags flags, FggSerialHandle* handle);

extern void fggSerialClose(FggSerialHandle* handle);

extern void fggSerialWriteBuffer(const uint32_t size, const void* src, FggSerialHandle handle);

extern void fggSerialReadBuffer(const uint32_t size, void* dst, FggSerialHandle handle);


#endif // FGG_UART_H
