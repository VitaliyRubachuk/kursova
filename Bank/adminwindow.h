#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H
#include <QTextEdit>
#include <QPushButton>

#include <QDialog>
#include <QVBoxLayout>


class AdminWindow : public QDialog
{
    Q_OBJECT
private:
    AdminWindow *adminWindow;

public:
    AdminWindow(QWidget *parent = nullptr);
    void applyButtonStyle(QPushButton* button);
    void applyTextEditStyle(QTextEdit* textEdit);
    void showCredits();
    void showAccounts();
    void clearTable();
    void refreshAccounts();
    void showlUserInfo();
    void showAdditionalUserInfo();
    QTextEdit *accountList;
signals:
    void tableCleared();
};

#endif // ADMINWINDOW_H
