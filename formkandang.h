#ifndef FORMKANDANG_H
#define FORMKANDANG_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class FormKandang;
}

class FormKandang : public QWidget
{
    Q_OBJECT

public:
    explicit FormKandang(QWidget *parent = nullptr);
    ~FormKandang();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::FormKandang *ui;
    QSqlDatabase koneksiDB;
};

#endif // FORMKANDANG_H
