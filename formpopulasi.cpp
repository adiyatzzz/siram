#include "formpopulasi.h"
#include "ui_formpopulasi.h"

FormPopulasi::FormPopulasi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormPopulasi)
{
    ui->setupUi(this);


}

FormPopulasi::~FormPopulasi()
{
    delete ui;
}

void FormPopulasi::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    ui->kodeKandangComboBox->clear();
    QSqlQuery sql(koneksiDB);
    sql.prepare("SELECT * FROM kandang");
    sql.exec();
    while(sql.next()){
        QString a = sql.value(sql.record().indexOf("kd_kandang")).toString();
        QString b = sql.value(sql.record().indexOf("nama_kandang")).toString();
        QString c = sql.value(sql.record().indexOf("kapasitas")).toString();
        QString n = a+"/"+b+"/"+c;
        ui->kodeKandangComboBox->addItem(n);
    }
}


void FormPopulasi::on_pushButton_clicked()
{
    QStringList kandangData = ui->kodeKandangComboBox->currentText().split("/");
    QString kd_kandang = kandangData[0];
    int kapasitas = kandangData[2].toInt();
    int jmlMati = ui->jumlahMatiLineEdit->text().toInt();
    int jmlHidup = ui->jumlahHidupLineEdit->text().toInt();
    int hitungSisa = kapasitas - jmlHidup;
    if(hitungSisa == 0){
        jmlMati = 0;
        ui->jumlahMatiLineEdit->setText(QString::number(jmlMati));
    }


    QSqlQuery sql(koneksiDB);
    sql.prepare("INSERT INTO populasi (id_populasi, tgl_populasi, jml_mati, jml_hidup, sisa, kd_kandang) VALUE(:id_populasi, :tgl_populasi, :jml_mati, :jml_hidup, :sisa, :kd_kandang)");
    sql.bindValue(":id_populasi", ui->idPopulasiLineEdit->text());
    sql.bindValue(":tgl_populasi", ui->tanggalPopulasiDateEdit->date());
    sql.bindValue(":jml_mati", jmlMati);
    sql.bindValue(":jml_hidup", jmlHidup);
    sql.bindValue(":sisa", hitungSisa);
    sql.bindValue(":kd_kandang", kd_kandang);

    ui->sisaLineEdit->setText(QString::number(hitungSisa));

    if(sql.exec()){
        qDebug()<<"Data berhasil di simpan";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormPopulasi::on_pushButton_2_clicked()
{
    QStringList kandangData = ui->kodeKandangComboBox->currentText().split("/");
    QString kd_kandang = kandangData[0];
    int kapasitas = kandangData[2].toInt();
    int jmlMati = ui->jumlahMatiLineEdit->text().toInt();
    int jmlHidup = ui->jumlahHidupLineEdit->text().toInt();
    int hitungSisa = kapasitas - jmlHidup;
    if(hitungSisa == 0){
        jmlMati = 0;
        ui->jumlahMatiLineEdit->setText(QString::number(jmlMati));
    }

    QSqlQuery sql(koneksiDB);
    sql.prepare("UPDATE populasi SET tgl_populasi=:tgl_populasi, jml_mati=:jml_mati, jml_hidup=:jml_hidup, sisa=:sisa, kd_kandang=:kd_kandang WHERE id_populasi=:id_populasi");
    sql.bindValue(":id_populasi", ui->idPopulasiLineEdit->text());
    sql.bindValue(":tgl_populasi", ui->tanggalPopulasiDateEdit->date());
    sql.bindValue(":jml_mati", jmlMati);
    sql.bindValue(":jml_hidup", jmlHidup);
    sql.bindValue(":sisa", hitungSisa);
    sql.bindValue(":kd_kandang", kd_kandang);

    ui->sisaLineEdit->setText(QString::number(hitungSisa));

    if(sql.exec()){
        qDebug()<<"Data berhasil di ubah";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormPopulasi::on_pushButton_3_clicked()
{
    QSqlQuery sql(koneksiDB);
    sql.prepare("DELETE FROM populasi WHERE id_populasi=:id_populasi");
    sql.bindValue(":id_populasi", ui->idPopulasiLineEdit->text());

    if(sql.exec()){
        qDebug()<<"Data berhasil di hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}

