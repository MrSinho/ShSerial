#include "fggSerial.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void fggSerialOpen(const char* port, const uint16_t baudRate, const FggSerialFlags flags, FggSerialHandle handle) {

#ifdef _WIN32
	char _port[8] = "\\\\.\\";
	strcat(_port, port);
	handle._handle = CreateFileA(_port, flags, 0, NULL, OPEN_EXISTING, 0, NULL);
#ifndef NDEBUG
	if (handle._handle == INVALID_HANDLE_VALUE) {
		printf("FggSerial error: cannot open serial port %s", port);
		return;
	}
#endif // NDEBUG
#endif // _WIN32


#ifdef __linux__
	uint8_t _flags = 0;
	switch(flags) {
	  case FGG_SERIAL_READ_BIT: _flags = O_RDONLY; break;
	  case FGG_SERIAL_WRITE_BIT: _flags = O_WRONLY; break;
	  case FGG_SERIAL_READ_BIT | FGG_SERIAL_WRITE_BIT: _flags = O_RDWR; break;
  	}
  	handle.descriptor = open("/dev/ttyUSB0", (int)_flags);
#ifndef NDEBUG
	if (!handle.descriptor) {
		printf("FggSerial error: cannot open serial port %s\n", port);
		return;
	}
#endif // NDEBUG
#endif // UNIX


}

void fggSerialClose(FggSerialHandle handle) {

#ifdef _WIN32
	CloseHandle(handle._handle);
#endif

}

void fggSerialWriteBuffer(const uint32_t size, const void* src, FggSerialHandle handle) {

#ifdef _WIN32
	long unsigned int pnBytesWritten = 0;
	int result = WriteFile(handle._handle, src, size, &pnBytesWritten, NULL);
#ifndef NDEBUG
	if (!result) {
		printf("FggSerial error: cannot write to serial port, handle %p\n", handle._handle);
	}
#endif // NDEBUG
#endif // _WIN32

}

void fggSerialReadBuffer(const uint32_t size, void* dst, FggSerialHandle handle) {

#ifdef _WIN32
	long unsigned int pnBytesWritten = 0;
	int result = ReadFile(handle._handle, dst, size, &pnBytesWritten, NULL);
	if (!result) {
		printf("FggSerial error: cannot write to serial port, handle %p\n", handle._handle);
	}
#endif

}

