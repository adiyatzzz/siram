#ifndef FORMPOPULASI_H
#define FORMPOPULASI_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QShowEvent>
#include <QSqlQueryModel>

namespace Ui {
class FormPopulasi;
}

class FormPopulasi : public QWidget
{
    Q_OBJECT

public:
    explicit FormPopulasi(QWidget *parent = nullptr);
    void loadTabelPopulasi();
    void clearFormInput();
    ~FormPopulasi();

    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tablePopulasi_clicked(const QModelIndex &index);

private:
    Ui::FormPopulasi *ui;
    QSqlDatabase koneksiDB;
    QSqlQueryModel *tabelModel;
};

#endif // FORMPOPULASI_H
