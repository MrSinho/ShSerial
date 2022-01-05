#ifndef SH_SERIAL_H
#define SH_SERIAL_H

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef __linux__
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif // UNIX

#include <stdint.h>


typedef enum ShSerialFlags {

#ifdef _WIN32
  SH_SERIAL_READ  = GENERIC_READ,
  SH_SERIAL_WRITE = GENERIC_WRITE,
  SH_SERIAL_READ_WRITE = GENERIC_READ | GENERIC_WRITE,
#endif // _WIN32

#ifdef __linux__
  SH_SERIAL_READ   = O_RDONLY,
  SH_SERIAL_WRITE  = O_WRONLY,
  SH_SERIAL_READ_WRITE = O_RDWR,
#endif // __linux__


} ShSerialFlags;


typedef struct ShSerialHandle {

#ifdef _WIN32
  HANDLE _handle;
#endif

#ifdef __linux__
  int fd;
#endif // UNIX

} ShSerialHandle;


#ifdef _WIN32

typedef enum ShSerialCommMask {

  SH_SERIAL_EV_BREAK     = EV_BREAK   ,		
  SH_SERIAL_EV_CTS       = EV_CTS     ,			
  SH_SERIAL_EV_DSR       = EV_DSR     ,			
  SH_SERIAL_EV_ERR       = EV_ERR     ,			
  SH_SERIAL_EV_EVENT1    = EV_EVENT1  ,		
  SH_SERIAL_EV_EVENT2    = EV_EVENT2  ,		
  SH_SERIAL_EV_PERR      = EV_PERR    , 		
  SH_SERIAL_EV_RING      = EV_RING    , 		
  SH_SERIAL_EV_RLSD      = EV_RLSD    , 		
  SH_SERIAL_EV_RX80FULL  = EV_RX80FULL,	
  SH_SERIAL_EV_RXCHAR    = EV_RXCHAR  ,		
  SH_SERIAL_EV_RXFLAG    = EV_RXFLAG  ,		
  SH_SERIAL_EV_TXEMPTY   = EV_TXEMPTY ,	

} ShSerialCommMask;

extern uint16_t shSerialSetReceiveMask(ShSerialCommMask mask, ShSerialHandle* p_handle);

#endif // _WIN32

extern void shSerialSleep(uint32_t ms);

extern uint8_t shSerialOpen(const char* port, const uint16_t baud_rate, const uint32_t read_timeout_ms, const ShSerialFlags flags, ShSerialHandle* p_handle);

extern uint16_t shSerialWriteBuffer(const uint32_t size, void* src, unsigned long* p_bytes_written, ShSerialHandle* p_handle);

extern uint16_t shSerialReadBuffer(const uint32_t size, void* dst, unsigned long* bytes_read, ShSerialHandle* p_handle);

extern uint16_t shSerialClose(ShSerialHandle* p_handle);

extern uint16_t shSerialCheckResult(ShSerialHandle* p_handle, const int result, const char* msg);

extern const char* shSerialGetError();

#endif // SH_UART_H
