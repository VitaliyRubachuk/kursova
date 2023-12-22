#include "adminwindow.h"
#include <QTextEdit>
#include <QPushButton>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

AdminWindow::AdminWindow(QWidget *parent) : QDialog(parent){showAdminWindow();}

void AdminWindow::showAdminWindow()
{
    setWindowTitle("Адміністративна панель");
    setFixedSize(600, 600);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *clearTableButton = new QPushButton("Очистити базу даних", this);
    connect(clearTableButton, &QPushButton::clicked, this, &AdminWindow::clearTable);
    applyButtonStyle(clearTableButton);
    layout->addWidget(clearTableButton);

    accountList = new QTextEdit(this);
    accountList->setReadOnly(true);
    applyTextEditStyle(accountList);
    layout->addWidget(accountList);

    QPushButton *showAccountsButton = new QPushButton("Показати аккаунти", this);
    connect(showAccountsButton, &QPushButton::clicked, this, &AdminWindow::showAccounts);
    applyButtonStyle(showAccountsButton);
    layout->addWidget(showAccountsButton);

    QPushButton *showAdditionalInfoButton = new QPushButton("Інформація про користувачів", this);
    connect(showAdditionalInfoButton, &QPushButton::clicked, this, &AdminWindow::showlUserInfo);
    applyButtonStyle(showAdditionalInfoButton);
    layout->addWidget(showAdditionalInfoButton);

    QPushButton *showUserInfoButton = new QPushButton("Додаткова інформація про користувачів", this);
    connect(showUserInfoButton, &QPushButton::clicked, this, &AdminWindow::showAdditionalUserInfo);
    applyButtonStyle(showUserInfoButton);
    layout->addWidget(showUserInfoButton);

    QPushButton *showCreditsButton = new QPushButton("Показати кредити", this);
    connect(showCreditsButton, &QPushButton::clicked, this, &AdminWindow::showCredits);
    applyButtonStyle(showCreditsButton);
    layout->addWidget(showCreditsButton);


    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    connect(this, &AdminWindow::tableCleared, this, &AdminWindow::refreshAccounts);
}

void AdminWindow::clearTable() {
    emit tableCleared();
    refreshAccounts(); // Оновлення після очищення таблиці
}


void AdminWindow::showAccounts()
{
    accountList->clear();

    QSqlQuery query("SELECT id, username, CreationDate FROM Users ORDER BY id ASC");
    QString accounts;
    while (query.next()) {
        accounts += "Номер аккаунту: " + query.value(0).toString() + "\nЛогін: " + query.value(1).toString() + "\nДата створення: " + query.value(2).toString() + "\n\n";
    }
    accountList->setText(accounts);
}


void AdminWindow::refreshAccounts()
{
    showAccounts();
}

void AdminWindow::showCredits()
{
    accountList->clear();

    QSqlQuery query("SELECT * FROM Users WHERE role <> 'admin'");
    QString accounts;
    bool creditsExist = false;

    while (query.next()) {
        QString username = query.value("username").toString();
        QSqlQuery creditQuery;
        creditQuery.prepare("SELECT Cards.Name AS CardName, CreditHistory.id, CreditHistory.Amount FROM Cards JOIN CreditHistory ON Cards.Username = CreditHistory.Username WHERE Cards.Username = :username ORDER BY CreditHistory.id ASC");
        creditQuery.bindValue(":username", username);

        if (creditQuery.exec())
        {
            while (creditQuery.next())
            {
                creditsExist = true;
                accounts += "Прізвище та Ім'я: " + creditQuery.value("CardName").toString() + "\nКредити:\n";
                do {
                    accounts += "Номер кредиту: " + creditQuery.value("id").toString() + " | Сумма: " + creditQuery.value("Amount").toString() + "\n";
                } while (creditQuery.next());
                accounts += "\n";
            }
        }
    }

    if (!creditsExist) {
        accountList->setText("Немає кредитів");
    } else {
        accountList->setText(accounts);
    }
}




void AdminWindow::applyButtonStyle(QPushButton* button)
{
    button->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");}

void AdminWindow::applyTextEditStyle(QTextEdit* textEdit)
{
    textEdit->setStyleSheet("QTextEdit {""background-color: #FFFFFF;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 12px;""padding: 6px;""}");
}

void AdminWindow::showlUserInfo()
{
    QDialog *aInfoDialog = new QDialog(this);
    aInfoDialog->setWindowTitle("Інформація про користувача");
    aInfoDialog->setFixedSize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(aInfoDialog);

    QLabel *label = new QLabel("Введіть номер акаунта:", aInfoDialog);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 14px;");
    layout->addWidget(label);

    QLineEdit *idInput = new QLineEdit(aInfoDialog);
    idInput->setStyleSheet("background-color: white;");
    layout->addWidget(idInput);

    QPushButton *submitButton = new QPushButton("Показати", aInfoDialog);
    layout->addWidget(submitButton);
    aInfoDialog->setStyleSheet("background-color: lightblue;");

    connect(submitButton, &QPushButton::clicked, [=]()
            {
        QString userId = idInput->text();
        if (userId.isEmpty())
        {
            QMessageBox::warning(aInfoDialog, "Помилка", "Будь ласка, введіть ID користувача!");
            return;
        }

        bool ok;
        int selectedUserId = userId.toInt(&ok);
        if (!ok)
        {
            QMessageBox::warning(aInfoDialog, "Помилка", "Введено невірний формат ID користувача!");
            return;
        }

        if (selectedUserId == 1)
        {
            QMessageBox::information(aInfoDialog, "Інформація", "Адміністратор банку");
        } else if (selectedUserId == 2)
        {
            QMessageBox::information(aInfoDialog, "Інформація", "Менеджер банку");
        } else {
            QSqlQuery userInfoQuery;
            userInfoQuery.prepare("SELECT Cards.Name, Cards.CardNumber, Cards.City, Cards.Address, Cards.TaxCode FROM Cards JOIN Users ON Cards.Username = Users.username WHERE Users.id = :id");
            userInfoQuery.bindValue(":id", selectedUserId);

            if (userInfoQuery.exec() && userInfoQuery.next())
            {
                QString name = userInfoQuery.value(0).toString();
                QString cardNumber = userInfoQuery.value(1).toString();
                QString city = userInfoQuery.value(2).toString();
                QString address = userInfoQuery.value(3).toString();
                QString taxCode = userInfoQuery.value(4).toString();

                QString userInfo = "<b>Прізвище та ім'я:</b> " + name + "<br>"
                                   "<b>Номер карти:</b> " + cardNumber + "<br>"
                                   "<b>Місто:</b> " + city + "<br>"
                                            "<b>Адреса:</b> " + address + "<br>"
                                   "<b>Податковий код:</b> " + taxCode;
                QMessageBox msgBox;
                msgBox.setStyleSheet("QLabel{min-width: 400px;}");
                msgBox.information(aInfoDialog, "Інформація", userInfo);
                msgBox.setMinimumWidth(500);
                aInfoDialog->close();
            } else
            {
                QMessageBox::warning(aInfoDialog, "Помилка", "Інформація про користувача не знайдена!");
            }
        }
        idInput->clear();
    });

    aInfoDialog->exec();

    connect(aInfoDialog, &QDialog::finished, [=]()
            {
        idInput->clear();
    });
}

void AdminWindow::showAdditionalUserInfo()
{
    QDialog *additionalInfoDialog = new QDialog(this);
    additionalInfoDialog->setWindowTitle("Додаткова інформація про користувача");
    additionalInfoDialog->setFixedSize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(additionalInfoDialog);

    QLabel *label = new QLabel("Введіть номер акаунта:", additionalInfoDialog);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 14px;");
    layout->addWidget(label);

    QLineEdit *idInput = new QLineEdit(additionalInfoDialog);
    idInput->setStyleSheet("background-color: white;");
    layout->addWidget(idInput);

    QPushButton *submitButton = new QPushButton("Показати", additionalInfoDialog);
    layout->addWidget(submitButton);
    additionalInfoDialog->setStyleSheet("background-color: lightblue;");
    connect(submitButton, &QPushButton::clicked, [=]()
            {
        QString userId = idInput->text();
        if (userId.isEmpty()) {
            QMessageBox::warning(additionalInfoDialog, "Помилка", "Будь ласка, введіть ID користувача!");
            return;
        }

        bool ok;
        int selectedUserId = userId.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(additionalInfoDialog, "Помилка", "Введено невірний формат ID користувача!");
            return;
        }

        if (selectedUserId == 1) {
            QMessageBox::information(additionalInfoDialog, "Інформація", "Адміністратор банку");
        } else if (selectedUserId == 2) {
            QMessageBox::information(additionalInfoDialog, "Інформація", "Менеджер банку");
        } else {
            QSqlQuery userInfoQuery;
            userInfoQuery.prepare("SELECT employmentPlace, salary, age, canTakeLoan FROM Users WHERE id = :id");
            userInfoQuery.bindValue(":id", selectedUserId);

            if (userInfoQuery.exec() && userInfoQuery.next())
            {
                QString workplace = userInfoQuery.value("employmentPlace").toString();
                double salary = userInfoQuery.value("salary").toDouble();
                int age = userInfoQuery.value("age").toInt();
                bool canTakeLoan = userInfoQuery.value("canTakeLoan").toBool();

                QString userInfo = "<b>Місце роботи:</b> " + workplace + "<br>"
                                   "<b>Зарплата:</b> " + QString::number(salary) +
                                   "<br><b>Вік:</b> " + QString::number(age) + "<br><br>";

                if (canTakeLoan) {
                    userInfo += "<b>Одобрено в кредитуванні!</b>";
                } else {
                    userInfo += "<b>Відмовлено в кредитуванні!</b>";
                }

                QMessageBox msgBox;
                msgBox.setStyleSheet("QLabel{min-width: 600px;}");
                msgBox.information(additionalInfoDialog, "Інформація", userInfo);
                msgBox.setMinimumWidth(675);
                msgBox.setMinimumHeight(450);
                additionalInfoDialog->close();
            } else {
                QMessageBox::warning(additionalInfoDialog, "Помилка", "Інформація про користувача не знайдена!");
            }
        }
        idInput->clear();
    });

    additionalInfoDialog->exec();

    connect(additionalInfoDialog, &QDialog::finished, [=]()
            {
        idInput->clear();
    });
}

