#ifndef FORMPRODUKSI_H
#define FORMPRODUKSI_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QShowEvent>
#include <QSqlQueryModel>

namespace Ui {
class FormProduksi;
}

class FormProduksi : public QWidget
{
    Q_OBJECT

public:
    explicit FormProduksi(QWidget *parent = nullptr);
    void loadTabelProduksi();
    void clearFormInput();
    ~FormProduksi();

    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableProduksi_clicked(const QModelIndex &index);

private:
    Ui::FormProduksi *ui;
    QSqlDatabase koneksiDB;
    QSqlQueryModel *tabelModel;
};

#endif // FORMPRODUKSI_H
