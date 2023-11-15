#include <Windows.h>


class ProcessManager {

public:
    ProcessManager() :
        si(new STARTUPINFOW()),
        piApp(new PROCESS_INFORMATION())
    {}

    ~ProcessManager() {
        delete si;
        delete piApp;
    }

    bool createApp(const wchar_t* appName, wchar_t* arguments) {

        clearMem();

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
private:
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

   
};
