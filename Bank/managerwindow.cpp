#include "managerwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDateTime>
#include <QSqlQueryModel>
#include "databasemanager.h"

ManagerWindow::ManagerWindow(QWidget *parent) : QDialog(parent){showManagerWindow();}

void ManagerWindow::showManagerWindow()
{
    setWindowTitle("Менеджерське вікно");
    setFixedSize(700, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);
    repayCreditButton = new QPushButton("Оплатити кредит", this);
    layout->addWidget(repayCreditButton);

    creditTable = new QTableWidget(this);
    layout->addWidget(creditTable);

    QPushButton *issueCreditButton = new QPushButton("Видати кредит", this);
    issueCreditButton->setFixedHeight(35);

    layout->addWidget(issueCreditButton);

    applyButtonStyle(repayCreditButton);
    applyButtonStyle(issueCreditButton);

    connect(repayCreditButton, &QPushButton::clicked, this, &ManagerWindow::repayCredit);
    connect(issueCreditButton, &QPushButton::clicked, this, &ManagerWindow::showIssueCreditDialog);

    QPalette pal = palette();

    pal.setColor(QPalette::Window, QColor(173, 216, 230));

    setAutoFillBackground(true);
    setPalette(pal);
    databaseManager = new DatabaseManager(this);
    updateCreditTable();
}


ManagerWindow::~ManagerWindow() {delete databaseManager;}

void ManagerWindow::repayCredit()
{
    QSqlQuery query("SELECT id FROM CreditHistory ORDER BY id ASC");

    if (!query.next()) {
        QMessageBox::warning(this, "Попередження", "Немає кредитів для оплати!");
        return;
    }

    QStringList creditIds;
    QSqlQueryModel model;
    model.setQuery("SELECT id FROM CreditHistory ORDER BY id ASC");
    int rows = model.rowCount();
    for (int i = 0; i < rows; ++i)
    {
        creditIds.append(QString::number(i + 1));
    }

    bool ok;
    QString creditId = QInputDialog::getText(this, "Оплата кредиту", "Введіть ID кредиту:", QLineEdit::Normal, "", &ok);

    if (ok && !creditId.isEmpty())
    {
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM CreditHistory WHERE id = :creditId");
        deleteQuery.bindValue(":creditId", creditId);

        if (deleteQuery.exec())
        {
            QSqlQuery updateQuery("SELECT id FROM CreditHistory ORDER BY id ASC");
            int row = 1;
            while (updateQuery.next())
            {
                int currentCreditId = updateQuery.value(0).toInt();
                QSqlQuery updateNumberQuery;
                updateNumberQuery.prepare("UPDATE CreditHistory SET id = :row WHERE id = :currentId");
                updateNumberQuery.bindValue(":row", row);
                updateNumberQuery.bindValue(":currentId", currentCreditId);
                updateNumberQuery.exec();
                ++row;
            }

            QMessageBox::information(this, "Оплата кредиту", "Кредит успішно оплачено!");
            updateCreditTable();
            databaseManager->updateCreditSequence();
        } else
        {
            QMessageBox::critical(this, "Помилка", "Помилка при оплаті кредиту: " + deleteQuery.lastError().text());
        }
    } else
    {
        QMessageBox::warning(this, "Попередження", "Будь ласка, введіть ID кредиту!");
    }
}




void ManagerWindow::updateCreditTable()
{
    creditTable->clear();
    creditTable->setRowCount(0);
    creditTable->setColumnCount(5);
    QStringList headers = {"Номер кредиту","Акаунт","Ім'я та прізвище", "Сума", "Дата оформлення"};
    creditTable->setHorizontalHeaderLabels(headers);

    QSqlQuery query("SELECT CreditHistory.id, Cards.Username, Cards.Name, CreditHistory.Amount, CreditHistory.Date ""FROM CreditHistory ""INNER JOIN Cards ON CreditHistory.Username = Cards.Username ""ORDER BY CreditHistory.id ASC");
    int row = 0;
    while (query.next())
    {
        QString creditNumber = QString::number(row + 1);
        QString username = query.value(1).toString();
        QString name = query.value(2).toString();
        QString amount = query.value(3).toString();
        QString creditDate = query.value(4).toString();

        creditTable->insertRow(row);
        creditTable->setItem(row, 0, new QTableWidgetItem(creditNumber));
        creditTable->setItem(row, 1, new QTableWidgetItem(username));
        creditTable->setItem(row, 2, new QTableWidgetItem(name));
        creditTable->setItem(row, 3, new QTableWidgetItem(amount));
        creditTable->setItem(row, 4, new QTableWidgetItem(creditDate));

        for (int col = 0; col < creditTable->columnCount(); ++col) {
            creditTable->item(row, col)->setTextAlignment(Qt::AlignCenter);
        }

        ++row;
    }

    for (int i = 0; i < creditTable->rowCount(); ++i) {
        creditTable->item(i, 0)->setText(QString::number(i + 1));
    }

    creditTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    creditTable->clearSelection();
}




void ManagerWindow::showIssueCreditDialog()
{
    QDialog *issueCreditDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(issueCreditDialog);
    issueCreditDialog->setWindowTitle("Видання кредиту");
    issueCreditDialog->setFixedSize(300, 200);

    QLineEdit *accountLineEdit = new QLineEdit(issueCreditDialog);
    QLineEdit *amountLineEdit = new QLineEdit(issueCreditDialog);

    QPushButton *issueCreditButton = new QPushButton("Видати кредит", issueCreditDialog);

    QString buttonStyle = "QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}";

    issueCreditButton->setStyleSheet(buttonStyle);

    layout->addWidget(new QLabel("Назва акаунта:"));
    layout->addWidget(accountLineEdit);
    layout->addWidget(new QLabel("Сума кредиту:"));
    layout->addWidget(amountLineEdit);
    layout->addWidget(issueCreditButton);

    connect(issueCreditButton, &QPushButton::clicked, [=]() {
        QString account = accountLineEdit->text();
        QString amount = amountLineEdit->text();
        issueCreditToAccount(account, amount);
        issueCreditDialog->close();
    });

    QPalette pal = issueCreditDialog->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230));
    issueCreditDialog->setAutoFillBackground(true);
    issueCreditDialog->setPalette(pal);

    issueCreditDialog->exec();
}

void ManagerWindow::issueCreditToAccount(const QString& username, const QString& amount)
{

    if (!isAccountExists(username))
    {
        QMessageBox::warning(nullptr, "Помилка", "Такого акаунта не існує.");
        updateCreditTable();
        return;
    }

    if (!hasCard(username))
    {
        QMessageBox::warning(nullptr, "Помилка", "Користувач не має картки.");
        updateCreditTable();
        return;
    }

    if (!canTakeLoan(username))
    {
        QMessageBox::warning(nullptr, "Помилка", "Користувач не має дозволу на отримання кредиту.");
        updateCreditTable();
        return;
    }

    double creditAmount = amount.toDouble();
    if (creditAmount <= 0) {
        QMessageBox::warning(nullptr, "Помилка", "Сума кредиту повинна бути більше 0.");
        updateCreditTable();
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO CreditHistory (Username, Amount, Date) "
                  "VALUES (:username, :amount, :creditDate)");
    query.bindValue(":username", username);
    query.bindValue(":amount", creditAmount);
    query.bindValue(":creditDate", QDateTime::currentDateTime().toString(Qt::ISODate));

    if (query.exec())
    {
        QMessageBox::information(nullptr, "Кредит", "Кредит успішно нараховано на рахунок " + username + " на суму " + amount);
        updateCreditTable();
    } else {
        QMessageBox::critical(nullptr, "Кредит", "Помилка при нарахуванні кредиту: " + query.lastError().text());
        updateCreditTable();
    }
}

bool ManagerWindow::hasCard(const QString& username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Cards WHERE Username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

bool ManagerWindow::isAccountExists(const QString& username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

bool ManagerWindow::canTakeLoan(const QString& username)
{
    QSqlQuery query;
    query.prepare("SELECT canTakeLoan FROM Users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next())
    {
        return query.value(0).toBool();
    }

    return false;
}

void ManagerWindow::applyButtonStyle(QPushButton* button)
{
    button->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;}""QPushButton:hover {""background-color: #C7E4F2;}""QPushButton:pressed {""background-color: #85B7D9;}");
}

void ManagerWindow::applyTextEditStyle(QTextEdit* textEdit)
{
    textEdit->setStyleSheet("QTextEdit {""background-color: #FFFFFF;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 12px;""padding: 6px;}");
}
