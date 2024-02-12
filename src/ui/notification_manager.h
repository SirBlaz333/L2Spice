#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QString>

class NotificationManager
{
public:
    static void showInfo(QString message, QString title = QString("Info"));
    static void showError(QString message, QString title = QString("Error"));
    static void showWarning(QString message, QString title = QString("Warning"));
    static bool showQuestion(QString question, QString title = QString());
};

#endif // NOTIFICATIONMANAGER_H
