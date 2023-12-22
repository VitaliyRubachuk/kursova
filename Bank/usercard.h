#ifndef USERCARD_H
#define USERCARD_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlQuery>

class UserCard : public QDialog
{
    Q_OBJECT

public:
    UserCard(const QString &currentUsername, QWidget *parent = nullptr);
    ~UserCard();

private slots:
    void showCardDetails();
    void getNewCard();
    void deleteCard();

private:
    QString currentUsername;
    QPushButton *cardButton;
    QPushButton *getCardButton;
    QPushButton *deleteCardButton;

    void addCardToDatabase(const QString& name, const QString& pin, const QString& cardNumber, const QString& username);
    QString getCreditAmountForUser(const QString& username);
    bool hasCredits(const QString& username);
};

#endif // USERCARD_H
