#ifndef FORMPAKAN_H
#define FORMPAKAN_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class FormPakan;
}

class FormPakan : public QWidget
{
    Q_OBJECT

public:
    explicit FormPakan(QWidget *parent = nullptr);
    ~FormPakan();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::FormPakan *ui;
    QSqlDatabase koneksiDB;
};

#endif // FORMPAKAN_H
