#include "mainwindow.h"
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
#include "databasemanager.h"
#include "userwindowmanager.h"
#include "usercardmanager.h"
#include <QApplication>
#include <QDir>
UserWindowManager::UserWindowManager(QObject *parent) : QObject(parent), userWindow(nullptr) {userCardManagerInstance = new UserCardManager();}

void UserWindowManager::showUserWindow(const QString& username)
{
    currentUsername = username;
    userWindow = new QDialog();
    db = new DatabaseManager(this);
    userWindow->setWindowTitle("Користувацьке вікно");
    userWindow->setFixedSize(500, 650);
    QVBoxLayout *layout = new QVBoxLayout(userWindow);


    QPushButton *viewCreditHistoryButton = new QPushButton("Подивитися актуальні кредити", userWindow);
    viewCreditHistoryButton->setFixedHeight(35);
    QPushButton *showCardButton = new QPushButton("Карта банку", userWindow);
    showCardButton->setFixedHeight(35);

    layout->addWidget(showCardButton);
    layout->addWidget(viewCreditHistoryButton);

    showCardButton->setStyleSheet("QPushButton {" "background-color: #A0CFE8;" "border-style: outset;" "border-width: 2px;" "border-radius: 10px;" "border-color: #80AEBD;" "font: bold 14px;" "min-width: 10em;" "padding: 6px;" "}" "QPushButton:hover {" "background-color: #C7E4F2;" "}" "QPushButton:pressed {" "background-color: #85B7D9;" "}");
    viewCreditHistoryButton->setStyleSheet("QPushButton {" "background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;" "}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");
    connect(showCardButton, &QPushButton::clicked, [=]() {
        userCardManagerInstance->showUserCards(currentUsername);
    });


    connect(viewCreditHistoryButton, &QPushButton::clicked, [=]()
            {
        QDialog *historyDialog = new QDialog(userWindow);
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
            } else
            {
                do
                {
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
    QPushButton *changePasswordButton = new QPushButton("Змінити пароль", userWindow);
    changePasswordButton->setFixedHeight(35);
    changePasswordButton->setStyleSheet("QPushButton {" "background-color: #A0CFE8;" "border-style: outset;" "border-width: 2px;" "border-radius: 10px;" "border-color: #80AEBD;" "font: bold 14px;" "min-width: 10em;" "padding: 6px;" "}" "QPushButton:hover {" "background-color: #C7E4F2;" "}" "QPushButton:pressed {" "background-color: #85B7D9;" "}");
    layout->addWidget(changePasswordButton);
    connect(changePasswordButton, &QPushButton::clicked, [=]() {changePassword(username);});

    QPushButton *applyForLoanButton = new QPushButton("Кредитування", userWindow);
    applyForLoanButton->setFixedHeight(35);
    applyForLoanButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");

    layout->addWidget(applyForLoanButton);

    QSqlQuery query;
    query.prepare("SELECT canTakeLoan, age, salary FROM Users WHERE username = :username");
    query.bindValue(":username", username);
    bool takeLoan = false;
    int userAge = 0;
    int usersalary = 0;
    if (query.exec() && query.next())
    {
        takeLoan = query.value(0).toBool();
        userAge = query.value(1).toInt();
        usersalary = query.value(2).toInt();
    }
    if (takeLoan)
    {
        applyForLoanButton->setEnabled(false);
    }
    if (userAge && usersalary)
    {
        applyForLoanButton->setEnabled(false);
    }


    connect(applyForLoanButton, &QPushButton::clicked, [=]() {showLoanDialog(username); });

    QString imagePath = QDir(QCoreApplication::applicationDirPath()).filePath("Картинки/111.png");
    QLabel *backgroundLabel = new QLabel();
    QPixmap backgroundImage(imagePath);
    backgroundLabel->setPixmap(backgroundImage);
    backgroundLabel->setScaledContents(true);
    layout->addWidget(backgroundLabel);

    QPalette pal = userWindow->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230));
    userWindow->setAutoFillBackground(true);
    userWindow->setPalette(pal);
    userWindow->exec();

}

void UserWindowManager::changePassword(const QString& username)
{
    QString newPassword = QInputDialog::getText(nullptr, "Зміна пароля", "Введіть новий пароль:", QLineEdit::Password);

    if (!newPassword.isEmpty()) {
        QByteArray hashedNewPassword = QCryptographicHash::hash(newPassword.toUtf8(), QCryptographicHash::Md5).toHex();

        QSqlQuery query;
        query.prepare("UPDATE Users SET password = :newPassword WHERE username = :username");
        query.bindValue(":newPassword", hashedNewPassword);
        query.bindValue(":username", username);

        if (query.exec())
        {
            QMessageBox::information(nullptr, "Зміна пароля", "Пароль успішно змінено!");
        } else
        {
            QMessageBox::critical(nullptr, "Зміна пароля", "Помилка при зміні пароля!");
        }
    }
}

int UserWindowManager::getNextCreditNumber()
{
    QSqlQuery query("SELECT MAX(CreditNumber) FROM CreditHistory");
    if (query.exec() && query.next()) {
        int maxCreditNumber = query.value(0).toInt();
        return maxCreditNumber + 1;
    }
    return 1;
}


QString UserWindowManager::getCreditAmountForUser(const QString& username)
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

bool UserWindowManager::hasCredits(const QString& username)
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

void UserWindowManager::showUserCards()
{
    UserCardManager cardManager;

    cardManager.showUserCards(currentUsername);
}

void UserWindowManager::showLoanDialog(const QString& username)
{
    QDialog *loanDialog = new QDialog();
    loanDialog->setWindowTitle("Кредитування");
    loanDialog->setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(loanDialog);

    QLabel *ageLabel = new QLabel("Введіть вік:", loanDialog);
    QLineEdit *ageLineEdit = new QLineEdit(loanDialog);
    layout->addWidget(ageLabel);
    layout->addWidget(ageLineEdit);

    QLabel *workplaceLabel = new QLabel("Введіть місце роботи:", loanDialog);
    QLineEdit *workplaceLineEdit = new QLineEdit(loanDialog);
    layout->addWidget(workplaceLabel);
    layout->addWidget(workplaceLineEdit);

    QLabel *salaryLabel = new QLabel("Введіть зарплату:", loanDialog);
    QLineEdit *salaryLineEdit = new QLineEdit(loanDialog);
    layout->addWidget(salaryLabel);
    layout->addWidget(salaryLineEdit);

    QPushButton *applyLoanButton = new QPushButton("Застосувати", loanDialog);
    layout->addWidget(applyLoanButton);

    connect(applyLoanButton, &QPushButton::clicked, [=]()
            {
        int age = ageLineEdit->text().toInt();
        QString workplace = workplaceLineEdit->text();
        double salary = salaryLineEdit->text().toDouble();

        bool canTakeLoan = checkLoanEligibility(age, salary);

        QSqlQuery query;
        query.prepare("UPDATE Users SET employmentPlace = :workplace WHERE username = :username");
        query.bindValue(":workplace", workplace);
        query.bindValue(":username", currentUsername);

        if (query.exec())
        {
            if (canTakeLoan)
            {
                QMessageBox::information(nullptr, "Оновлення даних", "Інформація про користувача оновлена!");
                databaseManagerInstance.updateUserLoanStatus(true, currentUsername);
            } else {
                QMessageBox::warning(nullptr, "Відмова в кредиті", "На жаль, ви не можете отримати кредит наразі.");
            }
        } else {
            QMessageBox::critical(nullptr, "Помилка", "Помилка при оновленні даних користувача!");
        }

        loanDialog->close();
    });

    applyLoanButton->setStyleSheet("QPushButton { background-color: #A0CFE8; border-style: outset; border-width: 2px; border-radius: 10px; border-color: #80AEBD; font: bold 14px; min-width: 10em; padding: 6px; } QPushButton:hover { background-color: #C7E4F2; } QPushButton:pressed { background-color: #85B7D9; }");
    ageLabel->setStyleSheet("QLabel { font-weight: bold; }");
    workplaceLabel->setStyleSheet("QLabel { font-weight: bold; }");
    salaryLabel->setStyleSheet("QLabel { font-weight: bold; }");
    ageLineEdit->setStyleSheet("QLineEdit { border: 1px solid #000; border-radius: 5px; padding: 2px; }");
    workplaceLineEdit->setStyleSheet("QLineEdit { border: 1px solid #000; border-radius: 5px; padding: 2px; }");
    salaryLineEdit->setStyleSheet("QLineEdit { border: 1px solid #000; border-radius: 5px; padding: 2px; }");
    loanDialog->setStyleSheet("background-color: #E6F0F5;");
    loanDialog->setLayout(layout);
    loanDialog->exec();
    userWindow->close();
    showUserWindow(username);
}


bool UserWindowManager::checkLoanEligibility(int age, double salary)
{
    QSqlQuery query;
    query.prepare("UPDATE Users SET age = :age, salary = :salary WHERE username = :username");
    query.bindValue(":age", age);
    query.bindValue(":salary", salary);
    query.bindValue(":username", currentUsername);

    if (query.exec())
    {
        qDebug() << "Інформація оновлена!";
    } else {
        qDebug() << "Помилка при оновлені інформації:" << query.lastError().text();
    }

    bool canTakeLoan = true;
    if (age < 18)
    {
        canTakeLoan = false;
        QMessageBox::warning(nullptr, "Неприпустимий вік", "Вибачте, ви не досягли потрібного віку для кредитування (18+).");
    }

    if (age > 99)
    {
        QMessageBox::warning(nullptr, "Неприпустимий вік", "Введіть дійсний вік!");
    }

    if (salary < 10000)
    {
        canTakeLoan = false;
        QMessageBox::warning(nullptr, "Низька зарплата", "Вибачте, ваша зарплата нижче мінімальної для кредитування (10 000+).");
    }

    return canTakeLoan;
}
