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
#include "managerwindow.h"
#include "userwindowmanager.h"
#include <QApplication>
#include <QDir>

Bank::Bank(QWidget *parent) : QMainWindow(parent)
{

    userWindowManager = new UserWindowManager(this);
    db = new DatabaseManager(this);
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

    loginButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");

    registerButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");

    showPasswordButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");

    usernameEdit->setStyleSheet("QLineEdit:focus {""border: 2px solid #6495ED;""}""QLineEdit:hover {""background-color: #F0F8FF;""}""QLineEdit:enabled {""color: black;""font-weight: bold;""}");

    passwordEdit->setStyleSheet("QLineEdit:focus {""border: 2px solid #6495ED;""}""QLineEdit:hover {""background-color: #F0F8FF;""}""QLineEdit:enabled {""color: black;""font-weight: bold;""}");

    connect(loginButton, SIGNAL(clicked()), this, SLOT(loginClicked()));
    connect(registerButton, SIGNAL(clicked()), this, SLOT(registerClicked()));
    connect(showPasswordButton, &QPushButton::clicked, this, &Bank::togglePasswordVisibility);

    if (!db->createConnection())
    {
        QMessageBox::critical(this, "Помилка", "Помилка при підключенні до бази даних");
    }
    createUserTable();
    createCreditTable();
    createCardsTable();

    QPalette pal = centralWidget->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230));
    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(pal);

    QString imagePath = QDir(QCoreApplication::applicationDirPath()).filePath("Картинки/1221.png");
    QLabel *backgroundLabel = new QLabel(centralWidget);
    QPixmap backgroundImage(imagePath);
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
    delete db;
}




void Bank::togglePasswordVisibility()
{
    passwordEdit->setEchoMode(passwordEdit->echoMode() == QLineEdit::Password ? QLineEdit::Normal : QLineEdit::Password);
}

void Bank::createUserTable()
{
    db->createUserTable();
}

void Bank::createCreditTable()
{
    db->createCreditTable();
}

void Bank::createCardsTable()
{
    db->createCardsTable();
}

void Bank::clearTable()
{
    db->clearTable();
}


void Bank::loginClicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next())
    {
        QString storedPassword = query.value("password").toString();
        QString role = query.value("role").toString();

        QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();
        QString hashedPasswordStr = QString::fromLatin1(hashedPassword);

        if (storedPassword == hashedPasswordStr)
        {
            if (role == "manager")
            {
                ManagerWindow *managerWindow = new ManagerWindow(this);
                managerWindow->exec();
                usernameEdit->clear();
                passwordEdit->clear();
                return;
            }
            if (role == "admin")
            {
                AdminWindow *adminWindow = new AdminWindow(this);
                connect(adminWindow, &AdminWindow::tableCleared, this, &Bank::clearTable);
                adminWindow->exec();
                usernameEdit->clear();
                passwordEdit->clear();
                return;
            }

            userWindowManager->showUserWindow(username);
            usernameEdit->clear();
            passwordEdit->clear();
            return;
        }
    }

    QMessageBox::warning(this, "Логін", "Неправильний логін чи пароль");
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

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex();
    QString hashedPasswordStr = QString::fromLatin1(hashedPassword);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString creationDate = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    QSqlQuery query;
    query.prepare("INSERT INTO Users (username, password, role, CreationDate) VALUES (:username, :password, :role, :creationDate)");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPasswordStr);
    query.bindValue(":role", "user");
    query.bindValue(":creationDate", creationDate);

    if (query.exec())
    {
        QMessageBox::information(this, "Реєстрація", "Аккаунт успішно створено!");
        usernameEdit->clear();
        passwordEdit->clear();
    } else {
        QMessageBox::critical(this, "Реєстрація", "Помилка при створенні аккаунта!");
    }
}







