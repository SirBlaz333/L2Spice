#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QString>

/**
 * NotificationManager is used to display the messages to the user.
 */
class NotificationManager
{
public:
    /**
     * Display the information message box to the user.
     * @param message - the message to display.
     * @param title - the title of the message box. It is "Info" by default.
     */
    static void showInfo(QString message, QString title = QString("Info"));

    /**
     * Display the error message box to the user.
     * @param message - the message to display.
     * @param title - the title of the message box. It is "Error" by default.
     */
    static void showError(QString message, QString title = QString("Error"));

    /**
     * Display the warning message box to the user.
     * @param message - the message to display.
     * @param title - the title of the message box. It is "Warning" by default.
     */
    static void showWarning(QString message, QString title = QString("Warning"));

    /**
     * Display the question message box. The user can answer "Yer" or "No" to it.
     *
     * @param question - the question message to display.
     * @param title - the title of the message box. It is empty by default.
     * @return true is the answer is yes, false otherwise.
     */
    static bool showQuestion(QString question, QString title = QString());
};

#endif // NOTIFICATIONMANAGER_H
