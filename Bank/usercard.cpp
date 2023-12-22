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
#include <QCryptographicHash>
#include "userwindowmanager.h"
#include "usercardmanager.h"
#include "databasemanager.h"
#include <QApplication>
#include <QDir>
UserCardManager::UserCardManager(QObject *parent) : QObject(parent) {}

void UserCardManager::showUserCards(const QString& username)
{
    currentUsername = username;

    cardDialog = new QDialog();
    QVBoxLayout *layout = new QVBoxLayout(cardDialog);
    cardDialog->setWindowTitle("Карта банку");
    cardDialog->setFixedSize(300, 200);

    cardButton = new QPushButton("Карта", cardDialog);
    getCardButton = new QPushButton("Отримати карту", cardDialog);
    deleteCardButton = new QPushButton("Видалити карту", cardDialog);

    layout->addWidget(cardButton);
    layout->addWidget(getCardButton);
    layout->addWidget(deleteCardButton);

    QSqlQuery query;
    query.prepare("SELECT CardNumber FROM Cards WHERE Username = :username");
    query.bindValue(":username", currentUsername);
    query.exec();

    if (!query.next())
    {
        deleteCardButton->setEnabled(false);
        cardButton->setEnabled(false);
    }
    else
    {
        deleteCardButton->setEnabled(true);
        cardButton->setEnabled(true);
    }

    if (cardButton->isEnabled())
    {
        query.prepare("SELECT CardNumber FROM Cards WHERE Username = :username");
        query.bindValue(":username", currentUsername);
        query.exec();
        if (query.next())
        {
            getCardButton->setEnabled(false);
        }
    }

    cardButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");
    getCardButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");
    deleteCardButton->setStyleSheet("QPushButton {""background-color: #A0CFE8;""border-style: outset;""border-width: 2px;""border-radius: 10px;""border-color: #80AEBD;""font: bold 14px;""min-width: 10em;""padding: 6px;""}""QPushButton:hover {""background-color: #C7E4F2;""}""QPushButton:pressed {""background-color: #85B7D9;""}");

    connect(cardButton, &QPushButton::clicked, this, &UserCardManager::cardButtonClicked);

    connect(getCardButton, &QPushButton::clicked, this, &UserCardManager::getCardButtonClicked);

    connect(deleteCardButton, &QPushButton::clicked, this, &UserCardManager::deleteCardButtonClicked);

    QPalette pal = cardDialog->palette();
    pal.setColor(QPalette::Window, QColor(173, 216, 230));
    cardDialog->setAutoFillBackground(true);
    cardDialog->setPalette(pal);

    cardDialog->exec();
}


bool UserCardManager::checkPin(const QString& enteredPin, const QString& storedPin)
{
    QByteArray hashedEnteredPin = QCryptographicHash::hash(enteredPin.toUtf8(), QCryptographicHash::Sha256);

    return (hashedEnteredPin.toHex() == storedPin);
}

void UserCardManager::cardButtonClicked()
{
        bool ok;
        QString pin = QInputDialog::getText(nullptr, tr("Введіть пін-код"), tr("Пін-код:"), QLineEdit::Password, QString(), &ok);

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

            while (query.next())
            {
                storedPin = query.value(0).toString();
                cardNumber = query.value(1).toString();
                cardName = query.value(2).toString();
            }

            if (checkPin(pin, storedPin))
            {
                creditAmount = userWindowManager->getCreditAmountForUser(currentUsername);


                QDialog *cardDetailsDialog = new QDialog(cardDialog);

                QVBoxLayout *layout = new QVBoxLayout(cardDetailsDialog);

                QString styledCardNumber = "<font size='5'>" + cardNumber + "</font>";
                QLabel *cardNumberLabel = new QLabel("<font size='5'>Номер картки: </font>" + styledCardNumber);
                cardNumberLabel->setAlignment(Qt::AlignCenter);

                QStringList nameParts = cardName.split(" ");
                QString lastName = nameParts[0];
                QString firstName = (nameParts.size() > 1) ? nameParts[1] : "";

                QString styledCardName = "<font size='5'>" + lastName + " " + firstName + "</font>";
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

                QString imagePath = QDir(QCoreApplication::applicationDirPath()).filePath("Картинки/13.png");
                QLabel *imageLabel = new QLabel(cardDetailsDialog);
                QPixmap image(imagePath);
                imageLabel->setPixmap(image);
                imageLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
                layout->addWidget(imageLabel);

                cardDetailsDialog->setLayout(layout);

                QPalette pal = cardDetailsDialog->palette();
                pal.setColor(QPalette::Window, QColor(173, 216, 230));
                cardDetailsDialog->setAutoFillBackground(true);
                cardDetailsDialog->setPalette(pal);

                cardDetailsDialog->exec();
            }
            else
            {
                QMessageBox::warning(nullptr, tr("Помилка"), tr("Неправильний пін-код!"));
            }
        }
}


void UserCardManager::getCardButtonClicked()
{
        QSqlQuery query;
        query.prepare("SELECT CardNumber FROM Cards WHERE Username = :username");
        query.bindValue(":username", currentUsername);
        query.exec();

        if (query.next())
        {
            QMessageBox::information(cardDialog, tr("Помилка"), tr("У вас вже є карта!"));
        }
        else
        {
            QDialog *getCardDialog = new QDialog(cardDialog);
            getCardDialog->setWindowTitle("Отримати карту");
            getCardDialog->setFixedSize(800, 500);

            QPalette pal = getCardDialog->palette();
            pal.setColor(QPalette::Window, QColor(173, 216, 230));
            getCardDialog->setAutoFillBackground(true);
            getCardDialog->setPalette(pal);

            QVBoxLayout *getCardLayout = new QVBoxLayout(getCardDialog);

            QLabel *titleLabel = new QLabel("Отримати нову карту", getCardDialog);
            titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #004080;");
            titleLabel->setAlignment(Qt::AlignCenter);


            QLineEdit *nameLineEdit = new QLineEdit(getCardDialog);
            QLineEdit *pinLineEdit = new QLineEdit(getCardDialog);
            QLineEdit *cityLineEdit = new QLineEdit(getCardDialog);
            QLineEdit *addressLineEdit = new QLineEdit(getCardDialog);
            QLineEdit *taxCodeLineEdit = new QLineEdit(getCardDialog);
            pinLineEdit->setEchoMode(QLineEdit::Password);

            QPushButton *createCardButton = new QPushButton("Створити карту", getCardDialog);

            getCardLayout->addWidget(titleLabel);
            getCardLayout->addWidget(new QLabel("Прізвище та ім'я:", getCardDialog));
            getCardLayout->addWidget(nameLineEdit);
            getCardLayout->addWidget(new QLabel("Пін-код:", getCardDialog));
            getCardLayout->addWidget(pinLineEdit);

            getCardLayout->addWidget(new QLabel("Місто:", getCardDialog));
            getCardLayout->addWidget(cityLineEdit);
            getCardLayout->addWidget(new QLabel("Адрес проживання:", getCardDialog));
            getCardLayout->addWidget(addressLineEdit);
            getCardLayout->addWidget(new QLabel("Код П.П.:", getCardDialog));
            getCardLayout->addWidget(taxCodeLineEdit);
            getCardLayout->addWidget(createCardButton);
            // Стилізація кнопок і полів вводу
            titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #004080; margin-bottom: 10px;");
            nameLineEdit->setStyleSheet("font-size: 16px; padding: 8px; margin-bottom: 14px;");
            pinLineEdit->setStyleSheet("font-size: 16px; padding: 8px; margin-bottom: 14px;");

            cityLineEdit->setStyleSheet("font-size: 16px; padding: 8px; margin-bottom: 14px;");
            addressLineEdit->setStyleSheet("font-size: 16px; padding: 8px; margin-bottom: 14px;");
            taxCodeLineEdit->setStyleSheet("font-size: 16px; padding: 8px; margin-bottom: 14px;");
            createCardButton->setStyleSheet("QPushButton { background-color: #008CBA; color: white; border: none; padding: 10px 20px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; border-radius: 5px; } QPushButton:hover { background-color: #005780; }"); // Голубий фон кнопки, темно-голубий при наведенні

            connect(createCardButton, &QPushButton::clicked, [=]()
            {
                if (nameLineEdit->text().isEmpty() || cityLineEdit->text().isEmpty() || addressLineEdit->text().isEmpty() || taxCodeLineEdit->text().isEmpty())
                {
                    QMessageBox::warning(getCardDialog, tr("Помилка"), tr("Будь ласка, заповніть всі обов'язкові поля!"));
                    return;
                }

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, 9999);

                QString cardNumber = QString::number(dis(gen)).rightJustified(4, '0');
                QLineEdit *lastNameLineEdit = new QLineEdit(getCardDialog);
                DatabaseManager::DatabaseParams params;
                params.lastName = lastNameLineEdit->text();
                params.firstName = nameLineEdit->text();
                params.pin = pinLineEdit->text();
                params.cardNumber = cardNumber; // це залежить від вашої логіки отримання номеру картки
                params.username = currentUsername;
                params.city = cityLineEdit->text();
                params.address = addressLineEdit->text();
                params.taxCode = taxCodeLineEdit->text();
                databaseManagerInstance.addCardToDatabase(params);
                cardDialog->close();
                getCardDialog->close();
                showUserCards(currentUsername);
                getCardButton->setEnabled(false);
            });
            cardDialog->close();
            getCardDialog->exec();
        }
}

void UserCardManager::deleteCardButtonClicked()
{
    if (userWindowManager->hasCredits(currentUsername))
    {
        QMessageBox::warning(cardDialog, "Карта", "У вас є кредити. Спочатку оплатіть їх перед видаленням картки.");
        return;
    }

    QDialog *pinDialog = new QDialog(cardDialog);
    pinDialog->setWindowTitle("Введіть пін-код");
    pinDialog->setFixedSize(400, 200);

    QLineEdit *pinLineEdit = new QLineEdit(pinDialog);
    pinLineEdit->setEchoMode(QLineEdit::Password);

    QPushButton *confirmButton = new QPushButton("Підтвердити", pinDialog);

    QLabel *titleLabel1 = new QLabel("Введіть пін-код для підтвердження видалення", pinDialog);
    titleLabel1->setStyleSheet("font-size: 16px; font-weight: bold; color: #004080;");

    QVBoxLayout *pinLayout = new QVBoxLayout(pinDialog);
    pinLayout->addWidget(titleLabel1);
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
            QString storedPinHash = query.value(0).toString();
            if (checkPin(enteredPin, storedPinHash))
            {
                databaseManagerInstance.deleteCard(currentUsername);
                pinDialog->close();
                cardDialog->close();
                showUserCards(currentUsername);
            }
            else
            {
                QMessageBox::warning(pinDialog, tr("Помилка"), tr("Неправильний пін-код!"));
            }
        }
    });

    pinDialog->exec();
}


