#ifndef USERWINDOWMANAGER_H
#define USERWINDOWMANAGER_H

#include <QObject>
#include <QDialog>
#include <QString>
#include "mainwindow.h"
#include "usercardmanager.h"
class Bank;

class UserCardManager;

class UserWindowManager : public QObject
{
    Q_OBJECT
    DatabaseManager *db;
public:
    explicit UserWindowManager(QObject *parent = nullptr);
    void showUserWindow(const QString& username);
    void changePassword(const QString& username);
    int getNextCreditNumber();
    QString getCreditAmountForUser(const QString& username);
    bool hasCredits(const QString& username);
    void showCredits();
    void showLoanDialog(const QString& username);
    bool checkLoanEligibility(int age, double salary);
private:
    DatabaseManager databaseManagerInstance;
    UserCardManager *userCardManagerInstance;
    QString currentUsername;
    QDialog* userWindow;

public slots:
    void showUserCards();


signals:

};

#endif // USERWINDOWMANAGER_H
