#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include <src/app/app_controller.h>
#include <src/app/app_header.h>
#include <src/file/file_manager.h>

class ConsoleApplication
{
    AppController appController;
    AppHeader appHeader;
    FileManager fileManager;
    int argc;
    char **argv;
    bool showHelp;
    bool convert;

public:
    ConsoleApplication(int argc, char **argv);
    ~ConsoleApplication();
    int exec();
};

#endif // CONSOLE_APP_H
