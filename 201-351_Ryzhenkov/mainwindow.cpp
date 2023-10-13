#include "mainwindow.h"
#include "QCryptographicHash"
#include "QFile"
#include "QMessageBox"
#include "QString"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
    QString pinCode = ui->Pin->text();




    if ("1111" == pinCode) {  // сравнение расшифрованного текста с введенным пинкодом
        game window;
        window.setModal(true);
        this->close();
        window.exec();
    } else {
        QMessageBox::warning(this, "Authotization", "Pin is incorrect");
    }
}
