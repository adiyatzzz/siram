#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <formkandang.h>
#include <formpakan.h>
#include <formpopulasi.h>
#include <formproduksi.h>
#include <formjadwal.h>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    FormKandang *formKandang;
    FormPakan *formPakan;
    FormPopulasi *formPopulasi;
    FormProduksi *formProduksi;
    FormJadwal *formJadwal;
    QSqlDatabase koneksiDB;
};
#endif // MAINWINDOW_H
