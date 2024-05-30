#include "formjadwal.h"
#include "ui_formjadwal.h"

FormJadwal::FormJadwal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormJadwal)
{
    ui->setupUi(this);
}

FormJadwal::~FormJadwal()
{
    delete ui;
}

void FormJadwal::showEvent(QShowEvent *event) {
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

    ui->kodePakanComboBox->clear();
    sql.prepare("SELECT * FROM pakan");
    sql.exec();
    while(sql.next()){
        QString a = sql.value(sql.record().indexOf("kd_pakan")).toString();
        QString b = sql.value(sql.record().indexOf("nama_pakan")).toString();
        QString c = sql.value(sql.record().indexOf("jenis_pakan")).toString();
        QString d = sql.value(sql.record().indexOf("jml_pakan")).toString();
        QString n = a+"/"+b+"/"+c+"/"+d+" Kg";
        ui->kodePakanComboBox->addItem(n);
    }
}

void FormJadwal::on_pushButton_clicked()
{
    QStringList populasiData = ui->iDPopulasiComboBox->currentText().split("/");
    QString id_populasi = populasiData[0];
    QStringList pakanData = ui->kodePakanComboBox->currentText().split("/");
    QString kd_pakan = pakanData[0];

    QSqlQuery sql(koneksiDB);
    sql.prepare("INSERT INTO jadwal (id_jadwal, tgl_jadwal, jenis, total, jml, id_populasi, kd_pakan) VALUE(:id_jadwal, :tgl_jadwal, :jenis, :total, :jml, :id_populasi, :kd_pakan)");
    sql.bindValue(":id_jadwal", ui->iDJadwalLineEdit->text());
    sql.bindValue(":tgl_jadwal", ui->tanggalJadwalDateEdit->date());
    sql.bindValue(":jenis", ui->jenisJadwalComboBox->currentText());
    sql.bindValue(":total", ui->totalLineEdit->text());
    sql.bindValue(":jml", ui->jumlahPakaiLineEdit->text());
    sql.bindValue(":id_populasi", id_populasi);
    sql.bindValue(":kd_pakan", kd_pakan);

    if(sql.exec()){
        qDebug()<<"Data berhasil di simpan";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormJadwal::on_pushButton_2_clicked()
{
    QStringList populasiData = ui->iDPopulasiComboBox->currentText().split("/");
    QString id_populasi = populasiData[0];
    QStringList pakanData = ui->kodePakanComboBox->currentText().split("/");
    QString kd_pakan = pakanData[0];

    QSqlQuery sql(koneksiDB);
    sql.prepare("UPDATE jadwal SET tgl_jadwal=:tgl_jadwal, jenis=:jenis, total=:total, jml=:jml, id_populasi=:id_populasi, kd_pakan=:kd_pakan WHERE id_jadwal=:id_jadwal");
    sql.bindValue(":id_jadwal", ui->iDJadwalLineEdit->text());
    sql.bindValue(":tgl_jadwal", ui->tanggalJadwalDateEdit->date());
    sql.bindValue(":jenis", ui->jenisJadwalComboBox->currentText());
    sql.bindValue(":total", ui->totalLineEdit->text());
    sql.bindValue(":jml", ui->jumlahPakaiLineEdit->text());
    sql.bindValue(":id_populasi", id_populasi);
    sql.bindValue(":kd_pakan", kd_pakan);

    if(sql.exec()){
        qDebug()<<"Data berhasil di ubah";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormJadwal::on_pushButton_3_clicked()
{
    QSqlQuery sql(koneksiDB);
    sql.prepare("DELETE FROM jadwal WHERE id_jadwal=:id_jadwal");
    sql.bindValue(":id_jadwal", ui->iDJadwalLineEdit->text());

    if(sql.exec()){
        qDebug()<<"Data berhasil di hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}

