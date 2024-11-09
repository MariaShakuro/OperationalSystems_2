#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "Structure.h"

//#include "Structure.h"
class Creator {
private:
    std::string binname;   //name of binary file
    int record;    //count of records
public:
    //Default constructor
    Creator() :binname(""), record(0) {}
    //Parametrized constructor
    Creator(const std::string& binname, int record):binname(binname),record(record) {}
   
    //Gettery
    std::string getBinname() const { return binname; }
    int getRecord() const { return record; }

    void CreateFile() {
        std::ofstream outFile(binname, std::ios::binary);
        if (!outFile) {
            std::cerr << "Error opening file for writing\n";
            return;

        }
       
        std::vector<employee> employees;
        for (int i = 0; i < record; ++i) {
            employee e;
            std::cout << "Employee number :";
            std::cin >> e.num;
            std::cout << "Name of employee :";
            std::cin >> e.name;
            std::cout << "Worked hours :";
            std::cin >> e.hours;
            //Binfile
            outFile.write(reinterpret_cast<char*>(&e), sizeof(e));
            // Store the employee in the vector
            employees.push_back(e);
        }
        outFile.close();
        std::cout << " " << "\n";
        std::cout << "______________INFORMATION_____________________" << "\n";
        for (const auto& e : employees) {
            std::cout << "Employee number: " << e.num << "\n";
            std::cout << "Name of employee: " << e.name << "\n";
            std::cout << "Worked hours: " << e.hours << "\n";
            std::cout << " " << "\n";
        }
        std::cout << " " << "\n";
    }

   

};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <number of records>\n";
        return 1;
    }
    std::string binname = argv[1];
    int record= std::stoi(argv[2]);

    Creator creator(binname, record);
    creator.CreateFile();
    return 0;
}