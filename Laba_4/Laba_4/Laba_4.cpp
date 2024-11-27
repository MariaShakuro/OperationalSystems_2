// Laba_4.cpp: определяет точку входа для приложения.
//"Синхронизация процессов"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "Laba_4.h"

using namespace std;
string convertWideStringToString(const wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size_needed, NULL, NULL);
    return str;
}

int main() {
    HANDLE hMutex, hFull, hEmpty;
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    wchar_t fileName[50];

    wstring fileN;
    int recNum, receiverNum;
    cout << "Enter a name of binary file: ";
    wcin >> fileN;
    cout << "Enter count of notes in binary file: ";
    cin >> recNum;
    if (recNum < 1) {
        cout << "Incorrect number of files";
        return 1;
    }

    wstring s = L"../Sender/Sender.exe " + fileN;
    wcsncpy(fileName, s.c_str(),s.size()+1);

    ofstream createBinFile(fileN, ios::binary);
    createBinFile.close();

    hMutex = CreateMutexW(NULL, FALSE, L"SyncMutex");
    hFull = CreateSemaphoreW(NULL, 0, recNum, L"FullSemaphore");
    hEmpty = CreateSemaphoreW(NULL, recNum, recNum, L"EmptySemaphore");
    if (hMutex == NULL) {
        cout << "Error of creation a mutex" << endl;
        return GetLastError();
    }
    cout << "Mutex created and waiting to be released..." << endl;
    WaitForSingleObject(hMutex,INFINITE);

    ReleaseMutex(hMutex); // Освобождаем мьютекс сразу после захвата
    cout << "Mutex released." << endl;

    cout << "Enter the count of processes Sender: ";
    cin >> receiverNum;
    if (receiverNum < 1) {
        cout << "Incorrect number of processes";
        return 1;
    }

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    // Определение массива hProcessors
    HANDLE* hProcessors = new HANDLE[receiverNum];
    for (int i = 0; i < receiverNum; i++) {
        if (!CreateProcessW(NULL, fileName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
            cout << "Error of creation processes " << i << endl;
            return GetLastError();
        }
        hProcessors[i] = pi.hProcess;
        CloseHandle(pi.hThread);
    }
    Sleep(100);
   /* if (receiverNum == 1) WaitForSingleObject(hProcessors[0], INFINITE);
    else WaitForMultipleObjects(receiverNum, hProcessors, TRUE, INFINITE);*/

    ifstream inBinFile;
    ofstream outBinFile;
   //ReleaseMutex(hMutex);
    string userAns;
    char *fileElem=new char[20];
    string deleting;
    while (true) {
        cout << "Enter the command(exit/read): ";
        cin >> userAns;

        if (userAns == "exit") {
            for (int i = 0; i < receiverNum; i++) {
                TerminateProcess(hProcessors[i], 1);
                CloseHandle(hProcessors[i]);
            }
            break;
        }
        else {
            WaitForSingleObject(hFull, INFINITE);
            WaitForSingleObject(hMutex, INFINITE);
            inBinFile.open(fileN, ios::binary);
            inBinFile.read(fileElem, 20);
            inBinFile >> deleting;
            if (strcmp(fileElem, deleting.data()) == 0)
                deleting = "";
            inBinFile.close();

            outBinFile.open(fileN, ios::binary);
            outBinFile.clear();
            outBinFile.write(deleting.data(), deleting.size());
            outBinFile.close();
            cout <<fileElem<< endl;
            ReleaseMutex(hMutex);
            ReleaseSemaphore(hEmpty, 1, NULL);
        }
    }

    WaitForMultipleObjects(receiverNum,&pi.hProcess, TRUE, INFINITE);

    delete[] fileElem; delete[] hProcessors;

    /*for (int i = 0; i < receiverNum; i++) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }*/
    CloseHandle(hMutex);
    CloseHandle(hFull);
    CloseHandle(hEmpty);
    inBinFile.close();

   // return 0;
}
