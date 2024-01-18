#ifndef CONSOLEAPPLICATION_H
#define CONSOLEAPPLICATION_H

#include <src/app/appcontroller.h>


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

#endif // CONSOLEAPPLICATION_H
