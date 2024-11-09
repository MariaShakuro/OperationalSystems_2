#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

int main() {
	setlocale(LC_ALL, "RUS");
	std::string binname;	//name of binary file
	int record;	//count of records
	std::string tname;	//name of text file
	double price;	//price for hour work

	std::cout << "Enter binary file name: ";
	std::cin >> binname;
	std::cout << "Enter number of records: ";
	std::cin >> record;
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	//launch Creator
	std::string Wproc1 = "Creator.exe";
	std::string Wpram1 = Wproc1 + " " + binname + " " + std::to_string(record);
	char smth[] = "D:\\Labs 2 grade\\OC\\Laba_1\\Laba1\\out\\build\\x64-debug\\Creator\\Creator.exe";
	if (CreateProcess(smth, &Wpram1[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else {
		std::cerr << "Error creation " << "Creator.exe" << "\n";
	}
	std::cout << "Enter report file name: ";
	std::cin >> tname;
	std::cout << "Enter price: ";
	std::cin >> price;
	std::cout << " " << "\n";

	//launch Reporter
	std::string Wproc2 = "Reporter.exe";
	std::string Wpram2 = Wproc2 + " " + binname + " " + tname + " " + std::to_string(price);
	char smth2[] = "D:\\Labs 2 grade\\OC\\Laba_1\\Laba1\\out\\build\\x64-debug\\Reporter\\Reporter.exe";
	if (CreateProcess(smth2, &Wpram2[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else {
		std::cerr << "Error creation " << "Reporter.exe" << "\n";
	}
	return 0;
}



