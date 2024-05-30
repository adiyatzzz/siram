#ifndef FORMJADWAL_H
#define FORMJADWAL_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QShowEvent>

namespace Ui {
class FormJadwal;
}

class FormJadwal : public QWidget
{
    Q_OBJECT

public:
    explicit FormJadwal(QWidget *parent = nullptr);
    ~FormJadwal();

    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::FormJadwal *ui;
    QSqlDatabase koneksiDB;
};

#endif // FORMJADWAL_H
