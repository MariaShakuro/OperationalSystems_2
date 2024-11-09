#include "Laba_3a.h"
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

HANDLE outputMutex;

DWORD WINAPI MarkerThread(LPVOID param) {
    INFO* info = (INFO*)param;
    srand(info->threadId);
    while (true) {
        WaitForSingleObject(info->startEvent, INFINITE);
        while (true) {
            int randValue = rand();
            int index = randValue % info->arraySize;

            if (info->array[index] == 0) {
                Sleep(5);
                info->array[index] = info->threadId;
                Sleep(5);
            }
            else {
                int markedCount = 0;
                for (int i = 0; i < info->arraySize; i++) {
                    if (info->array[i] == info->threadId)
                        markedCount++;
                }
                WaitForSingleObject(outputMutex, INFINITE);
                cout << "Поток " <<info->threadId << " не смог пометить индекс " << index + 1 << ". Количество помеченных элементов: " << markedCount << "\n";
                ReleaseMutex(outputMutex);

                SetEvent(info->pauseEvent);

                HANDLE events[2] = { info->continueEvent, info->stopEvent };
                DWORD result = WaitForMultipleObjects(2, events, FALSE, INFINITE);

                if (result == WAIT_OBJECT_0 + 1) {
                    for (int i = 0; i < info->arraySize; i++)
                        if (info->array[i] == info->threadId)
                            info->array[i] = 0;
                    return 0;
                }
                else {
                    ResetEvent(info->continueEvent);
                    ResetEvent(info->pauseEvent);

                    break;
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    outputMutex = CreateMutex(NULL, FALSE, NULL);
    int arraySize;
    cout << "Введите размер массива: \n";
    cin >> arraySize;
    int* array = new int[arraySize]();

    int markerCount;
    cout << "Введите количество экземпляров потока marker: \n";
    cin >> markerCount;
    HANDLE* threads = new HANDLE[markerCount];
    INFO* infoData = new INFO[markerCount];
    HANDLE* pauseEvents = new HANDLE[markerCount];

    vector<int> activeMarkers;

    for (int i = 0; i < markerCount; i++) {
        infoData[i].threadId = i + 1;
        infoData[i].array = array;
        infoData[i].arraySize = arraySize;
        infoData[i].startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        infoData[i].pauseEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        infoData[i].stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        infoData[i].continueEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        pauseEvents[i] = infoData[i].pauseEvent;

        threads[i] = CreateThread(NULL, 0, MarkerThread, &infoData[i], 0, NULL);
        activeMarkers.push_back(i + 1);
    }

    for (int i = 0; i < markerCount; i++) {
        SetEvent(infoData[i].startEvent);
    }

    while (!activeMarkers.empty()) {
        HANDLE* currentPauseEvents = new HANDLE[activeMarkers.size()];
        for (int i = 0; i < activeMarkers.size(); i++) {
            currentPauseEvents[i] = pauseEvents[activeMarkers[i] - 1];
        }
        WaitForMultipleObjects(activeMarkers.size(), currentPauseEvents, TRUE, INFINITE);
        delete[] currentPauseEvents;


        WaitForSingleObject(outputMutex, INFINITE);
        cout << "\nМассив: \n";
        for (int i = 0; i < arraySize; i++)
            cout << array[i] << " ";
        cout << "\n";
        ReleaseMutex(outputMutex);

        int threadIdToStop;
        WaitForSingleObject(outputMutex, INFINITE);
        cout << "Введите номер потока marker, чтобы остановить его: ";
        ReleaseMutex(outputMutex);
        cin >> threadIdToStop;
        cout << "\n";

        auto it = find(activeMarkers.begin(), activeMarkers.end(), threadIdToStop);

        if (it != activeMarkers.end()) {
            SetEvent(infoData[threadIdToStop - 1].stopEvent);
            WaitForSingleObject(threads[threadIdToStop - 1], INFINITE);

            activeMarkers.erase(it);

            WaitForSingleObject(outputMutex, INFINITE);
            cout << "Массив после остановки потока " << threadIdToStop << ": ";
            for (int i = 0; i < arraySize; i++)
                cout << array[i] << " ";
            cout << "\n\n";
            ReleaseMutex(outputMutex);

            ResetEvent(infoData[threadIdToStop - 1].pauseEvent);
            for (int id : activeMarkers) {
                SetEvent(infoData[id - 1].continueEvent);
                ResetEvent(infoData[id - 1].pauseEvent);
            }
        }
        else {
            WaitForSingleObject(outputMutex, INFINITE);
            cout << "Поток с номером " << threadIdToStop << " не активен.\n\nДоступные потоки: ";
            for (int id : activeMarkers) {
                cout << id << " ";
            }
            cout << "\n";
            ReleaseMutex(outputMutex);
        }
    }

    for (int i = 0; i < markerCount; i++) {
        CloseHandle(threads[i]);
        CloseHandle(infoData[i].startEvent);
        CloseHandle(infoData[i].stopEvent);
        CloseHandle(infoData[i].continueEvent);
    }
    CloseHandle(outputMutex);

    delete[] array;
    delete[] threads;
    delete[] infoData;
    delete[] pauseEvents;

    return 0;
}
