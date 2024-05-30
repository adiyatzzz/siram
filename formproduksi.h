#ifndef FORMPRODUKSI_H
#define FORMPRODUKSI_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QShowEvent>

namespace Ui {
class FormProduksi;
}

class FormProduksi : public QWidget
{
    Q_OBJECT

public:
    explicit FormProduksi(QWidget *parent = nullptr);
    ~FormProduksi();

    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::FormProduksi *ui;
    QSqlDatabase koneksiDB;
};

#endif // FORMPRODUKSI_H
