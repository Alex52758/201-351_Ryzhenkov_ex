#include "game.h"
#include "ui_game.h"
#include "qlistwidget.h"
#include "QMessageBox"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "string"
#include "jsonModel.h"
#include "mainwindow.h"

game::game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    game::gamefun();
}

game::~game()
{
    delete ui;
}

void game::gamecontrol()
{
    if (var == 3) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Игра закончена");
        QString text = QString::number(sum);
        msgBox.setText(text);
        msgBox.exec();
        ui->tableWidget->setRowCount(0);
        ui->label->setText("");
        var = 0;
        sum = 0;
        randomhislo();
        gamefun(); // происходит сброс игры
    }
}

void game::gamefun()
{
    game::randomhislo();
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            QLineEdit* lineEdit = new QLineEdit();

            for (int s = 0; s < 9; ++s) {
                QByteArray encryptedValue = QByteArray::fromHex(randomNumbersqs[s].toUtf8());
                QString decryptedValue = Crypt::decrypt(encryptedValue, pinCode, pinCode);
                randomNumbers[s] = decryptedValue.toInt();
            }

            QString mass = QString::number(randomNumbers[row * 3 + column]);
            lineEdit->setText(mass);
            ui->tableWidget->setStyleSheet("QLineEdit { border: none }");
            lineEdit->setReadOnly(true);
            lineEdit->setEchoMode(QLineEdit::Password);
            ui->tableWidget->setCellWidget(row, column, lineEdit);
            lineEdit->installEventFilter(this);
        }
    }
}

int game::randomhislo()
{
    const int arraySize = 9;
    std::fill(std::begin(randomNumbers), std::end(randomNumbers), 0);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < arraySize; ++i) {
        int randomNumber = std::rand() % 10000;
        QString randomNum = QString::number(randomNumber);
        QByteArray encryptedValue = Crypt::encrypt(randomNum.toUtf8(), pinCode, pinCode);
        randomNumbersqs[i] = encryptedValue.toHex();
    }

    return 0;
}

bool game::eventFilter(QObject* watched, QEvent* event)
{
    if(event->type() == QEvent::MouseButtonPress) {
        if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(watched)) {
            Q_FOREACH(const QLineEdit* i, findChildren<QLineEdit*>())
                i->disconnect();

            int row = lineEdit->property("row").toInt();
            int column = lineEdit->property("column").toInt();

            if (var != 3) {
                var++;
                for (int i = 0; i < 3; i++)
                    for (int с = 0; с < 3; с++){
                        if (i != row || с != column) {
                            for (int s = 0; s < 9; ++s) {
                                QByteArray encryptedValue = QByteArray::fromHex(randomNumbersqs[s].toUtf8());
                                QString decryptedValue = Crypt::decrypt(encryptedValue, pinCode, pinCode);
                                randomNumbers[s] = decryptedValue.toInt();
                            }
                            QString mass = QString::number(randomNumbers[i * 3 + с]);
                            lineEdit->installEventFilter(this);
                            lineEdit->setReadOnly(true);
                            ui->tableWidget->setStyleSheet("QLineEdit { border: none }");
                            lineEdit = new QLineEdit(mass);
                            lineEdit->setProperty("row", i);
                            lineEdit->setProperty("column", с);
                            lineEdit->setEchoMode(QLineEdit::Password);
                            lineEdit->setText(mass);
                            ui->tableWidget->setCellWidget(i, с, lineEdit);
                        } else {
                            for (int s = 0; s < 9; ++s) {
                                QByteArray encryptedValue = QByteArray::fromHex(randomNumbersqs[s].toUtf8());
                                QString decryptedValue = Crypt::decrypt(encryptedValue, pinCode, pinCode);
                                randomNumbers[s] = decryptedValue.toInt();
                            }
                            ui->tableWidget->setStyleSheet("QLineEdit { border: none }");
                            lineEdit->installEventFilter(this);
                            QLineEdit* lineEdit = new QLineEdit();
                            QString mass = QString::number(randomNumbers[i * 3 + с]);
                            lineEdit->setText(mass);
                            lineEdit->setReadOnly(true);
                            lineEdit->setEchoMode(QLineEdit::Normal);
                            ui->tableWidget->setCellWidget(i, с, lineEdit);
                            game::sum = game::sum + mass.toInt();
                            ui->label->setText(QString::number(game::sum));
                            gamecontrol();
                        }
                    }
            }
        }
    }
    return QObject::eventFilter(watched, event);
}




