#include "adminwindow.h"
#include <QTextEdit>
#include <QPushButton>
#include <QSqlQuery>

AdminWindow::AdminWindow(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Адміністративна панель");
    setFixedSize(400, 400);
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *clearTableButton = new QPushButton("Clear Table", this);
    connect(clearTableButton, &QPushButton::clicked, this, &AdminWindow::clearTable);
    layout->addWidget(clearTableButton);

    QTextEdit *accountList = new QTextEdit(this);
    accountList->setReadOnly(true);
    layout->addWidget(accountList);

    QPushButton *showAccountsButton = new QPushButton("Аккаунти", this);
    connect(showAccountsButton, &QPushButton::clicked, [=]()
            {
        QSqlQuery query("SELECT * FROM Users");
        QString accounts;
        while (query.next())
        {
            accounts += "Аккаунт: " + query.value(0).toString() + "\nПароль: " + query.value(1).toString() + "\n\n";
        }
        accountList->setText(accounts);
    });
    layout->addWidget(showAccountsButton);

    QPushButton *showCreditsButton = new QPushButton("Кредити", this);
    connect(showCreditsButton, &QPushButton::clicked, this, &AdminWindow::showCredits);
    layout->addWidget(showCreditsButton);

    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void AdminWindow::clearTable()
{
    emit tableCleared();
}

void AdminWindow::showCredits()
{
    QTextEdit *accountList = findChild<QTextEdit *>();
    if (!accountList)
    {
        return;
    }

    accountList->clear();

    QSqlQuery query("SELECT * FROM Users");
    QString accounts;
    bool creditsExist = false;

    while (query.next()) {
        QString username = query.value(0).toString();
        QSqlQuery creditQuery;
        creditQuery.prepare("SELECT CreditNumber, Amount FROM CreditHistory WHERE Username = :username");
        creditQuery.bindValue(":username", username);

        if (creditQuery.exec()) {
            if (creditQuery.next()) {
                creditsExist = true;
                accounts += "Ім'я: " + username + "\nКредити:\n";
                do
                {
                    accounts += "Номер кредиту: " + creditQuery.value(0).toString() + " | Сумма: " + creditQuery.value(1).toString() + "\n";
                }
                while (creditQuery.next());
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


