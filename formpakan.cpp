#include "formpakan.h"
#include "ui_formpakan.h"

FormPakan::FormPakan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormPakan)
{
    ui->setupUi(this);
    loadTabelPakan();
}

void FormPakan::loadTabelPakan()
{
    // set table
    tabelModel = new QSqlQueryModel(this);
    tabelModel->setQuery("SELECT * FROM pakan ORDER BY kd_pakan ASC");
    tabelModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Kode Pakan"));
    tabelModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Nama Pakan"));
    tabelModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Jenis Pakan"));
    tabelModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Jumlah Pakan (Kg)"));

    ui->tablePakan->setModel(tabelModel);
    ui->tablePakan->setColumnWidth(0, 100);
    ui->tablePakan->setColumnWidth(1, 150);
    ui->tablePakan->setColumnWidth(2, 100);
    ui->tablePakan->setColumnWidth(3, 100);
    ui->tablePakan->show();
}

void FormPakan::clearFormInput()
{
    ui->kodePakanLineEdit->setText("");
    ui->namaPakanLineEdit->setText("");
    ui->jenisPakanLineEdit->setText("");
    ui->jumlahPakanLineEdit->setText("");
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

    loadTabelPakan();
    clearFormInput();
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

    loadTabelPakan();
    clearFormInput();
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

    loadTabelPakan();
    clearFormInput();
}


void FormPakan::on_tablePakan_clicked(const QModelIndex &index)
{
    int rowidx = ui->tablePakan->selectionModel()->currentIndex().row();
    ui->kodePakanLineEdit->setText(tabelModel->index(rowidx, 0).data().toString());
    ui->namaPakanLineEdit->setText(tabelModel->index(rowidx, 1).data().toString());
    ui->jenisPakanLineEdit->setText(tabelModel->index(rowidx, 2).data().toString());
    ui->jumlahPakanLineEdit->setText(tabelModel->index(rowidx, 3).data().toString());
}

