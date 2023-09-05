#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "shserial/shSerial.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _WIN32
#include <termios.h>
#include <errno.h>
#endif // _WIN32

#ifdef _MSC_VER
#pragma warning (disable: 28193 4996)
#endif // _MSC_VER



void shSerialSleep(
	uint32_t ms
) {
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms*1000);
#endif
}

uint8_t shSerialOpen(
	char*           port, 
	uint32_t        baud_rate, 
	uint32_t        read_timeout_ms, 
	ShSerialFlags   flags, 
	ShSerialHandle* p_handle
) {
	shSerialError(
		p_handle == NULL,
		"shSerialOpen: invalid handle memory",
		return 0
	);

	shSerialError(
		port == NULL,
		"shSerialOpen: invalid port memory",
		return 0
	);



#ifdef _WIN32

	BOOL r         = 0;
	char _port[32] = "\\\\.\\";
	
	strcat(_port, port);

	(*p_handle) = CreateFile(
		_port,                 //lpFileName
		flags,                 //dwDesiredAccess
		0,                     //dwShareMode
		NULL,                  //lpSecurityAttributes
		OPEN_EXISTING,         //dwCreationDisposition
		0,                     //dwFlagsAndAttributes
		NULL                   //hTemplateFile
	);
	
	shSerialError(
		(*p_handle) == SH_SERIAL_NULL_HANDLE,
		"shSerialOpen: cannot open serial port",
		return 0
	);

	DCB src_dcb = { 0 };

	r = GetCommState(
		(*p_handle), //hFile
		&src_dcb     //lpDCB
	);

	shSerialError(
		shSerialBadResult(r),
		"shSerialOpen: failed getting current device control block",
		return 0
	);

	src_dcb.BaudRate = baud_rate;
	src_dcb.StopBits = ONESTOPBIT;
	src_dcb.Parity   = NOPARITY;
	src_dcb.ByteSize = 8;

	r = SetCommState(
		(*p_handle), //hFile
		&src_dcb     //lpDCB
	);

	shSerialError(
		shSerialBadResult(r),
		"shSerialOpen: failed setting device control block",
		return 0
	);

	COMMTIMEOUTS timeout = {
		read_timeout_ms, //ReadIntervalTimeout
		1,               //ReadTotalTimeoutMultiplier
		1,               //ReadTotalTimeoutConstant
		1,               //WriteTotalTimeoutMultiplier
		1                //WriteTotalTimeoutConstant
	};
	
	r = SetCommTimeouts(
		(*p_handle), //hFile
		&timeout     //lpCommTimeouts
	);

	shSerialError(
		shSerialBadResult(r),
		"shSerialOpen: cannot set timeouts",
		return 0
	);

#else

	int r = 0;

	(*p_handle) = open(
		port,            //pathname
		flags | O_NOCTTY //flags
	);

	shSerialError(
		(*p_handle) == SH_SERIAL_NULL_HANDLE,
		"shSerialOpen: cannot open serial port",
		return 0
	);

	struct termios dcb = { 0 };

	r = tcgetattr(
		(*p_handle), //fd 
		&dcb         //termios_p
	);

	shSerialError(
		shSerialBadResult(r),
		"shSerialOpen: failed getting current device control block",
		return 0
	);

	r = cfsetispeed(
		&dcb,     //termios_p
		baud_rate //speed
	);
	
	r += cfsetospeed(
		&dcb,     //termios_p
		baud_rate //speed
	);

	shSerialError(
		shSerialBadResult(r),
		"shSerialOpen: failed setting baud rate",
		return 0
	);

	dcb.c_cflag     &=  ~PARENB;            // Make 8n1
	dcb.c_cflag     &=  ~CSTOPB;
	dcb.c_cflag     &=  ~CSIZE;
	dcb.c_cflag     |=  CS8;
	dcb.c_cflag     &=  ~CRTSCTS;           // no flow control
	dcb.c_cc[VMIN]   =  1;                  // read doesn't block
	dcb.c_cc[VTIME]  =  (int)((float)read_timeout_ms / 100.0f); // 0.5 seconds read timeout
	dcb.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
	
	r = cfmakeraw(
		&dcb //termios_p
	);
	
	shSerialError(
		shSerialBadResult(r),
		"shSerialOpen: failed setting device control block",
		return 0
	);

	r = tcflush(
		(*p_handle), //fd
		TCIFLUSH     //queue_selector
	);

	shSerialError(
		shSerialBadResult(r),
		"shSerialOpen: failed setting queue selector",
		return 0
	);
	
	r = tcsetattr(
		(*p_handle), //fd
		TCSANOW,     //optional_actions
		&dcb         //termios_p
	);

	shSerialError(
		shSerialBadResult(r),
		"shSerialOpen: failed setting device control block",
		return 0
	);

#endif//WIN32

	return 1;
}

uint8_t shSerialClose(
	ShSerialHandle handle
) {
	shSerialError(
		handle == SH_SERIAL_NULL_HANDLE,
		"shSerialRead: invalid handle memory",
		return 0
	);


#ifdef _WIN32

	BOOL r = 0;

	r = CloseHandle(handle);

#else

	int r = 0;

	r = close(handle);

#endif//_WIN32

	shSerialError(
		shSerialBadResult(r),
		"shSerialRead: failed closing serial port",
		return 0
	);

	return 1;
}

uint8_t shSerialRead(
	uint32_t       size, 
	void*          dst,
	uint32_t*      p_bytes_read,
	ShSerialHandle handle
) {
	shSerialError(
		handle == SH_SERIAL_NULL_HANDLE,
		"shSerialRead: invalid handle memory",
		return 0
	);

	shSerialError(
		size == 0,
		"shSerialRead: invalid read size",
		return 0
	)

	shSerialError(
		dst == NULL,
		"shSerialRead: invalid dst memory",
		return 0
	)

#ifdef _WIN32

	BOOL  r          = 0;
	DWORD bytes_read = 0;

	r = ReadFile(
		handle,      //hFile
		dst,         //lpBuffer
		size,        //nNumberOfBytesToRead
		&bytes_read, //lpNumberOfBytesRead
		NULL         //lpOverlapped
	);

#else

	uint8_t  r          = 1;
	uint32_t bytes_read = 0;

	bytes_read = (uint32_t)read(
		handle, //fd
		dst,    //
		size    //
	);

#endif//_WIN32

	if (p_bytes_read != NULL) {
		(*p_bytes_read) = (uint32_t)bytes_read;
	}

	shSerialError(
		shSerialBadResult(r),
		"shSerialRead: failed reading from serial port",
		return 0
	);

	return 1;
}

uint8_t shSerialWrite(
	uint32_t       size, 
	void*          src, 
	uint32_t*      p_bytes_written,
	ShSerialHandle handle
) {
	shSerialError(
		handle == SH_SERIAL_NULL_HANDLE,
		"shSerialWrite: invalid handle memory",
		return 0
	);

	shSerialError(
		size == 0,
		"shSerialWrite: invalid read size",
		return 0
	)

	shSerialError(
		src == NULL,
		"shSerialWrite: invalid dst memory",
		return 0
	)


#ifdef _WIN32

	BOOL  r             = 0;
	DWORD bytes_written = 0;

	bytes_written = WriteFile(
		handle,         //hFile
		src,            //lpBuffer
		size,           //nNumberOfBytesToWrite
		&bytes_written, //lpNumberOfBytesWritten
		NULL            //lpOverlapped
	);

#else

	uint8_t  r             = 1;
	uint32_t bytes_written = 0;

	bytes_written = (uint32_t)write(
		handle, //fd
		src,    //
		size    //
	);

#endif // _WIN32

	if (p_bytes_written != 0) {
		(*p_bytes_written) = (uint32_t)bytes_written;
	}

	shSerialError(
		shSerialBadResult(r),
		"shSerialWrite: failed writing to serial port",
		return 0
	);

	return 1;
}

char* shSerialGetError() {
#ifdef _WIN32
	return "unknown error";
#else
	return strerror(errno);
#endif // _WIN32
}



#ifdef __cplusplus
}
#endif//__cplusplus