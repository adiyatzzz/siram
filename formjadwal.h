#ifndef FORMJADWAL_H
#define FORMJADWAL_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QShowEvent>
#include <QSqlQueryModel>

namespace Ui {
class FormJadwal;
}

class FormJadwal : public QWidget
{
    Q_OBJECT

public:
    explicit FormJadwal(QWidget *parent = nullptr);
    void loadTabelJadwal();
    void clearFormInput();
    ~FormJadwal();

    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableJadwal_clicked(const QModelIndex &index);

private:
    Ui::FormJadwal *ui;
    QSqlDatabase koneksiDB;
    QSqlQueryModel *tabelModel;
};

#endif // FORMJADWAL_H
