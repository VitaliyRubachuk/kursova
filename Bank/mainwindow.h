#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QPalette>
#include <QMessageBox>
#include <QCryptographicHash>
#include "databasemanager.h"
#include "userwindowmanager.h"

class UserWindowManager;

class Bank : public QMainWindow
{
    Q_OBJECT

public:
    Bank(QWidget *parent = nullptr);
    ~Bank();
    DatabaseManager *db;

private slots:
    void togglePasswordVisibility();
    void createUserTable();
    void createCreditTable();
    void createCardsTable();
    void clearTable();
    void loginClicked();
    void registerClicked();


private:
    UserWindowManager *userWindowManager;
    QPushButton *showPasswordButton;
    QDialog* userWindow;
    QString currentUsername;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;
    int pinValue;
    void showUserWindow(const QString& username);
    bool createConnection();
    void applyStyles();

};

#endif // MAINWINDOW_H


