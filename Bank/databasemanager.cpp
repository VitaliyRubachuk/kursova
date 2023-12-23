#include "databasemanager.h"
#include <QDebug>
#include <QSqlError>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QCoreApplication>
#include <QInputDialog>
#include <QLineEdit>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {}

DatabaseManager::~DatabaseManager()
{
    db.close();
}


bool DatabaseManager::createConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("users");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open())
    {
        qDebug() << "Помилка підключення до бази даних:" << db.lastError().text();
        return false;
    }
    qDebug() << "Підключення до бази даних встановлено.";
    return true;
}



void DatabaseManager::createUserTable()
{
    QByteArray passwordAdmin = QCryptographicHash::hash("1234", QCryptographicHash::Md5).toHex();
    QByteArray passwordManager = QCryptographicHash::hash("1231", QCryptographicHash::Md5).toHex();

    QString hashedPasswordAdmin = QString::fromLatin1(passwordAdmin);
    QString hashedPasswordManager = QString::fromLatin1(passwordManager);

    QSqlQuery query(db);

    query.exec("SELECT MAX(id) FROM Users");
    query.next();
    int maxId = query.value(0).toInt();
    int nextId = maxId + 1;

    query.exec("CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY, username VARCHAR(255) UNIQUE, password TEXT, role TEXT, CreationDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP, employmentPlace TEXT, salary INTEGER, age INTEGER, canTakeLoan BOOLEAN DEFAULT FALSE)");

    qDebug() << "Виконується запит: " << query.lastQuery();
    if (!query.exec())
    {
    qDebug() << "Запит не вдалося виконати: " << query.lastError().text();
    } else
    {
    qDebug() << "Запит успішно виконано";
    }

    query.prepare("INSERT IGNORE INTO Users (id, username, password, role, employmentPlace, salary, age, canTakeLoan) ""VALUES (:id, :username, :password, :role, :employmentPlace, :salary, :age, :canTakeLoan)");
    query.bindValue(":id", nextId);
    query.bindValue(":username", "myadmin");
    query.bindValue(":password", hashedPasswordAdmin);
    query.bindValue(":role", "admin");
    query.bindValue(":employmentPlace", "Bank.ua");  // Додати значення за замовчуванням для роботи
    query.bindValue(":salary", 100000); // Додати значення за замовчуванням для зарплати адміна
    query.bindValue(":age", 34);
    query.bindValue(":canTakeLoan", false);
    query.exec();

    nextId++;
    query.bindValue(":id", nextId);
    query.bindValue(":username", "manager");
    query.bindValue(":password", hashedPasswordManager);
    query.bindValue(":role", "manager");
    query.bindValue(":employmentPlace", "Bank.ua");  // Додати значення за замовчуванням для роботи
    query.bindValue(":salary", 50000);  // Додати значення за замовчуванням для зарплати менеджера
    query.bindValue(":age", 22);
    query.bindValue(":canTakeLoan", false);
    query.exec();
}
void DatabaseManager::createCreditTable()
{
    QSqlQuery query(db);

    bool success = query.exec("CREATE TABLE IF NOT EXISTS CreditHistory (id INTEGER PRIMARY KEY AUTO_INCREMENT, Username TEXT, Amount REAL, Date TEXT)");

    if (!success)
    {
        qDebug() << "Помилка SQL запиту:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Таблиця CreditHistory успішно створена!";
    }
}


void DatabaseManager::createCardsTable()
{
    QSqlQuery query(db);

    bool success = query.exec("CREATE TABLE IF NOT EXISTS Cards (Id INTEGER PRIMARY KEY AUTO_INCREMENT, Name TEXT, Pin TEXT, CardNumber TEXT, Username TEXT, City TEXT, Address TEXT, TaxCode TEXT)");
    if (success)
    {
        qDebug() << "Таблиця Cards успішно створена!";
    } else {
        qDebug() << "Таблиця Cards не створена!:" << query.lastError().text();
    }
}


void DatabaseManager::clearTable()
{
    QString userCode = QInputDialog::getText(nullptr, "Введіть код", "Введіть код:", QLineEdit::Normal, "", nullptr, Qt::WindowFlags(), Qt::ImhNone);

    if (userCode != "1111")
    {
        QMessageBox messageBox;
        messageBox.warning(nullptr, "Помилка", "Введений невірний код. Очищення таблиці відхилено.");
        return;
    }

    QSqlQuery query(db);
    query.exec("DELETE FROM CreditHistory");
    query.exec("DELETE FROM Cards");
    query.exec("DELETE FROM sqlite_sequence WHERE name='CreditHistory'");
    query.exec("DELETE FROM sqlite_sequence WHERE name='Cards'");
    query.exec("DELETE FROM Users WHERE role <> 'admin' AND role <> 'manager'");
    emit tablesCleared();
}



void DatabaseManager::updateCreditSequence()
{
    QSqlQuery query(db);
    query.exec("DELETE FROM sqlite_sequence WHERE name='CreditHistory'");

    query.exec("SELECT MAX(id) FROM CreditHistory");
    query.next();
    int maxId = query.value(0).toInt();

    query.exec(QString("INSERT INTO sqlite_sequence (name, seq) VALUES ('CreditHistory', %1)").arg(maxId));
}

void DatabaseManager::addCardToDatabase(const DatabaseParams& params)
{
    QSqlQuery maxIdQuery("SELECT MAX(Id) FROM Cards");
    maxIdQuery.exec();
    int maxId = maxIdQuery.next() ? maxIdQuery.value(0).toInt() : 0;
    int newId = maxId + 1;

    bool ok;
    pinValue = params.pin.toInt(&ok);
    if (params.pin.length() != 4 || !ok)
    {
        QMessageBox::warning(nullptr, tr("Помилка"), tr("Пін-код повинен містити рівно 4 цифри!"));
        return;
    }

    QByteArray hashedPin = QCryptographicHash::hash(params.pin.toUtf8(), QCryptographicHash::Sha256);

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Cards (Id, Name, Pin, CardNumber, Username, City, Address, TaxCode) VALUES (:id, :name, :pin, :cardNumber, :username, :city, :address, :taxCode)");
    insertQuery.bindValue(":id", newId);
    insertQuery.bindValue(":name", params.firstName + " " + params.lastName);
    insertQuery.bindValue(":pin", hashedPin.toHex());
    insertQuery.bindValue(":cardNumber", params.cardNumber);
    insertQuery.bindValue(":username", params.username);
    insertQuery.bindValue(":city", params.city);
    insertQuery.bindValue(":address", params.address);
    insertQuery.bindValue(":taxCode", params.taxCode);

    if (insertQuery.exec())
    {
        QMessageBox::information(nullptr, tr("Карта"), tr("Карта успішно створена! Номер вашої карти: ") + params.cardNumber);
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Помилка"), tr("Помилка при створенні картки!"));
        return;
    }
}


void DatabaseManager::updateCardNumbers()
{
    QSqlQuery updateQuery("SELECT Id FROM Cards ORDER BY Id ASC");
    int row = 1;
    while (updateQuery.next())
    {
        int currentId = updateQuery.value(0).toInt();
        QSqlQuery updateNumberQuery;
        updateNumberQuery.prepare("UPDATE Cards SET Id = :row WHERE Id = :currentId");
        updateNumberQuery.bindValue(":row", row);
        updateNumberQuery.bindValue(":currentId", currentId);
        updateNumberQuery.exec();
        ++row;
    }
}

void DatabaseManager::deleteCard(const QString& username)
{
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM Cards WHERE Username = :username");
    deleteQuery.bindValue(":username", username);

    if (deleteQuery.exec())
    {
        QMessageBox::information(nullptr, "Успіх", "Картка успішно видалена!");
        updateCardNumbers();
    }
    else
    {
        QMessageBox::critical(nullptr, "Помилка", "Помилка при видаленні картки!");
    }
}

void DatabaseManager::updateUserLoanStatus(bool canTakeLoan, const QString& username)
{
    QSqlQuery query;
    query.prepare("UPDATE Users SET canTakeLoan = :canTakeLoan WHERE username = :username");
    query.bindValue(":canTakeLoan", canTakeLoan);
    query.bindValue(":username", username);

    if (query.exec())
    {
        qDebug() << "Loan статус оновлено!";
    } else
    {
        qDebug() << "Помилка при оновленні loan статусу:" << query.lastError().text();
    }
}
