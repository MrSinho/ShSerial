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



typedef enum ShSerialBaudRate {

#ifdef _WIN32 
	SH_SERIAL_BAUD_RATE_50      = 50,
	SH_SERIAL_BAUD_RATE_75      = 75,
	SH_SERIAL_BAUD_RATE_110     = 110,
	SH_SERIAL_BAUD_RATE_134     = 134,
	SH_SERIAL_BAUD_RATE_150     = 150,
	SH_SERIAL_BAUD_RATE_200     = 200,
	SH_SERIAL_BAUD_RATE_300     = 300,
	SH_SERIAL_BAUD_RATE_600     = 600,
	SH_SERIAL_BAUD_RATE_1200    = 1200,
	SH_SERIAL_BAUD_RATE_1800    = 1800,
	SH_SERIAL_BAUD_RATE_2400    = 2400,
	SH_SERIAL_BAUD_RATE_4800    = 4800,
	SH_SERIAL_BAUD_RATE_9600    = 9600,
	SH_SERIAL_BAUD_RATE_19200   = 19200,
	SH_SERIAL_BAUD_RATE_38400   = 38400,
	SH_SERIAL_BAUD_RATE_57600   = 57600,
	SH_SERIAL_BAUD_RATE_115200  = 115200,
	SH_SERIAL_BAUD_RATE_230400  = 230400,
	SH_SERIAL_BAUD_RATE_460800  = 460800,
	SH_SERIAL_BAUD_RATE_500000  = 500000,
	SH_SERIAL_BAUD_RATE_576000  = 576000,
	SH_SERIAL_BAUD_RATE_921600  = 921600,
	SH_SERIAL_BAUD_RATE_1000000 = 1000000,
	SH_SERIAL_BAUD_RATE_1152000 = 1152000,
	SH_SERIAL_BAUD_RATE_1500000 = 1500000,
	SH_SERIAL_BAUD_RATE_2000000 = 2000000,
	SH_SERIAL_BAUD_RATE_2500000 = 2500000,
	SH_SERIAL_BAUD_RATE_3000000 = 3000000,
	SH_SERIAL_BAUD_RATE_3500000 = 3500000,
	SH_SERIAL_BAUD_RATE_4000000 = 4000000,
#else
	SH_SERIAL_BAUD_RATE_50      = B50,
	SH_SERIAL_BAUD_RATE_75      = B75,
	SH_SERIAL_BAUD_RATE_110     = B110,
	SH_SERIAL_BAUD_RATE_134     = B134,
	SH_SERIAL_BAUD_RATE_150     = B150,
	SH_SERIAL_BAUD_RATE_200     = B200,
	SH_SERIAL_BAUD_RATE_300     = B300,
	SH_SERIAL_BAUD_RATE_600     = B600,
	SH_SERIAL_BAUD_RATE_1200    = B1200,
	SH_SERIAL_BAUD_RATE_1800    = B1800,
	SH_SERIAL_BAUD_RATE_2400    = B2400,
	SH_SERIAL_BAUD_RATE_4800    = B4800,
	SH_SERIAL_BAUD_RATE_9600    = B9600,
	SH_SERIAL_BAUD_RATE_19200   = B19200,
	SH_SERIAL_BAUD_RATE_38400   = B38400,
	SH_SERIAL_BAUD_RATE_57600   = B57600,
	SH_SERIAL_BAUD_RATE_115200  = B115200,
	SH_SERIAL_BAUD_RATE_230400  = B230400,
	SH_SERIAL_BAUD_RATE_460800  = B460800,
	SH_SERIAL_BAUD_RATE_500000  = B500000,
	SH_SERIAL_BAUD_RATE_576000  = B576000,
	SH_SERIAL_BAUD_RATE_921600  = B921600,
	SH_SERIAL_BAUD_RATE_1000000 = B1000000,
	SH_SERIAL_BAUD_RATE_1152000 = B1152000,
	SH_SERIAL_BAUD_RATE_1500000 = B1500000,
	SH_SERIAL_BAUD_RATE_2000000 = B2000000,
	SH_SERIAL_BAUD_RATE_2500000 = B2500000,
	SH_SERIAL_BAUD_RATE_3000000 = B3000000,
	SH_SERIAL_BAUD_RATE_3500000 = B3500000,
	SH_SERIAL_BAUD_RATE_4000000 = B4000000,
#endif//_WIN32

	SH_SERIAL_BAUD_RATE_MAX_ENUM

} ShSerialBaudRate;


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
	char*            port, 
	ShSerialBaudRate baud_rate, 
	uint32_t         read_timeout_ms, 
	ShSerialFlags    flags, 
	ShSerialHandle*  p_handle
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
