#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <windows.h>

using namespace std;

void initConsole() 
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONIN$", "r", stdin);
    freopen_s(&f, "CONOUT$", "w", stdout); 
    freopen_s(&f, "CONOUT$", "w", stderr);
}

int main(int argc, char*argv[]) 
{
    initConsole();
    cout << "Sender process started..." << endl;

    HANDLE hMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, L"SyncMutex");
    HANDLE hFull = OpenSemaphoreW(SEMAPHORE_ALL_ACCESS, FALSE, L"FullSemaphore");
    HANDLE hEmpty = OpenSemaphoreW(SEMAPHORE_ALL_ACCESS, FALSE, L"EmptySemaphore");
    if (hMutex == NULL) {
        cout << "Open mutex error";
        return GetLastError();
    }
    if (hFull == NULL) {
        cout << "Open semaphore named full error";
        return GetLastError();
    }
    if (hEmpty == NULL) {
        cout << "Open semaphore named empty error";
        return GetLastError();
    }

    // Сигнал на готовность к работе
    cout << "Waiting for mutex..." << endl;
    WaitForSingleObject(hMutex, INFINITE);
    ReleaseMutex(hMutex);
    cout << "Mutex released, ready to work!" << endl;

    string message;
    string command;
    string ans;
    while (true) {
        cout << "Enter the command(send/exit): ";
        cin >>command;

        /*if (ans == "exit") break;
        else  {
            WaitForSingleObject(hEmpty, INFINITE);
            WaitForSingleObject(hMutex, INFINITE);
            ofstream out(argv[1],ios::app,ios::binary);
            out.write(ans.data(), 20);
            out.close();*/
        if (command == "exit" || command == "2")
            break;
        else 
            if (command == "send" || command == "1") 
            {
            cout << "Enter the message (less than 20 symbols): "; 
            cin.ignore();
            // Убираем остаточные символы новой строки из буфера 
            getline(cin, message);
            if (message.length() < 20)
            {
                cout << "Waiting for empty semaphore..." << endl;
                WaitForSingleObject(hEmpty, INFINITE);
                cout << "Empty semaphore acquired!" << endl;
                WaitForSingleObject(hMutex, INFINITE);
                ofstream out(argv[1], ios::app | ios::binary);
                out.write(message.c_str(), message.length());
                out.close();
                ReleaseMutex(hMutex);
                ReleaseSemaphore(hFull, 1, NULL);
                cout << "The message is delivered" << endl;
            }
            else {
                cout << "The message is too long.Try again..." << endl;
            }
            }
            else {
                cout << "Incorrect command.Try again..." << endl;
            }
    }

    return 0;
}
