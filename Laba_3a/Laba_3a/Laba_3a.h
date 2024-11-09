#ifndef LABA_3A_H
#define LABA_3A_H 
#include <Windows.h>

struct INFO {
	int threadId;
	int* array;
	int arraySize;
	HANDLE startEvent;
	HANDLE pauseEvent;
	HANDLE stopEvent;
	HANDLE continueEvent;
};
DWORD WINAPI MarkerThread(LPVOID param);
extern HANDLE outputMutex;

#endif // LABA_3A_H

