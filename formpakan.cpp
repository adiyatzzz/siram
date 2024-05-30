#include "formpakan.h"
#include "ui_formpakan.h"

FormPakan::FormPakan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormPakan)
{
    ui->setupUi(this);
}

FormPakan::~FormPakan()
{
    delete ui;
}

void FormPakan::on_pushButton_clicked()
{
    QSqlQuery sql(koneksiDB);
    sql.prepare("INSERT INTO pakan (kd_pakan, nama_pakan, jenis_pakan, jml_pakan) VALUE(:kd_pakan, :nama_pakan, :jenis_pakan, :jml_pakan)");
    sql.bindValue(":kd_pakan", ui->kodePakanLineEdit->text());
    sql.bindValue(":nama_pakan", ui->namaPakanLineEdit->text());
    sql.bindValue(":jenis_pakan", ui->jenisPakanLineEdit->text());
    sql.bindValue(":jml_pakan", ui->jumlahPakanLineEdit->text());

    if(sql.exec()){
        qDebug()<<"Data berhasil di simpan";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormPakan::on_pushButton_2_clicked()
{
    QSqlQuery sql(koneksiDB);
    sql.prepare("UPDATE pakan SET nama_pakan=:nama_pakan, jenis_pakan=:jenis_pakan, jml_pakan =:jml_pakan WHERE kd_pakan=:kd_pakan");
    sql.bindValue(":kd_pakan", ui->kodePakanLineEdit->text());
    sql.bindValue(":nama_pakan", ui->namaPakanLineEdit->text());
    sql.bindValue(":jenis_pakan", ui->jenisPakanLineEdit->text());
    sql.bindValue(":jml_pakan", ui->jumlahPakanLineEdit->text());

    if(sql.exec()){
        qDebug()<<"Data berhasil di ubah";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormPakan::on_pushButton_3_clicked()
{
    QSqlQuery sql(koneksiDB);
    sql.prepare("DELETE FROM pakan WHERE kd_pakan=:kd_pakan");
    sql.bindValue(":kd_pakan", ui->kodePakanLineEdit->text());

    if(sql.exec()){
        qDebug()<<"Data berhasil di hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}

