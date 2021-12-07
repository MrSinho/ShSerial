#include "fggSerial.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _WIN32
#include <termios.h>
#include <errno.h>
#endif // _WIN32

void fggSerialSleep(uint32_t ms) {
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms*1000);
#endif
}

uint8_t fggSerialOpen(const char* port, const uint16_t baud_rate, const uint32_t read_timeout_ms, const FggSerialFlags flags, FggSerialHandle* p_handle) {
#ifdef _WIN32
	char _port[10] = "\\\\.\\";
	strcat(_port, port);
	p_handle->_handle = CreateFile(_port, flags, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (p_handle->_handle == INVALID_HANDLE_VALUE) {
#ifndef NDEBUG
		printf("FggSerial error, handle %p: cannot open serial port %s\n", p_handle, port);
#endif // NDEBUG
		return 0;
	}
	DCB dcb = { 0 };
	dcb.DCBlength = sizeof(DCB);
	if (!fggSerialCheckResult(p_handle, GetCommState(p_handle->_handle, &dcb), "cannot set comm state")) { return 0; }
	dcb.BaudRate = baud_rate;
	dcb.ByteSize = 8;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;
	if (!fggSerialCheckResult(p_handle, SetCommState(p_handle->_handle, &dcb), "cannot set communication state")) { return 0; }
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = read_timeout_ms;		
	timeout.ReadTotalTimeoutMultiplier = 1;			
	timeout.ReadTotalTimeoutConstant = 0;	
	timeout.WriteTotalTimeoutConstant = 0;
    timeout.WriteTotalTimeoutMultiplier = 1;
	if (!fggSerialCheckResult(p_handle, SetCommTimeouts(p_handle->_handle, &timeout), "cannot set timeouts")) { return 0; }
	fggSerialCheckResult(p_handle, fggSerialSetReceiveMask(FGG_SERIAL_EV_RXCHAR, p_handle), "error setting receive mask");
#else
  	p_handle->fd = open(port, flags | O_NOCTTY);
	if (!fggSerialCheckResult(p_handle, p_handle->fd, "cannot open serial port")) {
		return 0;
	}
	struct termios conf = { 0 };
	tcgetattr(p_handle->fd, &conf);
	cfsetispeed(&conf, baud_rate);
	cfsetospeed(&conf, baud_rate);
	conf.c_cflag     &=  ~PARENB;            // Make 8n1
	conf.c_cflag     &=  ~CSTOPB;
	conf.c_cflag     &=  ~CSIZE;
	conf.c_cflag     |=  CS8;
	conf.c_cflag     &=  ~CRTSCTS;           // no flow control
	conf.c_cc[VMIN]   =  1;                  // read doesn't block
	conf.c_cc[VTIME]  =  (int)((float)read_timeout_ms / 100.0f); // 0.5 seconds read timeout
	conf.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
	cfmakeraw(&conf);
	tcflush(p_handle->fd, TCIFLUSH);
	tcsetattr(p_handle->fd, TCSANOW, &conf);
#endif // _WIN32
	return 1;
}

uint16_t fggSerialClose(FggSerialHandle* p_handle) {
#ifdef _WIN32
	return fggSerialCheckResult(p_handle, CloseHandle(p_handle->_handle), "cannot close serial port");
#else
	return fggSerialCheckResult(p_handle, close(p_handle->fd), "cannot close serial port");
#endif // _WIN32
}

uint16_t fggSerialReadBuffer(const uint32_t size, void* dst, unsigned long* bytes_read, FggSerialHandle* p_handle) {
#ifdef _WIN32
	return fggSerialCheckResult(p_handle, ReadFile(p_handle->_handle, dst, size, bytes_read, NULL), "cannot read from serial port");
#else
	return fggSerialCheckResult(p_handle, read(p_handle->fd, dst, size), "cannot read from serial port");
#endif // _WIN32
}


#ifdef _WIN32
uint16_t fggSerialSetReceiveMask(FggSerialCommMask mask, FggSerialHandle* p_handle) {
	if (!fggSerialCheckResult(p_handle, SetCommMask(p_handle->_handle, mask), "cannot set receive mask")) { 
		return 0; 
	} 
  	DWORD event_mask = 0;
	//for some reason waits indefinitely here sometimes
	return fggSerialCheckResult(p_handle, WaitCommEvent(p_handle->_handle, &event_mask, NULL), "cannot set waiting comm event");
}
#endif // _WIN32

uint16_t fggSerialWriteBuffer(const uint32_t size, void* src, unsigned long* p_bytes_written, FggSerialHandle* p_handle) {
#ifdef _WIN32
	return fggSerialCheckResult(p_handle, WriteFile(p_handle->_handle, src, size, p_bytes_written, NULL), "cannot write to serial port");
#else
	return fggSerialCheckResult(p_handle, write(p_handle->fd, src, size), "cannot write to serial port");
#endif // _WIN32
}


uint16_t fggSerialCheckResult(FggSerialHandle* p_handle, const int result, const char* msg) {
#ifdef _WIN32
	if (!result) {
#else
	if (result < 0) {
#endif
#ifndef NDEBUG
		printf("FggSerial error, handle 0x%p: %s, %s\n", p_handle, msg, fggSerialGetError());
#endif // NDEBUG
		return 0;		
	}
	return 1;
}

const char* fggSerialGetError() {
#ifdef _WIN32
	return "unknown error";
#else
	return strerror(errno);
#endif // _WIN32
}