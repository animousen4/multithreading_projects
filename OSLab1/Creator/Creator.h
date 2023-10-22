// Creator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <Windows.h>
#include "../Entities/Entities.h"


// creator
int main(int argc, char* argv[])
{   

    char* fileName = argv[1];
    char* amountChar = argv[2];

    int amount = atoi(amountChar);

    std::ofstream outputFile(fileName, std::ios::binary);
    Employee empl;
    std::cout << "\tID NAME HOURS\n";
    for (int i = 0; i < amount; i++) {

        std::cout << "#" << i + 1 << " -> ";
        std::cin >> empl;

        outputFile.write((char*)&empl, sizeof(Employee));
    }
    outputFile.close();
}
