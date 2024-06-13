#ifndef FORMKANDANG_H
#define FORMKANDANG_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <formchecker.h>

namespace Ui {
class FormKandang;
}

class FormKandang : public QWidget
{
    Q_OBJECT

public:
    explicit FormKandang(QWidget *parent = nullptr);
    void loadTabelKandang();
    void clearFormInput();
    ~FormKandang();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableKandang_clicked(const QModelIndex &index);

private:
    Ui::FormKandang *ui;
    QSqlDatabase koneksiDB;
    QSqlQueryModel *tabelModel;
    FormChecker *formChecker;
};

#endif // FORMKANDANG_H
