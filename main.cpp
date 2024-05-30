#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase koneksiDB = QSqlDatabase::addDatabase("QODBC");
    koneksiDB.setDatabaseName("dsn_siram");
    koneksiDB.setUserName("root");
    koneksiDB.setPassword("");

    if(koneksiDB.open()){
        qDebug()<<"Database terkoneksi";
    }else{
        qDebug()<<koneksiDB.lastError().text();
    }
    MainWindow w;
    w.show();
    return a.exec();
}
