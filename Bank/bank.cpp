#include "bank.h"
#include <QMessageBox>
#include "adminwindow.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCoreApplication>
#include <QFile>
#include <QtUiTools/QUiLoader>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLabel>
#include <QWidget>
#include <QtGlobal>
#include <random>
#include <QInputDialog>
#include <QSqlError>
#include <QDateTime>

Bank::Bank(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Банк.UA");
    setFixedSize(700, 800);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    showPasswordButton = new QPushButton("Показати пароль", this);
    showPasswordButton->setFixedHeight(35);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setFixedHeight(35);
    usernameEdit = new QLineEdit(this);
    usernameEdit->setFixedHeight(35);

    loginButton = new QPushButton("Логін", this);
    loginButton->setFixedHeight(50);
    registerButton = new QPushButton("Реєстрація", this);
    registerButton->setFixedHeight(50);

    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);

    QHBoxLayout *passwordLayout = new QHBoxLayout();
    passwordLayout->addWidget(passwordEdit);
    passwordLayout->addWidget(showPasswordButton);

    layout->addLayout(passwordLayout);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);

    //



    loginButton->setStyleSheet("QPushButton {"
                               "background-color: #A0CFE8;"
                               "border-style: outset;"
                               "border-width: 2px;"
                               "border-radius: 10px;"
                               "border-color: #80AEBD;"
                               "font: bold 14px;"
                               "min-width: 10em;"
                               "padding: 6px;"
                               "}"
                               "QPushButton:hover {"
                               "background-color: #C7E4F2;"
                               "}"
                               "QPushButton:pressed {"
                               "background-color: #85B7D9;"
                               "}");

    registerButton->setStyleSheet("QPushButton {"
                                  "background-color: #A0CFE8;"
                                  "border-style: outset;"
                                  "border-width: 2px;"
                                  "border-radius: 10px;"
                                  "border-color: #80AEBD;"
                                  "font: bold 14px;"
                                  "min-width: 10em;"
                                  "padding: 6px;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #C7E4F2;"
                                  "}"
                                  "QPushButton:pressed {"
                                  "background-color: #85B7D9;"
                                  "}");

    showPasswordButton->setStyleSheet("QPushButton {"
                                      "background-color: #A0CFE8;"
                                      "border-style: outset;"
                                      "border-width: 2px;"
                                      "border-radius: 10px;"
                                      "border-color: #80AEBD;"
                                      "font: bold 14px;"
                                      "min-width: 10em;"
                                      "padding: 6px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background-color: #C7E4F2;"
                                      "}"
                                      "QPushButton:pressed {"
                                      "background-color: #85B7D9;"
                                      "}");

    usernameEdit->setStyleSheet("QLineEdit:focus {"
                            "border: 2px solid #6495ED;"
                            "}"
                            "QLineEdit:hover {"
                            "background-color: #F0F8FF;"
                            "}"
                            "QLineEdit:enabled {"
                            "color: black;"
                            "font-weight: bold;"
                            "}");

    passwordEdit->setStyleSheet("QLineEdit:focus {"
                                "border: 2px solid #6495ED;"
                                "}"
                                "QLineEdit:hover {"
                                "background-color: #F0F8FF;"
                                "}"
                                "QLineEdit:enabled {"
                                "color: black;"
                                "font-weight: bold;"
                                "}");


    //

    connect(loginButton, SIGNAL(clicked()), this, SLOT(loginClicked()));
    connect(registerButton, SIGNAL(clicked()), this, SLOT(registerClicked()));
    connect(showPasswordButton, &QPushButton::clicked, this, &Bank::togglePasswordVisibility);
    connect(adminWindow, &AdminWindow::tableCleared, this, &Bank::clearTable);

    if (!createConnection())
    {
        QMessageBox::critical(this, "Помилка", "Помилка при підключенні до бази даних");
    }






    createUserTable();
    createCreditTable();
    createCardsTable();









    QPalette pal = centralWidget->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230)); // Світлоголубий колір
    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(pal);

    QLabel *backgroundLabel = new QLabel(centralWidget);
    QPixmap backgroundImage("D:/Курсова/1221.png");
    backgroundLabel->setPixmap(backgroundImage);
    backgroundLabel->setScaledContents(true);

    layout->addWidget(backgroundLabel);
    layout->setAlignment(backgroundLabel, Qt::AlignCenter);


    QLabel *titleLabel = new QLabel("Банк.ua", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-weight: bold; color: yellow; font-size: 30px");
    layout->addWidget(titleLabel);

    QLabel *titleLabel1 = new QLabel("Рибачук Віталій", this);
    titleLabel1->setAlignment(Qt::AlignCenter);
    titleLabel1->setStyleSheet("font-weight: bold; color: yellow; font-size: 10px");

    layout->addWidget(titleLabel1);


}




Bank::~Bank()
{
    db.close();
}

void Bank::togglePasswordVisibility()
{
    passwordEdit->setEchoMode(passwordEdit->echoMode() == QLineEdit::Password ? QLineEdit::Normal : QLineEdit::Password);
}

bool Bank::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open())
    {
        return false;
    }
    return true;
}

void Bank::createUserTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Users (username TEXT PRIMARY KEY, password TEXT)");

    query.prepare("INSERT OR IGNORE INTO Users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", "myadmin");
    query.bindValue(":password", "1234");
    query.exec();
}

void Bank::createCreditTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS CreditHistory (CreditNumber INTEGER PRIMARY KEY, Username TEXT, Amount REAL, Date TEXT, CardNumber TEXT)");
}

void Bank::createCardsTable()
{
    QSqlQuery query;
    bool success = query.exec("CREATE TABLE IF NOT EXISTS Cards (Name TEXT, Pin TEXT, CardNumber TEXT, Username TEXT)");

    if (success)
    {
        qDebug() << "Таблиця Cards успішно створенна!";
    } else {
        qDebug() << "Таблиця Cards не створенна!:" << query.lastError().text();
    }
}


void Bank::loginClicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next())
    {
        if (username == "myadmin")
        {
            AdminWindow *adminWindow = new AdminWindow(this);
            connect(adminWindow, &AdminWindow::tableCleared, this, &Bank::clearTable);
            adminWindow->exec();
        } else
        {
            showUserWindow(username);
        }

        usernameEdit->clear();
        passwordEdit->clear();
    } else
    {
        QMessageBox::warning(this, "Логін", "Неправильний логін чи пароль");
    }
}


void Bank::registerClicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Реєстрація", "Заповніть усі необхідні поля!");

        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec())
    {
        QMessageBox::information(this, "Реєстрація", "Аккаунт успішно створено!");

        usernameEdit->clear();
        passwordEdit->clear();
    } else {
        QMessageBox::critical(this, "Реєстрація", "Помилка при створенні аккаунта!");
    }
}

void Bank::clearTable()
{    QSqlQuery query;

    query.prepare("DELETE FROM Cards WHERE Username != 'myadmin'");
    query.exec();


    query.prepare("DELETE FROM Users WHERE username != 'myadmin'");
    query.exec();

    query.prepare("DELETE FROM CreditHistory WHERE Username != 'myadmin'");
    query.exec();
}

void Bank::showUserWindow(const QString& username)
{  

    currentUsername = username;
    QDialog *userWindow = new QDialog(this);
    userWindow->setWindowTitle("Користувацьке вікно");
    userWindow->setFixedSize(500, 650);
    QVBoxLayout *layout = new QVBoxLayout(userWindow);

    QPushButton *getCreditButton = new QPushButton("Отримати кредит", userWindow);
    getCreditButton->setFixedHeight(35);
    QPushButton *viewCreditHistoryButton = new QPushButton("Подивитися актуальні кредити", userWindow);
    viewCreditHistoryButton->setFixedHeight(35);
    QPushButton *repayCreditButton = new QPushButton("Оплатити кредит", userWindow);
    repayCreditButton->setFixedHeight(35);

    QPushButton *showCardButton = new QPushButton("Карта банку", userWindow);
    showCardButton->setFixedHeight(35);

    layout->addWidget(showCardButton);
    layout->addWidget(getCreditButton);
    layout->addWidget(viewCreditHistoryButton);
    layout->addWidget(repayCreditButton);


    showCardButton->setStyleSheet("QPushButton {" "background-color: #A0CFE8;" "border-style: outset;" "border-width: 2px;" "border-radius: 10px;" "border-color: #80AEBD;" "font: bold 14px;" "min-width: 10em;" "padding: 6px;" "}" "QPushButton:hover {" "background-color: #C7E4F2;" "}" "QPushButton:pressed {" "background-color: #85B7D9;" "}");
    getCreditButton->setStyleSheet("QPushButton {" "background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;" "}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");
    viewCreditHistoryButton->setStyleSheet("QPushButton {" "background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;" "}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");
    repayCreditButton->setStyleSheet("QPushButton {" "background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;" "}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");

    connect(showCardButton, &QPushButton::clicked, this, &Bank::showUserCards);


    connect(getCreditButton, &QPushButton::clicked, [=]()
            {
        QDialog *creditDialog = new QDialog(userWindow);
        QVBoxLayout *creditLayout = new QVBoxLayout(creditDialog);

        QLineEdit *creditLineEdit = new QLineEdit(creditDialog);
        QPushButton *getCredit = new QPushButton("Отримати", creditDialog);

        QString styleForCreditLineEdit = "QLineEdit {"
            "background-color: #f0f0f0;" // Колір фону
            "border: 1px solid #999;"    // Рамка
            "border-radius: 5px;"        // Скругленість країв
            "padding: 5px;"              // Відступи в середині поля
            "font-size: 16px;"           // Розмір шрифту
            "}";
        creditLineEdit->setStyleSheet(styleForCreditLineEdit);


        creditLayout->addWidget(creditLineEdit);
        creditLayout->addWidget(getCredit);
            creditDialog->setFixedSize(300, 300);
            creditDialog->setWindowTitle("Введіть сумму кредиту:");
            getCredit->setStyleSheet("QPushButton {" "background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;" "}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");
            creditLineEdit->setFixedHeight(35);

        connect(getCredit, &QPushButton::clicked, [=]()
        {
            QString creditAmount = creditLineEdit->text();
            addCredit(currentUsername, creditAmount);
            creditDialog->close();
            QWidget::update();
        });

            QPalette pal = creditDialog->palette();
            pal.setColor(QPalette::Window, QColor(173, 216, 230));
            creditDialog->setAutoFillBackground(true);
            creditDialog->setPalette(pal);
            creditDialog->setLayout(layout);
            creditDialog->show();

    });


    connect(viewCreditHistoryButton, &QPushButton::clicked, [=]()
            {
        QDialog *historyDialog = new QDialog(this);
        historyDialog->setWindowTitle("Актуальні кредити");
        historyDialog->setFixedSize(300, 300);
        QPalette pal = historyDialog->palette();
        pal.setColor(QPalette::Window, QColor("#A0CFE8"));
        historyDialog->setAutoFillBackground(true);
        historyDialog->setPalette(pal);

        QVBoxLayout *layout = new QVBoxLayout(historyDialog);

        QLabel *noCreditLabel = new QLabel("Немає актуальних кредитів!", historyDialog);
        QFont font("Arial", 14);
        noCreditLabel->setFont(font);
        noCreditLabel->setAlignment(Qt::AlignCenter);
        noCreditLabel->setVisible(false);

        QTableWidget *creditHistoryTable = new QTableWidget(historyDialog);
        creditHistoryTable->setColumnCount(2);
        creditHistoryTable->setHorizontalHeaderLabels(QStringList() << "Дата" << "Сумма");
        creditHistoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        QSqlQuery query;
        query.prepare("SELECT Date, Amount FROM CreditHistory WHERE Username = :username");
        query.bindValue(":username", currentUsername);

        if (query.exec())
        {
            int row = 0;
            if (!query.next())
            {
                noCreditLabel->setVisible(true);
            } else {
                do {
                    QString date = query.value(0).toString();
                    QString amount = query.value(1).toString();

                    creditHistoryTable->insertRow(row);
                    creditHistoryTable->setItem(row, 0, new QTableWidgetItem(date));
                    creditHistoryTable->setItem(row, 1, new QTableWidgetItem(amount));

                    row++;
                } while (query.next());
            }
        } else {
            QMessageBox::warning(historyDialog, "Помилка", "Помилка при витягненні даних!");
        }

        layout->addWidget(noCreditLabel);
        layout->addWidget(creditHistoryTable);
        historyDialog->setLayout(layout);
        historyDialog->exec();
    });




    connect(repayCreditButton, &QPushButton::clicked, [=]()
            {
        QString creditAmount = getCreditAmountForUser(currentUsername);
        QDialog *repayDialog = new QDialog(userWindow);
        QVBoxLayout *repayLayout = new QVBoxLayout(repayDialog);


        QLineEdit *repayLineEdit = new QLineEdit(repayDialog);
        QPushButton *repayCreditButton = new QPushButton("Оплатити", repayDialog);

            if (creditAmount.toDouble() <= 0.0)
            {
                repayCreditButton->setEnabled(false);
            }

        QString styleForRepayLineEdit = "QLineEdit {"
                                        "background-color: #f0f0f0;" // Колір фону
                                        "border: 1px solid #999;"    // Рамка
                                        "border-radius: 5px;"        // Скругленість країв
                                        "padding: 5px;"              // Відступи в середині поля
                                        "font-size: 16px;"           // Розмір шрифту
                                        "}";
        repayLineEdit->setStyleSheet(styleForRepayLineEdit);


        repayLayout->addWidget(repayLineEdit);
        repayLayout->addWidget(repayCreditButton);
        repayDialog->setFixedSize(300, 300);
        repayDialog->setWindowTitle("Введіть номер кредиту:");
        repayCreditButton->setStyleSheet("QPushButton {" "background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;" "}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");
        repayLineEdit->setFixedHeight(35);

        QPalette pal = repayDialog->palette();
        pal.setColor(QPalette::Window, QColor("#A0CFE8"));
        repayDialog->setAutoFillBackground(true);
        repayDialog->setPalette(pal);

        connect(repayCreditButton, &QPushButton::clicked, [=]()
        {
            QString creditNumber = repayLineEdit->text();
            repayCredit(creditNumber);
            repayDialog->close();
            QWidget::update();
        });
        repayDialog->setLayout(layout);
        repayDialog->show();
    });

    QLabel *backgroundLabel = new QLabel(this);
    QPixmap backgroundImage("D:/Курсова/111.png");
    backgroundLabel->setPixmap(backgroundImage);
    backgroundLabel->setScaledContents(true);
    layout->addWidget(backgroundLabel);

    QPalette pal = userWindow->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230));
    userWindow->setAutoFillBackground(true);
    userWindow->setPalette(pal);
    userWindow->exec();

}

void Bank::addCredit(const QString& username, const QString& amount)
{
    QSqlQuery cardQuery;
    cardQuery.prepare("SELECT CardNumber FROM Cards WHERE Username = :username");
    cardQuery.bindValue(":username", username);
    cardQuery.exec();

    if (!cardQuery.next())
    {
        QMessageBox::warning(this, "Кредит", "Ви не маєте картки. Отримайте карту, перш ніж отримувати кредит.");
        return;
    }

    QString cardNumber = cardQuery.value(0).toString();

    double creditAmount = amount.toDouble();
    if (creditAmount < 2500 || creditAmount > 250000)
    {
        QMessageBox::warning(this, "Кредит", "Сума кредиту повинна бути від 2500 до 250 000!");
        return;
    }

    int creditNumber = getNextCreditNumber();

    if (creditNumber == -1)
    {
        QMessageBox::critical(this, "Кредит", "Помилка отримання номера кредиту!");
        return;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO CreditHistory (CreditNumber, Username, Amount, Date) "
                  "VALUES (:creditNumber, :username, :amount, :creditDate)");
    query.bindValue(":creditNumber", creditNumber);
    query.bindValue(":username", username);
    query.bindValue(":amount", creditAmount);
    query.bindValue(":creditDate", QDateTime::currentDateTime().toString(Qt::ISODate));



    if (query.exec())
    {
        QMessageBox::information(this, "Кредит", "Кредит успішно оформлено!!");
    } else {
        QMessageBox::critical(this, "Кредит", "Помилка при створенні кредиту! " + query.lastError().text());
    }
}

int Bank::getNextCreditNumber()
{
    QSqlQuery query("SELECT MAX(CreditNumber) FROM CreditHistory");
    if (query.exec() && query.next()) {
        int maxCreditNumber = query.value(0).toInt();
        return maxCreditNumber + 1;
    }
    return 1; //1, якщо не отримати максимальний номер кредиту
}


void Bank::repayCredit(const QString& creditNumber)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CreditHistory WHERE CreditNumber = :creditNumber");
    query.bindValue(":creditNumber", creditNumber);

    if (query.exec())
    {
        QMessageBox::information(this, "Оплата", "Кредит успішно оплачено!");

        QSqlQuery updateQuery;
        updateQuery.prepare("SELECT CreditNumber FROM CreditHistory WHERE Username = :username");
        updateQuery.bindValue(":username", currentUsername);
        if (updateQuery.exec())
        {
            int newCreditNumber = 1;
            while (updateQuery.next()) {
                int currentCreditNumber = updateQuery.value(0).toInt();

                QSqlQuery updateNumberQuery;
                updateNumberQuery.prepare("UPDATE CreditHistory SET CreditNumber = :newCreditNumber WHERE CreditNumber = :currentCreditNumber AND Username = :username");
                updateNumberQuery.bindValue(":newCreditNumber", newCreditNumber);
                updateNumberQuery.bindValue(":currentCreditNumber", currentCreditNumber);
                updateNumberQuery.bindValue(":username", currentUsername);
                updateNumberQuery.exec();

                newCreditNumber++;
            }
        }
    } else {
        QMessageBox::critical(this, "Repay", "Помилка при оплаті кредиту!");
    }
}



void Bank::showCredits()
{
    if (!adminWindow)
    {
        adminWindow = new AdminWindow(this);
        connect(adminWindow, &AdminWindow::tableCleared, this, &Bank::clearTable);
    }
    adminWindow->showCredits();
}

void Bank::showUserCards()
{

    QDialog *cardDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(cardDialog);
    cardDialog->setWindowTitle("Карта банку");
    cardDialog->setFixedSize(300, 200);

    QPushButton *cardButton = new QPushButton("Карта", cardDialog);
    QPushButton *getCardButton = new QPushButton("Отримати карту", cardDialog);
    QPushButton *deleteCardButton = new QPushButton("Видалити карту", cardDialog);


    layout->addWidget(cardButton);
    layout->addWidget(getCardButton);
    layout->addWidget(deleteCardButton);

    //Карта
    QSqlQuery query;
    query.prepare("SELECT CardNumber FROM Cards WHERE Username = :username");
    query.bindValue(":username", currentUsername);
    query.exec();

    if (!query.next())
    {
        cardButton->setEnabled(false);
    } else
    {
        cardButton->setEnabled(true);
    }

    //Отримати карту
    query.prepare("SELECT CardNumber FROM Cards WHERE Username = :username");
    query.bindValue(":username", currentUsername);
    query.exec();
    if (query.next())
    {
        getCardButton->setEnabled(false);
    }

    cardButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");
    getCardButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");
    deleteCardButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");

connect(cardButton, &QPushButton::clicked, [=]()
            {
    bool ok;
    QString pin = QInputDialog::getText(this, tr("Введіть пін-код"), tr("Пін-код:"), QLineEdit::Password, QString(), &ok);

    if (ok && !pin.isEmpty())
    {
        QSqlQuery query;
        query.prepare("SELECT Pin, CardNumber, Name FROM Cards WHERE Username = :username");
        query.bindValue(":username", currentUsername);
        query.exec();

        QString storedPin;
        QString cardNumber;
        QString cardName;
        QString creditAmount;

        while (query.next()) {
            storedPin = query.value(0).toString();
            cardNumber = query.value(1).toString();
            cardName = query.value(2).toString();
        }

        if (pin == storedPin)
        {
            creditAmount = getCreditAmountForUser(currentUsername);  // оновлення суми кредиту після перевірки піна

            QDialog *cardDetailsDialog = new QDialog(this);
            QVBoxLayout *layout = new QVBoxLayout(cardDetailsDialog);

            QString styledCardNumber = "<font size='5'>" + cardNumber + "</font>";
            QLabel *cardNumberLabel = new QLabel("<font size='5'>Номер картки: </font>" + styledCardNumber);
            cardNumberLabel->setAlignment(Qt::AlignCenter);

            QString styledCardName = "<font size='5'>" + cardName + "</font>";
            QLabel *cardNameLabel = new QLabel("<font size='5'>Власник картки: </font>" + styledCardName);
            cardNameLabel->setAlignment(Qt::AlignCenter);

            QString styledCreditAmount = "<font size='5'>" + creditAmount + "</font>";
            QLabel *creditAmountLabel = new QLabel("<font size='5'>Сумма кредиту: </font>" + styledCreditAmount);
            creditAmountLabel->setAlignment(Qt::AlignCenter);

            if (creditAmount.toDouble() <= 0.0)
            {
                styledCreditAmount = "<font size='5' color='#888'>0.00</font>";
                creditAmountLabel->setText("<font size='5'>Сумма кредиту: </font>" + styledCreditAmount);
                creditAmountLabel->setText("<font size='5'>Сумма кредиту: 0.00</font>");
                creditAmountLabel->setStyleSheet("color: #888;");
            }

            layout->addWidget(cardNumberLabel);
            layout->addWidget(cardNameLabel);
            layout->addWidget(creditAmountLabel);

            QFrame *frame = new QFrame(cardDetailsDialog);
            frame->setFrameShape(QFrame::Box);
            frame->setLineWidth(2);
            frame->setMidLineWidth(1);
            frame->setStyleSheet("color: #333; background-color: #FFF;");
            QVBoxLayout *frameLayout = new QVBoxLayout(frame);
            frameLayout->addWidget(cardNumberLabel);
            frameLayout->addWidget(cardNameLabel);
            frameLayout->addWidget(creditAmountLabel);
            layout->addWidget(frame);

            QLabel *imageLabel = new QLabel(cardDetailsDialog);
            QPixmap image("D:/Курсова/13.png");
            imageLabel->setPixmap(image);
            imageLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            layout->addWidget(imageLabel);

            cardDetailsDialog->setLayout(layout);

            QPalette pal = cardDetailsDialog->palette();
            pal.setColor(QPalette::Window, QColor(173, 216, 230));
            cardDetailsDialog->setAutoFillBackground(true);
            cardDetailsDialog->setPalette(pal);
            cardDetailsDialog->exec();
        } else {
            QMessageBox::warning(this, tr("Помилка"), tr("Неправильний пін-код!"));
        }
    }
});




    connect(getCardButton, &QPushButton::clicked, [=]()
    {
        QDialog *getCardDialog = new QDialog(cardDialog);
        getCardDialog->setWindowTitle("Отримати карту");
        getCardDialog->setFixedSize(300, 200);

        QLineEdit *nameLineEdit = new QLineEdit(getCardDialog);
        QLineEdit *pinLineEdit = new QLineEdit(getCardDialog);
        pinLineEdit->setEchoMode(QLineEdit::Password);

        QPushButton *createCardButton = new QPushButton("Створити карту", getCardDialog);

        QVBoxLayout *getCardLayout = new QVBoxLayout(getCardDialog);
        getCardLayout->addWidget(new QLabel("Ім'я та прізвище:"));
        getCardLayout->addWidget(nameLineEdit);
        getCardLayout->addWidget(new QLabel("Пін-код:"));
        getCardLayout->addWidget(pinLineEdit);
        getCardLayout->addWidget(createCardButton);

        connect(createCardButton, &QPushButton::clicked, [=]() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 9999);

            QString cardNumber = QString::number(dis(gen)).rightJustified(4, '0');

            addCardToDatabase(nameLineEdit->text(), pinLineEdit->text(), cardNumber, currentUsername);
            QMessageBox::information(getCardDialog, "Карта", "Карта успішно створена! Номер вашої карти: " + cardNumber);
            getCardDialog->close();
            getCardButton->setEnabled(false);
        });
        getCardDialog->exec();
    });

connect(deleteCardButton, &QPushButton::clicked, [=]()
    {
        if (hasCredits(currentUsername))
        {
            QMessageBox::warning(cardDialog, "Карта", "У вас є кредити. Спочатку оплатіть їх перед видаленням картки.");
            return;
        }

    QDialog *pinDialog = new QDialog(cardDialog);
    pinDialog->setWindowTitle("Введіть пін-код");
    pinDialog->setFixedSize(300, 200);

    QLineEdit *pinLineEdit = new QLineEdit(pinDialog);
    pinLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *confirmButton = new QPushButton("Підтвердити", pinDialog);

    QVBoxLayout *pinLayout = new QVBoxLayout(pinDialog);
    pinLayout->addWidget(new QLabel("Введіть пін-код для підтвердження видалення"));
    pinLayout->addWidget(pinLineEdit);
    pinLayout->addWidget(confirmButton);

    QPalette pal = pinDialog->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230));
    pinDialog->setAutoFillBackground(true);
    pinDialog->setPalette(pal);


    confirmButton->setStyleSheet("QPushButton {" "background-color: #A0CFE8;" "border-style: outset;" "border-width: 2px;" "border-radius: 10px;" "border-color: #80AEBD;" "font: bold 14px;" "min-width: 10em;" "padding: 6px;" "}" "QPushButton:hover {" "background-color: #C7E4F2;" "}" "QPushButton:pressed {" "background-color: #85B7D9;" "}");

    connect(confirmButton, &QPushButton::clicked, [=]()
            {
        QString enteredPin = pinLineEdit->text();

        QSqlQuery query;
        query.prepare("SELECT Pin FROM Cards WHERE Username = :username");
        query.bindValue(":username", currentUsername);
        query.exec();

        if (query.next())
        {
            QString storedPin = query.value(0).toString();

            if (enteredPin == storedPin)
            {
                QSqlQuery deleteQuery;
                deleteQuery.prepare("DELETE FROM Cards WHERE Username = :username");
                deleteQuery.bindValue(":username", currentUsername);

                if (deleteQuery.exec()) {
                    QMessageBox::information(pinDialog, "Карта", "Картку успішно видалено!");
                    pinDialog->close();
                } else {
                    QMessageBox::critical(pinDialog, "Карта", "Помилка видалення картки!");
                }
            } else {
                QMessageBox::warning(pinDialog, "Помилка", "Неправильний пін-код!");
            }
        } else {
            QMessageBox::warning(pinDialog, "Помилка", "Помилка при отриманні пін-коду з бази даних!");
        }
    });

    pinDialog->exec();
});

    QPalette pal = cardDialog->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230));
    cardDialog->setAutoFillBackground(true);
    cardDialog->setPalette(pal);

    cardDialog->exec();
}


void Bank::addCardToDatabase(const QString& name, const QString& pin, const QString& cardNumber, const QString& username)
{
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Cards (Name, Pin, CardNumber, Username) VALUES (:name, :pin, :cardNumber, :username)");
    insertQuery.bindValue(":name", name);
    insertQuery.bindValue(":pin", pin);
    insertQuery.bindValue(":cardNumber", cardNumber);
    insertQuery.bindValue(":username", username);
    insertQuery.exec();
}


QString Bank::getCreditAmountForUser(const QString& username)
{
    QSqlQuery query;
    query.prepare("SELECT SUM(Amount) FROM CreditHistory WHERE Username = :username");
    query.bindValue(":username", username);
    query.exec();

    if (query.next())
    {
        return query.value(0).toString();
    }

    return "0.00";
}

bool Bank::hasCredits(const QString& username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM CreditHistory WHERE Username = :username");
    query.bindValue(":username", username);
    query.exec();

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}

