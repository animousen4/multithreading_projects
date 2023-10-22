// OSLab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "../Entities/Entities.h"

void printFileContent(wchar_t* fileName) {
    std::ifstream file(fileName);

    char c[50];
    while (file.getline(c, 50)) {
        std::wcout << c << std::endl;
    }

    file.close();
}

void printBinFileContent(wchar_t* fileName) {
    std::ifstream file(fileName, std::ios::binary);

    char c[50];
    Employee empl;
    while (!file.read((char*)&empl, sizeof(Employee)).eof()) {
        std::wcout << empl << std::endl;
    }

    file.close();
}
int main()
{

    wchar_t creatorArg[40] = L"";
    wchar_t fileNameEmployeeArg[20];
    wchar_t amountArg[10];

    wchar_t reporterArg[40] = L"";
    wchar_t fileNameReportArg[20];
    wchar_t hourSalaryArg[10];

    std::wcout << "FILENAME_EMPLOYEE(BINARY) AMOUNT_EMPLOYEE" << std::endl;
    std::wcin >> fileNameEmployeeArg >> amountArg;

    wcscat_s(creatorArg, fileNameEmployeeArg);
    wcscat_s(creatorArg, L" ");
    wcscat_s(creatorArg, amountArg);


    ProcessManager* p = new ProcessManager;

    // Start & finish Creator
    p->doLifeCycle(L"Creator.exe", creatorArg);

    std::wcout << std::endl;
    printBinFileContent(fileNameEmployeeArg);
    std::wcout << std::endl;

    std::wcout << "FILENAME_REPORT(TEXT) HOUR_SALARY" << std::endl;
    std::wcin >> fileNameReportArg >> hourSalaryArg;

    wcscat_s(reporterArg, fileNameEmployeeArg);
    wcscat_s(reporterArg, L" ");
    wcscat_s(reporterArg, fileNameReportArg);
    wcscat_s(reporterArg, L" ");
    wcscat_s(reporterArg, hourSalaryArg);

    //Start Reporter
    p->doLifeCycle(L"Reporter.exe", reporterArg);

    std::wcout << std::endl;
    printFileContent(fileNameReportArg);
    std::wcout << std::endl;

    system("pause");
    return 0;
}