#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include "databasemanager.h"

class ManagerWindow : public QDialog
{
    Q_OBJECT

public:
    ManagerWindow(QWidget *parent = nullptr);
    ~ManagerWindow();

private slots:
    bool hasCard(const QString& username);
    void repayCredit();
    void updateCreditTable();
    void showIssueCreditDialog();
    void issueCreditToAccount(const QString& account, const QString& amount);
    bool isAccountExists(const QString& username);
    void applyTextEditStyle(QTextEdit* textEdit);
    void applyButtonStyle(QPushButton* button);
    bool canTakeLoan(const QString& username);
    void showManagerWindow();
private:
    QPushButton *repayCreditButton;
    QTableWidget *creditTable;
    DatabaseManager* databaseManager;
    QPushButton *managerButton;
};

#endif // MANAGERWINDOW_H
