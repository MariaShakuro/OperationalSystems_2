#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "Sender.h"

using namespace std;
CRITICAL_SECTION cs; // Объявление критической секции
void writeToFile(const string& filename,const string& message) {
	EnterCriticalSection(&cs); // Вход в критическую секцию
	std::ofstream outFile(filename, std::ios::binary | std::ios::app);
	if (!outFile) {
		cerr << "Не удалось открыть файл для записи.\n";
		LeaveCriticalSection(&cs); // Выход из критической секции
		return;
	}
	int messageLength = message.size();
	outFile.write(reinterpret_cast<const char*>(&message), sizeof(message));
	outFile.write(message.c_str(), messageLength);
	outFile.close();
	LeaveCriticalSection(&cs); // Выход из критической секции
}

int main(int argc,char* argv[]) {
	setlocale(LC_ALL,"RUS");
	/*if (argc != 3) {
		cerr << "Ошибка: имя файла и имя события должны быть переданы в качестве аргументов командной строки.\n"; 
		return 1; 
	}*/
	string filename = argv[1];
	
     //1
	string nameOfFile;
	cout << "Введите имя файла:\n";
	cout << endl;
	cin >> nameOfFile;
	cout << endl;

	InitializeCriticalSection(&cs); // Инициализация критической секции
	HANDLE readyEvent = CreateEvent(NULL, TRUE, FALSE, "ReadyEvent");
	if (readyEvent == NULL) {
		cerr << "Событие не создано...\n";
		DeleteCriticalSection(&cs); // Удаление критической секции
		return 1;
	}
	//2
	SetEvent(readyEvent);
	//3
	bool isRunning = true;
	while (isRunning) {
		int commandForSender;
		cout << "Выберите команду:\n1 - Отправить процессу Receiver сообщение\n2 - Прекратить свою работу\n ";
		cin >> commandForSender;
		cin.ignore();
		if (commandForSender == 1) {
			string message;
			cout << "Введите сообщение:\n";
			cin.ignore();
			getline(cin,message);
			 if(message.length() <20) writeToFile(filename,message);
		    cout << "Сообщение записано\n";
			cout << "Отправлено процессу сообщение.." << endl;
		}
		else if (commandForSender == 2) {
			cout << "Процесс завершен" << endl;
			bool isRunning = false;
			break;
		}else cout << "Некорректный ввод.Попробуйте снова..." << endl;
	}
	
	CloseHandle(readyEvent);
	DeleteCriticalSection(&cs); // Удаление критической секции
	return 0;
}