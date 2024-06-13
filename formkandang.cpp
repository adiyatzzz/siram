#include "formkandang.h"
#include "ui_formkandang.h"

FormKandang::FormKandang(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormKandang)
{
    ui->setupUi(this);
    loadTabelKandang();
}

void FormKandang::loadTabelKandang()
{
    // set table
    tabelModel = new QSqlQueryModel(this);
    tabelModel->setQuery("SELECT * FROM kandang ORDER BY kd_kandang ASC");
    tabelModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Kode Kandang"));
    tabelModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Nama Kandang"));
    tabelModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Kapasitas"));

    ui->tableKandang->setModel(tabelModel);
    ui->tableKandang->setColumnWidth(0, 100);
    ui->tableKandang->setColumnWidth(1, 150);
    ui->tableKandang->setColumnWidth(2, 100);
    ui->tableKandang->show();
}

void FormKandang::clearFormInput()
{
    ui->kodeKandangLineEdit->setText("");
    ui->namaKandangLineEdit->setText("");
    ui->kapasitasLineEdit->setText("");
}

FormKandang::~FormKandang()
{
    delete ui;
}

void FormKandang::on_pushButton_clicked()
{

    QSqlQuery sql(koneksiDB);
    if(formChecker->isFieldEmpty(this, ui->kodeKandangLineEdit, "Kode Kandang Belum Diisi") ||
        formChecker->isFieldEmpty(this, ui->namaKandangLineEdit, "Nama Kandang Belum Diisi") ||
        formChecker->isFieldEmpty(this, ui->kapasitasLineEdit, "Kapasitas Kandang Belum Diisi") ){
        return;
    }

    sql.prepare("SELECT * FROM kandang WHERE kd_kandang = '"+ ui->kodeKandangLineEdit->text() + "'");
    sql.exec();

    if (sql.next()) {
        QMessageBox::information(this, "Warning", "Kode Kandang sudah digunakan");
        ui->kodeKandangLineEdit->setText(sql.value(0).toString());
        ui->namaKandangLineEdit->setText(sql.value(1).toString());
        ui->kapasitasLineEdit->setText(sql.value(2).toString());
    } else {
        sql.prepare("INSERT INTO kandang (kd_kandang, nama_kandang, kapasitas) VALUE(:kd_kandang, :nama_kandang, :kapasitas)");
        sql.bindValue(":kd_kandang", ui->kodeKandangLineEdit->text());
        sql.bindValue(":nama_kandang", ui->namaKandangLineEdit->text());
        sql.bindValue(":kapasitas", ui->kapasitasLineEdit->text());

        if(sql.exec()){
            qDebug()<<"Data berhasil di simpan";
        }else{
            qDebug()<<sql.lastError().text();
        }

        loadTabelKandang();
        clearFormInput();
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
    loadTabelKandang();
    clearFormInput();
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
    loadTabelKandang();
    clearFormInput();
}

void FormKandang::on_tableKandang_clicked(const QModelIndex &index)
{
    int rowidx = ui->tableKandang->selectionModel()->currentIndex().row();
    ui->kodeKandangLineEdit->setText(tabelModel->index(rowidx, 0).data().toString());
    ui->namaKandangLineEdit->setText(tabelModel->index(rowidx, 1).data().toString());
    ui->kapasitasLineEdit->setText(tabelModel->index(rowidx, 2).data().toString());
}


