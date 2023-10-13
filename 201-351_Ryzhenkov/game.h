#ifndef GAME_H
#define GAME_H
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QDialog>
#include <QLineEdit>
#include "jsonModel.h"
#include "crypt.h"

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    ~game();
    void gamefun();
    int randomhislo();
    int randomNumbers[12];
    int sum = 0;
    void gamecontrol();
    int var = 0;
    QListWidget listWidget;
//    QString Url = 0;
//    QString Login = 0;
//    QString Pass = 0;
//    JsonModel::Row rowss = {Url, Login, Pass};
    QString pinCode = "1234";


private slots:

private:
    Ui::game *ui;
    bool eventFilter(QObject* watched, QEvent* event);
    QLineEdit *lineEdit;
};

#endif // GAME_H
