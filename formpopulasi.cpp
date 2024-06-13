#include "formpopulasi.h"
#include "ui_formpopulasi.h"

FormPopulasi::FormPopulasi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormPopulasi)
{
    ui->setupUi(this);
    clearFormInput();
    loadTabelPopulasi();

}

void FormPopulasi::loadTabelPopulasi()
{
    // set table
    tabelModel = new QSqlQueryModel(this);
    tabelModel->setQuery("SELECT populasi.id_populasi, populasi.tgl_populasi, populasi.jml_mati, populasi.jml_hidup, populasi.sisa, populasi.kd_kandang, kandang.nama_kandang, kandang.kapasitas FROM populasi INNER JOIN kandang ON populasi.kd_kandang = kandang.kd_kandang ORDER BY populasi.id_populasi ASC");
    tabelModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Populasi"));
    tabelModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Tgl Populasi"));
    tabelModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Jumlah Mati"));
    tabelModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Jumlah Hidup"));
    tabelModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Sisa"));
    tabelModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Kode Kandang"));
    tabelModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Nama Kandang"));
    tabelModel->setHeaderData(7, Qt::Horizontal, QObject::tr("Kapasitas"));

    ui->tablePopulasi->setModel(tabelModel);
    ui->tablePopulasi->setColumnWidth(0, 100);
    ui->tablePopulasi->setColumnWidth(1, 100);
    ui->tablePopulasi->setColumnWidth(2, 100);
    ui->tablePopulasi->setColumnWidth(3, 100);
    ui->tablePopulasi->setColumnWidth(4, 100);
    ui->tablePopulasi->setColumnWidth(5, 100);
    ui->tablePopulasi->setColumnWidth(6, 150);
    ui->tablePopulasi->setColumnWidth(7, 100);
    ui->tablePopulasi->show();
}

void FormPopulasi::clearFormInput()
{
    QDate date = QDate::currentDate();
    ui->idPopulasiLineEdit->setText("");
    ui->tanggalPopulasiDateEdit->setDate(date);
    ui->jumlahHidupLineEdit->setText("");
    ui->jumlahMatiLineEdit->setText("");
    ui->sisaLineEdit->setText("");
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
    if(formChecker->isFieldEmpty(this, ui->idPopulasiLineEdit, "ID Populasi Belum Di Isi") ||
        formChecker->isFieldEmpty(this, ui->jumlahMatiLineEdit, "Jumlah Mati Belum Di Isi") ||
        formChecker->isFieldEmpty(this, ui->jumlahHidupLineEdit, "Jumlah Hidup Belum Di Isi") ){
        return;
    }

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

    sql.prepare("SELECT * FROM populasi WHERE id_populasi = '"+ ui->idPopulasiLineEdit->text() + "'");
    sql.exec();

    if (sql.next()) {
        QMessageBox::information(this, "Warning", "ID Populasi Sudah Digunakan");
        ui->idPopulasiLineEdit->setText(sql.value(0).toString());
        ui->tanggalPopulasiDateEdit->setDate(sql.value(1).toDate());
        ui->jumlahMatiLineEdit->setText(sql.value(2).toString());
        ui->jumlahHidupLineEdit->setText(sql.value(3).toString());
        ui->sisaLineEdit->setText(sql.value(4).toString());

        // cari kode_kandang dan set text ke cmbbox
        QString cekKodeKandang = sql.value(5).toString();
        sql.prepare("SELECT * FROM kandang WHERE kd_kandang = '"+ cekKodeKandang + "'");
        sql.exec();
        sql.next();
        QString kdKandang = sql.value(0).toString();
        QString namaKandang = sql.value(1).toString();
        QString kapasitas = sql.value(2).toString();
        QString cmbText = kdKandang+"/"+namaKandang+"/"+kapasitas;
        ui->kodeKandangComboBox->setCurrentText(cmbText);
    } else {
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

        clearFormInput();
        loadTabelPopulasi();
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

    clearFormInput();
    loadTabelPopulasi();
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

    clearFormInput();
    loadTabelPopulasi();
}


void FormPopulasi::on_tablePopulasi_clicked(const QModelIndex &index)
{
    int rowidx = ui->tablePopulasi->selectionModel()->currentIndex().row();
    QString kdKandang = tabelModel->index(rowidx, 5).data().toString();
    QString namaKandang = tabelModel->index(rowidx, 6).data().toString();
    QString kapasitas = tabelModel->index(rowidx, 7).data().toString();
    QString cmbText = kdKandang+"/"+namaKandang+"/"+kapasitas;

    ui->idPopulasiLineEdit->setText(tabelModel->index(rowidx, 0).data().toString());
    ui->tanggalPopulasiDateEdit->setDate(tabelModel->index(rowidx, 1).data().toDate());
    ui->jumlahMatiLineEdit->setText(tabelModel->index(rowidx, 2).data().toString());
    ui->jumlahHidupLineEdit->setText(tabelModel->index(rowidx, 3).data().toString());
    ui->sisaLineEdit->setText(tabelModel->index(rowidx, 4).data().toString());
    ui->kodeKandangComboBox->setCurrentText(cmbText);
}

