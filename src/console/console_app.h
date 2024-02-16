#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include <src/app/app_controller.h>
#include <src/app/app_header.h>
#include <src/file/file_manager.h>

class ConsoleApplication
{
    AppController appController;
    AppHeader appHeader;
    int argc;
    char **argv;

public:
    ConsoleApplication(int argc, char **argv);
    int exec();
private:
    QString convertHtmlToPlain(QString);
};

#endif // CONSOLE_APP_H
