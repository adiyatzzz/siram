#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // instance form
    formKandang = new FormKandang;
    formPakan = new FormPakan;
    formPopulasi = new FormPopulasi;
    formProduksi = new FormProduksi;
    formJadwal = new FormJadwal;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    formKandang->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    formPakan->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    formPopulasi->show();
}


void MainWindow::on_pushButton_5_clicked()
{
    formProduksi->show();
}


void MainWindow::on_pushButton_clicked()
{
    formJadwal->show();
}

