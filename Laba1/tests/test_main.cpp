/*#include <gtest/gtest.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>

// Function prototypes (if any functions are to be tested separately)

// Test case for the main function
TEST(test_main, ProcessCreation) {
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    std::string binname = "test.bin";
    int record = 10;
    std::string tname = "report.txt";
    double price = 50.0;

    std::string Wproc1 = "Creator.exe";
    std::string Wpram1 = Wproc1 + " " + binname + " " + std::to_string(record);
    char smth[] = "D:\\Labs 2 grade\\OC\\Laba_1\\Laba1\\out\\build\\x64-debug\\Creator\\Creator.exe";
    ASSERT_TRUE(CreateProcess(smth, &Wpram1[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi));
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::string Wproc2 = "Reporter.exe";
    std::string Wpram2 = Wproc2 + " " + binname + " " + tname + " " + std::to_string(price);
    char smth2[] = "D:\\Labs 2 grade\\OC\\Laba_1\\Laba1\\out\\build\\x64-debug\\Reporter\\Reporter.exe";
    ASSERT_TRUE(CreateProcess(smth2, &Wpram2[0], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi));
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

// Main function for running all tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/




