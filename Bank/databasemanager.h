#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    struct DatabaseParams
    {
        QString lastName;
        QString firstName;
        QString pin;
        QString cardNumber;
        QString username;
        QString city;
        QString address;
        QString taxCode;
    };
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();
    bool createConnection();
    void createUserTable();
    void createCreditTable();
    void createCardsTable();
    void clearTable();
    void updateCreditSequence();
    void addCardToDatabase(const DatabaseParams& params);
    void updateCardNumbers();
    void deleteCard(const QString& username);
    void updateUserLoanStatus(bool canTakeLoan, const QString& username);
private:
    QSqlDatabase db;
    int pinValue;

signals:
    void tablesCleared();

};

#endif // DATABASEMANAGER_H
