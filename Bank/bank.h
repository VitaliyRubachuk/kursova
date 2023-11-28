#ifndef BANK_H
#define BANK_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "adminwindow.h"

class Bank : public QMainWindow
{
    Q_OBJECT

public:
    Bank(QWidget *parent = nullptr);
    ~Bank();


private slots:
    void togglePasswordVisibility();
    void showCredits();
    void loginClicked();
    void registerClicked();
    void clearTable();
    void showUserWindow(const QString& username);
    void addCredit(const QString& username, const QString& amount);
    void repayCredit(const QString& creditNumber);
    void addCardToDatabase(const QString& name, const QString& pin, const QString& cardNumber, const QString& username);
    void showUserCards();
    QString getCreditAmountForUser(const QString& username);
    int getNextCreditNumber();
    bool hasCredits(const QString& username);

private:

    QPushButton *showPasswordButton;
    QDialog* userWindow;
    QString currentUsername;
    AdminWindow *adminWindow;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QSqlDatabase db;

    bool createConnection();
    void createUserTable();
    void createCreditTable();
    void createCardsTable();
};

#endif // BANK_H
