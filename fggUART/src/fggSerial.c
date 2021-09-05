#include "fggSerial.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void fggSerialOpen(const char* port, const uint16_t baud_rate, const uint32_t n_bits_x_call, const uint32_t max_byte_interval, const uint32_t max_timeout, const FggSerialFlags flags, FggSerialHandle* p_handle) {

#ifdef _WIN32
	char _port[10] = "\\\\.\\";
	strcat(_port, port);
	p_handle->_handle = CreateFile(_port, flags, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (p_handle->_handle == INVALID_HANDLE_VALUE) {
#ifndef NDEBUG
		printf("FggSerial error: cannot open serial port %s\n", port);
#endif // NDEBUG
		return;
	}

	//settings
	DCB dcb = { 0 };
	dcb.DCBlength = sizeof(DCB);
	int result = GetCommState(p_handle->_handle, &dcb); //retreives  the current settings
    if (!result) {
#ifndef NDEBUG
        printf("FggSerial error: cannot get com state for port %s\n", port);
#endif // NDEBUG
		return;
    }
	dcb.BaudRate = baud_rate;
	dcb.ByteSize = n_bits_x_call;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;
	result = SetCommState(p_handle->_handle, &dcb);
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
	timeout.WriteTotalTimeoutConstant = max_timeout;
    timeout.WriteTotalTimeoutMultiplier = 1;	
	result = SetCommTimeouts(p_handle->_handle, &timeout);
	if (!result) {
		printf("FggSerial error: cannot set timeouts on port %s\n", port);
	}

	//comm mask

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
	CloseHandle(handle->_handle);
#endif // _WIN32
}

void fggSerialReadBuffer(const uint32_t size, void* dst, unsigned long* bytes_read, FggSerialHandle p_handle) {
#ifdef _WIN32
	int result = ReadFile(p_handle._handle, dst, size, bytes_read, NULL);
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

void fggSerialSetReceiveMask(FggSerialHandle* p_handle, FggSerialCommMask mask) {
#ifdef _WIN32
	  int result = SetCommMask(p_handle->_handle, mask);
  	if (!result) {
#ifndef NDEBUG
		printf("FggSerial error: cannot set receive mask\n");
#endif // NDEBUG
		return;
	  }
  	//Setting WaitComm() Event
  	DWORD event_mask = 0;
  	result = WaitCommEvent(p_handle->_handle, &event_mask, NULL); //Wait for the character to be received
  	if (!result) {
#ifndef NDEBUG
		printf("FggSerial error while waiting for comm event\n");
#endif // NDEBUG
		return;
  	}
#endif // _WIN32
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