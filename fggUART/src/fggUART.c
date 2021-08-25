#include "fggUART.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void fggSerialOpen(const char* port, const FggSerialFlags flags, FggSerialHandle handle) {

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

