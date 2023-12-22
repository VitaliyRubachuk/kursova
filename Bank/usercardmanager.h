#ifndef USERCARDMANAGER_H
#define USERCARDMANAGER_H

#include <QObject>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QSqlQuery>
#include <QMessageBox>
#include <QInputDialog>
#include <QPalette>
#include <random>
#include <QCryptographicHash>
#include "userwindowmanager.h"
#include "databasemanager.h"


class UserWindowManager;

class UserCardManager : public QObject
{
    Q_OBJECT

public:
    explicit UserCardManager(QObject *parent = nullptr);
    void deleteCard(const QString& username);
    bool checkPin(const QString& enteredPin, const QString& storedPin);
    void updateCardNumbers();
    void showUserCards(const QString& username);

public slots:
    void cardButtonClicked();
    void getCardButtonClicked();
    void deleteCardButtonClicked();

private:
    DatabaseManager databaseManagerInstance;
    UserWindowManager* userWindowManager;
    QDialog* cardDialog;
    QPushButton *cardButton;
    QPushButton *getCardButton;
    QPushButton *deleteCardButton;
    QString currentUsername;
    int pinValue;

};

#endif // USERCARDMANAGER_H
