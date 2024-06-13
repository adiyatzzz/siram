#ifndef FORMPAKAN_H
#define FORMPAKAN_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <formchecker.h>

namespace Ui {
class FormPakan;
}

class FormPakan : public QWidget
{
    Q_OBJECT

public:
    explicit FormPakan(QWidget *parent = nullptr);
    void loadTabelPakan();
    void clearFormInput();
    ~FormPakan();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tablePakan_clicked(const QModelIndex &index);

private:
    Ui::FormPakan *ui;
    QSqlDatabase koneksiDB;
    QSqlQueryModel *tabelModel;
    FormChecker *formChecker;
};

#endif // FORMPAKAN_H
