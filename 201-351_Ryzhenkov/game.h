#ifndef GAME_H
#define GAME_H
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QDialog>
#include <QLineEdit>

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
    //    QLineEdit* lineEdit;

private slots:
    //    void on_listWidget_itemClicked(QListWidgetItem *item);

    //    void on_tableWidget_itemClicked(QTableWidgetItem *item);


private:
    Ui::game *ui;
    bool eventFilter(QObject* watched, QEvent* event);
    QLineEdit *lineEdit;
};

#endif // GAME_H
