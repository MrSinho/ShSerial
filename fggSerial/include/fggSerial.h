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
  FGG_SERIAL_READ  = GENERIC_READ,
  FGG_SERIAL_WRITE = GENERIC_WRITE,
  FGG_SERIAL_READ_WRITE = GENERIC_READ | GENERIC_WRITE,
#endif // _WIN32

#ifdef __linux__
  FGG_SERIAL_READ   = O_RDONLY,
  FGG_SERIAL_WRITE  = O_WRONLY,
  FGG_SERIAL_READ_WRITE = O_RDWR,
#endif // __linux__


} FggSerialFlags;


typedef struct FggSerialHandle {

#ifdef _WIN32
  HANDLE _handle;
#endif

#ifdef __linux__
  int fd;
#endif // UNIX

} FggSerialHandle;


#ifdef _WIN32

typedef enum FggSerialCommMask {

  FGG_SERIAL_EV_BREAK     = EV_BREAK   ,		
  FGG_SERIAL_EV_CTS       = EV_CTS     ,			
  FGG_SERIAL_EV_DSR       = EV_DSR     ,			
  FGG_SERIAL_EV_ERR       = EV_ERR     ,			
  FGG_SERIAL_EV_EVENT1    = EV_EVENT1  ,		
  FGG_SERIAL_EV_EVENT2    = EV_EVENT2  ,		
  FGG_SERIAL_EV_PERR      = EV_PERR    , 		
  FGG_SERIAL_EV_RING      = EV_RING    , 		
  FGG_SERIAL_EV_RLSD      = EV_RLSD    , 		
  FGG_SERIAL_EV_RX80FULL  = EV_RX80FULL,	
  FGG_SERIAL_EV_RXCHAR    = EV_RXCHAR  ,		
  FGG_SERIAL_EV_RXFLAG    = EV_RXFLAG  ,		
  FGG_SERIAL_EV_TXEMPTY   = EV_TXEMPTY ,	

} FggSerialCommMask;

extern uint16_t fggSerialSetReceiveMask(FggSerialCommMask mask, FggSerialHandle* p_handle);

#endif // _WIN32

extern void fggSerialSleep(uint32_t ms);

extern uint8_t fggSerialOpen(const char* port, const uint16_t baud_rate, const uint32_t read_timeout, const FggSerialFlags flags, FggSerialHandle* p_handle);

extern uint16_t fggSerialWriteBuffer(const uint32_t size, void* src, FggSerialHandle* p_handle);

extern uint16_t fggSerialReadBuffer(const uint32_t size, void* dst, unsigned long* bytes_read, FggSerialHandle* p_handle);

extern uint16_t fggSerialClose(FggSerialHandle* p_handle);

extern uint16_t fggSerialCheckResult(FggSerialHandle* p_handle, const int result, const char* msg);

extern const char* fggSerialTranslateError();

#endif // FGG_UART_H
