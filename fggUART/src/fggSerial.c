#include "fggSerial.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void fggSerialOpen(const char* port, const uint16_t baud_rate, const uint32_t n_bits_x_call, const uint32_t max_byte_interval, const uint32_t max_timeout, const FggSerialFlags flags, FggSerialHandle* handle) {

#ifdef _WIN32
	char _port[8] = "\\\\.\\";
	strcat(_port, port);
	handle->_handle = CreateFile(_port, flags, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (handle->_handle == INVALID_HANDLE_VALUE) {
#ifndef NDEBUG
		printf("FggSerial error: cannot open serial port %s\n", port);
#endif // NDEBUG
		return;
	}

	PurgeComm(handle->_handle, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

	//settings
	DCB dcb = { 0 };
	dcb.DCBlength = sizeof(DCB);
	dcb.BaudRate 	= baud_rate;
	dcb.ByteSize 	= (BYTE)n_bits_x_call;
	dcb.Parity		= 0;
	dcb.StopBits 	= ONESTOPBIT;
	int result = SetCommState(handle->_handle, &dcb);
	if (!result) {
#ifndef NDEBUG
		printf("FggSerial error: cannot set communication state on serial port %s\n", port);
#endif // NDEBUG
		return;
	}

	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = max_byte_interval;		
	timeout.ReadTotalTimeoutMultiplier = 1;			
	timeout.ReadTotalTimeoutConstant = max_timeout;		
	result = SetCommTimeouts(handle->_handle, &timeout);
	if (!result) {
		printf("FggSerial error: cannot set timeouts on port %s\n", port);
	}

	PurgeComm(handle->_handle, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

#endif // _WIN32


#ifdef __linux__
	uint8_t _flags = 0;
	switch(flags) {
	  case FGG_SERIAL_READ_BIT: _flags = O_RDONLY; break;
	  case FGG_SERIAL_WRITE_BIT: _flags = O_WRONLY; break;
	  case FGG_SERIAL_READ_BIT | FGG_SERIAL_WRITE_BIT: _flags = O_RDWR; break;
  	}
  	handle.descriptor = open("/dev/ttyUSB0", (int)_flags);
	if (!handle.descriptor) {
#ifndef NDEBUG
		printf("FggSerial error: cannot open serial port %s\n", port);
#endif // NDEBUG
		return;
	}

#endif // __linux__
}

void fggSerialClose(FggSerialHandle* handle) {

#ifdef _WIN32
	PurgeComm(handle->_handle, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
	CloseHandle(handle->_handle);
#endif

}

void fggSerialWriteBuffer(const uint32_t size, const void* src, FggSerialHandle handle) {

#ifdef _WIN32
	unsigned long bytes_written = 0;
	int result = WriteFile(handle._handle, src, size, &bytes_written, NULL);
#ifndef NDEBUG
	if (!result) {
		printf("FggSerial error: cannot write to serial port, handle %p\n", handle._handle);
	}
#endif // NDEBUG
#endif // _WIN32

}

void fggSerialReadBuffer(const uint32_t size, void* dst, FggSerialHandle handle) {

#ifdef _WIN32
	unsigned long bytes_read = 0;
	int result = ReadFile(handle._handle, dst, size, &bytes_read, NULL);
#ifndef NDEBUG
	if (!result) {
		uint32_t error = GetLastError();
		char error_s[256];
		switch(error) {
			case ERROR_INVALID_HANDLE: 
				strcpy(error_s, "invalid handle");
				break;
			case ERROR_INVALID_USER_BUFFER:
				strcpy(error_s, "invalid user buffer");
				break;
			case ERROR_NOT_ENOUGH_MEMORY:
				strcpy(error_s, "not enough memory");
				break;
			case ERROR_INSUFFICIENT_BUFFER: 
				strcpy(error_s, "insufficient buffer");
				break;
		}
		printf("FggSerial error: cannot read from serial port, %s\n", error_s);
	}
#endif // NDEBUG
#endif // _WIN32

}

