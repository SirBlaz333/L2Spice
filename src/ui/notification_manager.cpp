#include "notification_manager.h"

#include <QMessageBox>

void showMessage(QString message, QMessageBox::Icon icon, QString title)
{
    QMessageBox messageBox;
    messageBox.setIcon(icon);
    messageBox.setWindowTitle(title);
    messageBox.setText(message);
    messageBox.setMinimumWidth(150);
    messageBox.addButton(QMessageBox::Ok);
    messageBox.exec();
}

void NotificationManager::showInfo(QString message, QString title)
{
    showMessage(message, QMessageBox::Information, title);
}

void NotificationManager::showError(QString message, QString title)
{
    showMessage(message, QMessageBox::Critical, title);
}

void NotificationManager::showWarning(QString message, QString title) {
    showMessage(message, QMessageBox::Warning, title);
}

bool NotificationManager::showQuestion(QString question, QString title)
{
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr,
                                                              title,
                                                              question,
                                                              QMessageBox::Yes | QMessageBox::No);
    return reply == QMessageBox::Yes;
}
