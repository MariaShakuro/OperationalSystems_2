#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "Sender.h"

using namespace std;
CRITICAL_SECTION cs; // ���������� ����������� ������
void writeToFile(const string& filename,const string& message) {
	EnterCriticalSection(&cs); // ���� � ����������� ������
	std::ofstream outFile(filename, std::ios::binary | std::ios::app);
	if (!outFile) {
		cerr << "�� ������� ������� ���� ��� ������.\n";
		LeaveCriticalSection(&cs); // ����� �� ����������� ������
		return;
	}
	int messageLength = message.size();
	outFile.write(reinterpret_cast<const char*>(&message), sizeof(message));
	outFile.write(message.c_str(), messageLength);
	outFile.close();
	LeaveCriticalSection(&cs); // ����� �� ����������� ������
}

int main(int argc,char* argv[]) {
	setlocale(LC_ALL,"RUS");
	/*if (argc != 3) {
		cerr << "������: ��� ����� � ��� ������� ������ ���� �������� � �������� ���������� ��������� ������.\n"; 
		return 1; 
	}*/
	string filename = argv[1];
	
     //1
	string nameOfFile;
	cout << "������� ��� �����:\n";
	cout << endl;
	cin >> nameOfFile;
	cout << endl;

	InitializeCriticalSection(&cs); // ������������� ����������� ������
	HANDLE readyEvent = CreateEvent(NULL, TRUE, FALSE, "ReadyEvent");
	if (readyEvent == NULL) {
		cerr << "������� �� �������...\n";
		DeleteCriticalSection(&cs); // �������� ����������� ������
		return 1;
	}
	//2
	SetEvent(readyEvent);
	//3
	bool isRunning = true;
	while (isRunning) {
		int commandForSender;
		cout << "�������� �������:\n1 - ��������� �������� Receiver ���������\n2 - ���������� ���� ������\n ";
		cin >> commandForSender;
		cin.ignore();
		if (commandForSender == 1) {
			string message;
			cout << "������� ���������:\n";
			cin.ignore();
			getline(cin,message);
			 if(message.length() <20) writeToFile(filename,message);
		    cout << "��������� ��������\n";
			cout << "���������� �������� ���������.." << endl;
		}
		else if (commandForSender == 2) {
			cout << "������� ��������" << endl;
			bool isRunning = false;
			break;
		}else cout << "������������ ����.���������� �����..." << endl;
	}
	
	CloseHandle(readyEvent);
	DeleteCriticalSection(&cs); // �������� ����������� ������
	return 0;
}