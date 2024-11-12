// Laba_4.cpp: определяет точку входа для приложения.
//"Синхронизация процессов"
#include "Laba_4.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

void readBinaryFile(const string& filename) {
		ifstream inFile(filename, ios::binary);
		if (!inFile) { 
			cerr << "Не удалось открыть файл для чтения.\n";
			return; 
		}
		int message;
		bool isEmpty = true;
		int messageLength;
		while (inFile.read(reinterpret_cast<char*>(&message), sizeof(message))) { 
			vector<char> buffer(messageLength);
			inFile.read(buffer.data(), messageLength);
			string message(buffer.begin(), buffer.end());
			cout << "Сообщение: " << message << endl;
		}
		inFile.close();
		if (isEmpty) {
			cout << "Файл пуст. Ожидание поступления нового сообщения..." << endl; while (true) {
				Sleep(10000); // Пауза 1 секунда
				ifstream checkFile(filename, ios::binary);
				if (checkFile.peek() != ifstream::traits_type::eof()) {
					checkFile.close(); 
					break;
				}
				checkFile.close(); 
			} 
			readBinaryFile(filename); // Рекурсивный вызов функции для чтения новых сообщений
		}
}


int main(){

	setlocale(LC_ALL,"RUS");

	//1
	string nameOfBinaryFile;
	int countOfNotes, countOfProcesses;
	cout << "Введите имя бинарного файла:";
	cin >> nameOfBinaryFile;
	cout << endl;
	cout << "Введите кол-во записей в бинарном файле:";
	cin >> countOfNotes;
	cout << endl;
	//2
	cout << "Введите кол-во процессов Sender:";
	cin >> countOfProcesses;
	cout << endl;
	//3
	vector<PROCESS_INFORMATION>processInfos(countOfProcesses);
	vector<STARTUPINFO>startupInfos(countOfProcesses, {sizeof(STARTUPINFO)});
	for (int i = 0; i < countOfProcesses;++i) {
		string commandLine = "../Sender/Sender.exe " + nameOfBinaryFile;
		if (!CreateProcess(NULL,
			const_cast<char*>(commandLine.c_str()),
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&startupInfos[i],
			&processInfos[i])) {
			cout << "Не удалось создать процесс Sender " << (i + 1) << endl;
		}
	}
	//4
	
	for (int i = 0; i < countOfProcesses;++i) {
		WaitForSingleObject(processInfos[i].hProcess, INFINITE);
	}
	//5
	while (true) {
		int command;
		cout << "Выберите команду:\n1 - Читать сообщение из бинарного файла\n2 - Завершить свою работу\n";
		cin >> command;
		if (command == 1) {
			readBinaryFile(nameOfBinaryFile);
			cout << "Файл прочитан" << endl;
		}
		else if (command == 2) { 
			cout << "Процесс завершен" << endl;
			break;
		}
		else cout << "Некорректный ввод.Попробуйте снова..." << endl;
	}

	// Закрытие хендлов процессов 
	for (int i = 0; i < countOfProcesses; ++i) { 
		CloseHandle(processInfos[i].hThread);
		CloseHandle(processInfos[i].hProcess);
	}
	
	return 0;
}
