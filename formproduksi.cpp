#include "formproduksi.h"
#include "ui_formproduksi.h"

FormProduksi::FormProduksi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormProduksi)
{
    ui->setupUi(this);
    loadTabelProduksi();
    clearFormInput();
}

void FormProduksi::loadTabelProduksi()
{
    // set table
    tabelModel = new QSqlQueryModel(this);
    tabelModel->setQuery("SELECT produksi.id_produksi, produksi.tgl_produksi, produksi.jml_utuh, produksi.jml_retak, produksi.total, produksi.id_populasi, populasi.tgl_populasi, populasi.jml_hidup, populasi.kd_kandang, kandang.nama_kandang, kandang.kapasitas FROM produksi INNER JOIN populasi ON produksi.id_populasi = populasi.id_populasi INNER JOIN kandang ON populasi.kd_kandang = kandang.kd_kandang ORDER BY produksi.id_produksi ASC");
    tabelModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Produksi"));
    tabelModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Tgl Produksi"));
    tabelModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Jumlah Utuh"));
    tabelModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Jumlah Retak"));
    tabelModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Total"));
    tabelModel->setHeaderData(5, Qt::Horizontal, QObject::tr("ID Populasi"));
    tabelModel->setHeaderData(6, Qt::Horizontal, QObject::tr("Tgl Populasi"));
    tabelModel->setHeaderData(7, Qt::Horizontal, QObject::tr("Jumlah Hidup"));
    tabelModel->setHeaderData(8, Qt::Horizontal, QObject::tr("Kode Kandang"));
    tabelModel->setHeaderData(9, Qt::Horizontal, QObject::tr("Nama Kandang"));
    tabelModel->setHeaderData(10, Qt::Horizontal, QObject::tr("Kapasitas"));

    ui->tableProduksi->setModel(tabelModel);
    ui->tableProduksi->setColumnWidth(0, 100);
    ui->tableProduksi->setColumnWidth(1, 100);
    ui->tableProduksi->setColumnWidth(2, 100);
    ui->tableProduksi->setColumnWidth(3, 100);
    ui->tableProduksi->setColumnWidth(4, 100);
    ui->tableProduksi->setColumnWidth(5, 100);
    ui->tableProduksi->setColumnWidth(6, 100);
    ui->tableProduksi->setColumnWidth(7, 100);
    ui->tableProduksi->setColumnWidth(8, 100);
    ui->tableProduksi->setColumnWidth(9, 150);
    ui->tableProduksi->setColumnWidth(10, 100);

    ui->tableProduksi->show();
}

void FormProduksi::clearFormInput()
{
    QDate date = QDate::currentDate();
    ui->iDProduksiLineEdit->setText("");
    ui->tanggalProduksiDateEdit->setDate(date);
    ui->jumlahUtuhLineEdit->setText("");
    ui->jumlahRetakLineEdit->setText("");
    ui->totalLineEdit->setText("");
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

    loadTabelProduksi();
    clearFormInput();
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

    loadTabelProduksi();
    clearFormInput();
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

    loadTabelProduksi();
    clearFormInput();
}


void FormProduksi::on_tableProduksi_clicked(const QModelIndex &index)
{
    int rowidx = ui->tableProduksi->selectionModel()->currentIndex().row();
    QString idPopulasi = tabelModel->index(rowidx, 5).data().toString();
    QString tglPopulasi = tabelModel->index(rowidx, 6).data().toString();
    QString jmlHidup = tabelModel->index(rowidx, 7).data().toString();
    QString cmbText = idPopulasi+"/"+tglPopulasi+"/"+jmlHidup;

    ui->iDProduksiLineEdit->setText(tabelModel->index(rowidx, 0).data().toString());
    ui->tanggalProduksiDateEdit->setDate(tabelModel->index(rowidx, 1).data().toDate());
    ui->jumlahUtuhLineEdit->setText(tabelModel->index(rowidx, 2).data().toString());
    ui->jumlahRetakLineEdit->setText(tabelModel->index(rowidx, 3).data().toString());
    ui->totalLineEdit->setText(tabelModel->index(rowidx, 4).data().toString());
    ui->iDPopulasiComboBox->setCurrentText(cmbText);
}

