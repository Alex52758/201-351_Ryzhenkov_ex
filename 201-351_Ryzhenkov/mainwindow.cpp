#include "mainwindow.h"
#include "QCryptographicHash"
#include "QFile"
#include "QMessageBox"
#include "QString"
#include "ui_mainwindow.h"
#include "game.h"
#include "crypt.h"
#include "jsonModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

}


MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
    QString pinCode = ui->Pin->text();

    QFile file(JsonModel::kFileName);

    if (!file.exists()) {
        auto encodedPin =
            Crypt::encrypt((pinCode + "\n[]").toUtf8(), pinCode, pinCode);

        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(encodedPin);
        file.close();

        QMessageBox::warning(this, "Pin", "Pin has been created");

        return MainWindow::on_pushButton_clicked();
    }
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QByteArray readedText = file.readAll();
    file.close();

    QString decodedText = Crypt::decrypt(readedText, pinCode, pinCode); // расшифровка пин 2 раз
    QString decodedKey = decodedText.split("\n")[0];

    qInfo() << "Key" << decodedKey;

    if (decodedKey == pinCode) {  // сравнение расшифрованного текста с введенным пинкодом
        game window;
        window.setModal(true);
        this->close();
        window.exec();
    } else {
        QMessageBox::warning(this, "Authotization", "Pin is incorrect");
    }
}

