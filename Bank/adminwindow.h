#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include <QVBoxLayout>


class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    AdminWindow(QWidget *parent = nullptr);

    void clearTable();
    void showCredits();

signals:
    void tableCleared();
};

#endif // ADMINWINDOW_H
