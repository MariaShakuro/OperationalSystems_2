/*#include <cassert>
#include <iostream>
#include <fstream>
#include "../Creator/creator.cpp"

void testDefaultConstructor() {
    Creator creator;
    assert(creator.getBinname() == "");
    assert(creator.getRecord() == 0);
    std::cout << "testDefaultConstructor passed\n";
}

void testParametrizedConstructor() {
    Creator creator("test.bin", 10);
    assert(creator.getBinname() == "test.bin");
    assert(creator.getRecord() == 10);
    std::cout << "testParametrizedConstructor passed\n";
}

void testCopyConstructor() {
    Creator original("test.bin", 10);
    Creator copy(original);
    assert(copy.getBinname() == "test.bin");
    assert(copy.getRecord() == 10);
    std::cout << "testCopyConstructor passed\n";
}

void testCreateFile() {
    Creator creator("test.bin", 2);
    creator.CreateFile();

    std::ifstream binFile("test.bin", std::ios::binary);
    assert(binFile.is_open());
    binFile.close();
    std::cout << "testCreateFile passed\n";
}

int main() {
    testDefaultConstructor();
    testParametrizedConstructor();
    testCopyConstructor();
    testCreateFile();
    return 0;
}*/




