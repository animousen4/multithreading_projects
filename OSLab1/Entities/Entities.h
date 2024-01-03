#pragma once

#include <fstream>
#include <conio.h>
#include <Windows.h>

struct Employee {
    int id;
    char name[10];
    double hours;

    friend std::ostream& operator<<(std::ostream& s, const Employee& e) {
        s << e.id << "\t" << e.name << "\t" << e.hours;
        return s;
    }

    friend std::istream& operator>>(std::istream& s, Employee& e) {
        s >> e.id >> e.name >> e.hours;
        return s;
    }

    friend std::wostream& operator<<(std::wostream& s, const Employee& e) {
        s << e.id << "\t" << e.name << "\t" << e.hours;
        return s;
    }
};

class ProcessManager {

public:
    ProcessManager(bool _printDebug = false) : 
        si(new STARTUPINFOW()),
        piApp(new PROCESS_INFORMATION()),
        printDebug(_printDebug)
    {
        clearMem();
    }

    void doLifeCycle(const wchar_t* appName, wchar_t* arguments) {
        clearMem();
        bool isCreated = createApp(appName, arguments);
        waitApp();
        closeApp();
    }
private:
    ~ProcessManager() {
        delete si;
        delete piApp;
    }

    bool printDebug;
    STARTUPINFOW* si;
    PROCESS_INFORMATION* piApp;

    void clearMem() {
        ZeroMemory(si, sizeof(STARTUPINFOW));
        si->cb = sizeof(STARTUPINFOW);
    }
    void closeApp() {
        CloseHandle(piApp->hProcess);
        CloseHandle(piApp->hThread);
    }


    void waitApp() {
        WaitForSingleObject(piApp->hProcess, INFINITE);
    }

    bool createApp(const wchar_t* appName, wchar_t* arguments) {
        
        wchar_t consoleCommand[80] = L"";

        wcscat_s(consoleCommand, appName);
        wcscat_s(consoleCommand, L" ");
        wcscat_s(consoleCommand, arguments);

        return CreateProcessW(
            NULL,
            consoleCommand,
            NULL,
            NULL,
            TRUE,
            CREATE_NEW_CONSOLE,
            NULL,
            NULL,
            si,
            piApp
        );
    }
};
