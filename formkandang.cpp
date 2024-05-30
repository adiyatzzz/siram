#include "formkandang.h"
#include "ui_formkandang.h"

FormKandang::FormKandang(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormKandang)
{
    ui->setupUi(this);

}

FormKandang::~FormKandang()
{
    delete ui;
}

void FormKandang::on_pushButton_clicked()
{
    QSqlQuery sql(koneksiDB);
    sql.prepare("INSERT INTO kandang (kd_kandang, nama_kandang, kapasitas) VALUE(:kd_kandang, :nama_kandang, :kapasitas)");
    sql.bindValue(":kd_kandang", ui->kodeKandangLineEdit->text());
    sql.bindValue(":nama_kandang", ui->namaKandangLineEdit->text());
    sql.bindValue(":kapasitas", ui->kapasitasLineEdit->text());

    if(sql.exec()){
        qDebug()<<"Data berhasil di simpan";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormKandang::on_pushButton_2_clicked()
{
    QSqlQuery sql(koneksiDB);
    sql.prepare("UPDATE kandang SET nama_kandang=:nama_kandang, kapasitas=:kapasitas WHERE kd_kandang=:kd_kandang");
    sql.bindValue(":kd_kandang", ui->kodeKandangLineEdit->text());
    sql.bindValue(":nama_kandang", ui->namaKandangLineEdit->text());
    sql.bindValue(":kapasitas", ui->kapasitasLineEdit->text());

    if(sql.exec()){
        qDebug()<<"Data berhasil di ubah";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormKandang::on_pushButton_3_clicked()
{
    QSqlQuery sql(koneksiDB);
    sql.prepare("DELETE FROM kandang WHERE kd_kandang=:kd_kandang");
    sql.bindValue(":kd_kandang", ui->kodeKandangLineEdit->text());

    if(sql.exec()){
        qDebug()<<"Data berhasil di hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}

