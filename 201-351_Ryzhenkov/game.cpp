#include "game.h"
#include "ui_game.h"
#include "qlistwidget.h""
#include "QMessageBox"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>



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
    if (var == 4) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Игра закончена");
        QMessageBox::warning(this, "Игра закончена", QString::number(sum));
        QString text = QString::number(sum);
        msgBox.setText(text);
        msgBox.exec();
        ui->tableWidget->setRowCount(0);
        ui->label->setText("");
        var =0;
        randomhislo();
        gamefun();//происходит сброс игры
    }
}
void game::gamefun() //заполнение
{

    game::randomhislo(); // запуск рандомайзера
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(3);

    ui->tableWidget->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
//    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    // Разрешаем выделение построчно
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок

    // Растягиваем последнюю колонку на всё доступное пространство
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 0
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            QLineEdit* lineEdit = new QLineEdit();
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



int game::randomhislo() { // делате рандом числа от 0000 до 9999 и в начале их обнуляет
    const int arraySize = 9; // Размер массива
    std::fill(std::begin(randomNumbers), std::end(randomNumbers), 0); // Обнуление всех элементов
    // Инициализация генератора случайных чисел с использованием текущего времени
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // Генерируем случайные числа и записываем их в массив
    for (int i = 0; i < arraySize; ++i) {
        int randomNumber = std::rand() % 10000;
        randomNumbers[i] = randomNumber;
        std::cout << randomNumbers[i];
    }
    // Выводим сгенерированные числа с ведущими нулями
    std::cout << "Случайные числа: ";
    for (int i = 0; i < arraySize; ++i) {
        // Преобразуем число в строку и добавляем ведущие нули
        std::string formattedNumber = std::to_string(randomNumbers[i]);
        while (formattedNumber.length() < 4) {
            formattedNumber = "0" + formattedNumber;
        }
        std::cout << formattedNumber << " ";
    }
    std::cout << std::endl;
    return 0;
}

//функция события qlineedit

bool game::eventFilter(QObject* watched, QEvent* event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(watched))
        {
            Q_FOREACH(const QLineEdit* i, findChildren<QLineEdit*>())
                i->disconnect();

            int row = lineEdit->property("row").toInt();
            int column = lineEdit->property("column").toInt();


            if (var != 3) { var++;

                for (int i = 0; i < 3; i++)
                    for (int с = 0; с < 3; с++){
                {
                    if (i != row || с != column) {
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
                    }
                    else {
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
                    }}
                }
            }
        }
    }
    return QObject::eventFilter(watched, event);
}










