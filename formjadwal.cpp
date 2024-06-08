#include "formjadwal.h"
#include "ui_formjadwal.h"

FormJadwal::FormJadwal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormJadwal)
{
    ui->setupUi(this);
    clearFormInput();
    loadTabelJadwal();

}

void FormJadwal::loadTabelJadwal()
{
    // set table
    tabelModel = new QSqlQueryModel(this);
    tabelModel->setQuery("SELECT jadwal.id_jadwal, jadwal.tgl_jadwal, jadwal.jenis, jadwal.total, jadwal.jml, jadwal.id_populasi, populasi.tgl_populasi, populasi.jml_hidup, kandang.nama_kandang, jadwal.kd_pakan, pakan.nama_pakan, pakan.jenis_pakan, pakan.jml_pakan FROM jadwal INNER JOIN populasi ON jadwal.id_populasi = populasi.id_populasi INNER JOIN kandang ON populasi.kd_kandang = kandang.kd_kandang INNER JOIN pakan ON jadwal.kd_pakan = pakan.kd_pakan ORDER BY jadwal.id_jadwal ASC");
    tabelModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Jadwal"));
    tabelModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Tgl Jadwal"));
    tabelModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Jenis Jadwal"));
    tabelModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Total Pakan Awal"));
    tabelModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Jumlah Pakai"));
    tabelModel->setHeaderData(5, Qt::Horizontal, QObject::tr("ID Populasi"));
    tabelModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Tgl Populasi"));
    tabelModel->setHeaderData(7, Qt::Horizontal, QObject::tr("Jumlah Hidup"));
    tabelModel->setHeaderData(8, Qt::Horizontal, QObject::tr("Nama Kandang"));
    tabelModel->setHeaderData(9, Qt::Horizontal, QObject::tr("Kode Pakan"));
    tabelModel->setHeaderData(10, Qt::Horizontal, QObject::tr("Nama Pakan"));
    tabelModel->setHeaderData(11, Qt::Horizontal, QObject::tr("Jenis Pakan"));
    tabelModel->setHeaderData(12, Qt::Horizontal, QObject::tr("Jumlah Pakan"));

    ui->tableJadwal->setModel(tabelModel);
    ui->tableJadwal->setColumnWidth(0, 100);
    ui->tableJadwal->setColumnWidth(1, 100);
    ui->tableJadwal->setColumnWidth(2, 100);
    ui->tableJadwal->setColumnWidth(3, 100);
    ui->tableJadwal->setColumnWidth(4, 100);
    ui->tableJadwal->setColumnWidth(5, 100);
    ui->tableJadwal->setColumnWidth(6, 100);
    ui->tableJadwal->setColumnWidth(7, 100);
    ui->tableJadwal->setColumnWidth(8, 100);
    ui->tableJadwal->setColumnWidth(9, 150);
    ui->tableJadwal->setColumnWidth(10, 100);
    ui->tableJadwal->setColumnWidth(11, 100);
    ui->tableJadwal->setColumnWidth(12, 100);

    ui->tableJadwal->show();
}

void FormJadwal::clearFormInput()
{
    QDate date = QDate::currentDate();
    ui->iDJadwalLineEdit->setText("");
    ui->jumlahPakaiLineEdit->setText("");
    ui->totalLineEdit->setText("");
    ui->tanggalJadwalDateEdit->setDate(date);
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

    clearFormInput();
    loadTabelJadwal();
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

    clearFormInput();
    loadTabelJadwal();
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

    clearFormInput();
    loadTabelJadwal();
}


void FormJadwal::on_tableJadwal_clicked(const QModelIndex &index)
{
    int rowidx = ui->tableJadwal->selectionModel()->currentIndex().row();
    QString idPopulasi = tabelModel->index(rowidx, 5).data().toString();
    QString tglPopulasi = tabelModel->index(rowidx, 6).data().toString();
    QString jmlHidup = tabelModel->index(rowidx, 7).data().toString();
    QString cmbPopulasi = idPopulasi+"/"+tglPopulasi+"/"+jmlHidup;

    QString kd_pakan = tabelModel->index(rowidx, 9).data().toString();
    QString nama_pakan = tabelModel->index(rowidx, 10).data().toString();
    QString jenis_pakan = tabelModel->index(rowidx, 11).data().toString();
    QString jml_pakan = tabelModel->index(rowidx, 12).data().toString();
    QString cmbPakan = kd_pakan+"/"+nama_pakan+"/"+jenis_pakan+"/"+jml_pakan+" Kg";

    ui->iDJadwalLineEdit->setText(tabelModel->index(rowidx, 0).data().toString());
    ui->tanggalJadwalDateEdit->setDate(tabelModel->index(rowidx, 1).data().toDate());
    ui->jenisJadwalComboBox->setCurrentText(tabelModel->index(rowidx, 2).data().toString());
    ui->totalLineEdit->setText(tabelModel->index(rowidx, 3).data().toString());
    ui->jumlahPakaiLineEdit->setText(tabelModel->index(rowidx, 4).data().toString());

    ui->iDPopulasiComboBox->setCurrentText(cmbPopulasi);
    ui->kodePakanComboBox->setCurrentText(cmbPakan);
}

