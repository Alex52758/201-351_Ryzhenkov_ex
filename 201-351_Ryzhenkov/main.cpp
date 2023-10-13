#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <windows.h>
#include <winbase.h>
#include <sstream>
#include <Tlhelp32.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <QApplication>
#include <fstream>
#include "QCryptographicHash"
#include "QDebug"
#include "QMessageBox"
#include "QProcess"
#include "QString"
#include "mainwindow.h"


typedef unsigned long long QWORD;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;
    w.show();
return a.exec(), system("taskkill /im /f");
}
