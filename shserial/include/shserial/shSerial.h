#ifndef SH_SERIAL_H
#define SH_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifdef _WIN32

#include <windows.h>

#else

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#endif//_WIN32


#include <stdint.h>



#ifdef _WIN32
	#define shSerialBadResult(result) ((result) < 1)
#else
	#define shSerialBadResult(result) ((result) < 0)
#endif//_WIN32


#define shSerialError(condition, error_msg, failure_expression)\
	if ((int)(condition)) {\
		printf("shserial error: %s, %s.\n", error_msg, shSerialGetError()); failure_expression;\
	}



typedef enum ShSerialFlags {
#ifdef _WIN32

	SH_SERIAL_READ       = GENERIC_READ,
	SH_SERIAL_WRITE      = GENERIC_WRITE,
	SH_SERIAL_READ_WRITE = GENERIC_READ | GENERIC_WRITE,

#else
  
	SH_SERIAL_READ       = O_RDONLY,
	SH_SERIAL_WRITE      = O_WRONLY,
	SH_SERIAL_READ_WRITE = O_RDWR,

#endif//_WIN32
} ShSerialFlags;



#ifdef _WIN32

typedef HANDLE ShSerialHandle;
#define SH_SERIAL_NULL_HANDLE NULL

#else

typedef int ShSerialHandle;
#define SH_SERIAL_NULL_HANDLE 0

#endif//_WIN32



#ifdef _WIN32

typedef enum ShSerialCommMask {
	SH_SERIAL_EV_BREAK     = EV_BREAK,		
	SH_SERIAL_EV_CTS       = EV_CTS,			
	SH_SERIAL_EV_DSR       = EV_DSR,			
	SH_SERIAL_EV_ERR       = EV_ERR,			
	SH_SERIAL_EV_EVENT1    = EV_EVENT1,		
	SH_SERIAL_EV_EVENT2    = EV_EVENT2,		
	SH_SERIAL_EV_PERR      = EV_PERR, 		
	SH_SERIAL_EV_RING      = EV_RING, 		
	SH_SERIAL_EV_RLSD      = EV_RLSD, 		
	SH_SERIAL_EV_RX80FULL  = EV_RX80FULL,	
	SH_SERIAL_EV_RXCHAR    = EV_RXCHAR,		
	SH_SERIAL_EV_RXFLAG    = EV_RXFLAG,		
	SH_SERIAL_EV_TXEMPTY   = EV_TXEMPTY,	
} ShSerialCommMask;

#endif//_WIN32



extern void shSerialSleep(
	uint32_t ms
);

extern uint8_t shSerialOpen(
	char*           port, 
	uint32_t        baud_rate, 
	uint32_t        read_timeout_ms, 
	ShSerialFlags   flags, 
	ShSerialHandle* p_handle
);

extern uint8_t shSerialWrite(
	uint32_t       size, 
	void*          src, 
	uint32_t*      p_bytes_written,
	ShSerialHandle handle
);

extern uint8_t shSerialRead(
	uint32_t        size, 
	void*           dst,
	uint32_t*       p_bytes_read,
	ShSerialHandle  handle
);

extern uint8_t shSerialClose(
	ShSerialHandle handle
);

extern char* shSerialGetError();




#ifdef __cplusplus
}
#endif//__cplusplus

#endif//SH_SERIAL_H
