#include <Windows.h>
#include <string>

class ProcessManager {

public:
    ProcessManager() :
        si(new STARTUPINFO()),
        piApp(new PROCESS_INFORMATION())
    {}

    ~ProcessManager() {
        delete si;
        delete piApp;
    }

    bool createApp(std::string appName, std::string arguments) {

        clearMem();
        char* startUpArgs = new char[100];
        std::string command = appName + " " + arguments;

        for (int i = 0; i < command.length(); i++) {
            startUpArgs[i] = command[i];
        }

        startUpArgs[command.size()] = 0;

        return CreateProcessA(
            NULL,
            startUpArgs,
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

    bool createApp(std::string appName) {
        return createApp(appName, "");
    }
private:
    STARTUPINFO* si;
    PROCESS_INFORMATION* piApp;

    void clearMem() {
        ZeroMemory(si, sizeof(STARTUPINFO));
        si->cb = sizeof(STARTUPINFO);
    }
    void closeApp() {
        CloseHandle(piApp->hProcess);
        CloseHandle(piApp->hThread);
    }


    void waitApp() {
        WaitForSingleObject(piApp->hProcess, INFINITE);
    }

   
};
