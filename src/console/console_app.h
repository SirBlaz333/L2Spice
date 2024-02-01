#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include <src/app/app_controller.h>


class ConsoleApplication
{
    AppController appController;
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
