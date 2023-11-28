/********************************************************************************
** Form generated from reading UI file 'bank.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BANK_H
#define UI_BANK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bank
{
public:
    QWidget *centralwidget;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *bank)
    {
        if (bank->objectName().isEmpty())
            bank->setObjectName("bank");
        bank->resize(800, 600);
        centralwidget = new QWidget(bank);
        centralwidget->setObjectName("centralwidget");
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(90, 200, 75, 24));
        registerButton = new QPushButton(centralwidget);
        registerButton->setObjectName("registerButton");
        registerButton->setGeometry(QRect(250, 200, 75, 24));
        usernameEdit = new QLineEdit(centralwidget);
        usernameEdit->setObjectName("usernameEdit");
        usernameEdit->setGeometry(QRect(150, 120, 113, 22));
        passwordEdit = new QLineEdit(centralwidget);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(150, 160, 113, 22));
        bank->setCentralWidget(centralwidget);
        menubar = new QMenuBar(bank);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        bank->setMenuBar(menubar);
        statusbar = new QStatusBar(bank);
        statusbar->setObjectName("statusbar");
        bank->setStatusBar(statusbar);

        retranslateUi(bank);

        QMetaObject::connectSlotsByName(bank);
    } // setupUi

    void retranslateUi(QMainWindow *bank)
    {
        bank->setWindowTitle(QCoreApplication::translate("bank", "bank", nullptr));
        loginButton->setText(QCoreApplication::translate("bank", "loginButton", nullptr));
        registerButton->setText(QCoreApplication::translate("bank", "registerButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bank: public Ui_bank {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANK_H
