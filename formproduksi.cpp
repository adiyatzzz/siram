#include "formproduksi.h"
#include "ui_formproduksi.h"

FormProduksi::FormProduksi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormProduksi)
{
    ui->setupUi(this);
}

FormProduksi::~FormProduksi()
{
    delete ui;
}

void FormProduksi::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    ui->iDPopulasiComboBox->clear();
    QSqlQuery sql(koneksiDB);
    sql.prepare("SELECT * FROM populasi");
    sql.exec();
    while(sql.next()){
        QString a = sql.value(sql.record().indexOf("id_populasi")).toString();
        QString b = sql.value(sql.record().indexOf("tgl_populasi")).toString();
        QString c = sql.value(sql.record().indexOf("jml_hidup")).toString();
        QString n = a+"/"+b+"/"+c;
        ui->iDPopulasiComboBox->addItem(n);
    }
}

void FormProduksi::on_pushButton_clicked()
{
    QStringList populasiData = ui->iDPopulasiComboBox->currentText().split("/");
    QString id_populasi = populasiData[0];
    int jmlUtuh = ui->jumlahUtuhLineEdit->text().toInt();
    int jmlRetak = ui->jumlahRetakLineEdit->text().toInt();
    int total = jmlUtuh + jmlRetak;

    QSqlQuery sql(koneksiDB);
    sql.prepare("INSERT INTO produksi (id_produksi, tgl_produksi, jml_utuh, jml_retak, total, id_populasi) VALUE (:id_produksi, :tgl_produksi, :jml_utuh, :jml_retak, :total, :id_populasi)");
    sql.bindValue(":id_produksi", ui->iDProduksiLineEdit->text());
    sql.bindValue(":tgl_produksi", ui->tanggalProduksiDateEdit->date());
    sql.bindValue(":jml_utuh", jmlUtuh);
    sql.bindValue(":jml_retak", jmlRetak);
    sql.bindValue(":total", total);
    sql.bindValue(":id_populasi", id_populasi);

    ui->totalLineEdit->setText(QString::number(total));

    if(sql.exec()){
        qDebug()<<"Data berhasil di simpan";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormProduksi::on_pushButton_2_clicked()
{
    QStringList populasiData = ui->iDPopulasiComboBox->currentText().split("/");
    QString id_populasi = populasiData[0];
    int jmlUtuh = ui->jumlahUtuhLineEdit->text().toInt();
    int jmlRetak = ui->jumlahRetakLineEdit->text().toInt();
    int total = jmlUtuh + jmlRetak;

    QSqlQuery sql(koneksiDB);
    sql.prepare("UPDATE produksi SET tgl_produksi=:tgl_produksi, jml_utuh=:jml_utuh, jml_retak=:jml_retak, total=:total, id_populasi=:id_populasi WHERE id_produksi=:id_produksi");
    sql.bindValue(":id_produksi", ui->iDProduksiLineEdit->text());
    sql.bindValue(":tgl_produksi", ui->tanggalProduksiDateEdit->date());
    sql.bindValue(":jml_utuh", jmlUtuh);
    sql.bindValue(":jml_retak", jmlRetak);
    sql.bindValue(":total", total);
    sql.bindValue(":id_populasi", id_populasi);

    ui->totalLineEdit->setText(QString::number(total));

    if(sql.exec()){
        qDebug()<<"Data berhasil di ubah";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormProduksi::on_pushButton_3_clicked()
{
    QSqlQuery sql(koneksiDB);
    sql.prepare("DELETE FROM produksi WHERE id_produksi=:id_produksi");
    sql.bindValue(":id_produksi", ui->iDProduksiLineEdit->text());

    if(sql.exec()){
        qDebug()<<"Data berhasil di hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}

