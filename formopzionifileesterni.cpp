#include "formopzionifileesterni.h"
#include "ui_formopzionifileesterni.h"

FormOpzioniFileEsterni::FormOpzioniFileEsterni(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormOpzioniFileEsterni)
{
    ui->setupUi(this);
    this->db= db;
    QSettings settings("Pollaccia", "turniOSA");
    ui->leNomeFileExcelMatriceTurni->setText(settings.value("opzioniFileEsterni/fileMatriciTurni","").toString());
    ui->cbFileMatriceTurni->setChecked(settings.value("opzioniFileEsterni/fileMatriciTurniCaricaAvvio", "true").toBool());
    ui->leNomeFileDatabase->setText(settings.value("opzioniFileEsterni/fileSQLITE","").toString());
}

FormOpzioniFileEsterni::~FormOpzioniFileEsterni()
{
    delete ui;
}

void FormOpzioniFileEsterni::on_pbScegliFileMatriceTurni_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Scegli file EXCEL descrittivo delle matrici di turni."), ".", tr("EXCEL file (*.xlsx)"));
    ui->leNomeFileExcelMatriceTurni->setText(fileName);
}

void FormOpzioniFileEsterni::on_pbSalvaOpzioni_clicked()
{
    QSettings settings("Pollaccia", "turniOSA");
    settings.setValue("opzioniFileEsterni/fileMatriciTurni", ui->leNomeFileExcelMatriceTurni->text());
    settings.setValue("opzioniFileEsterni/fileMatriciTurniCaricaAvvio", ui->cbFileMatriceTurni->isChecked());
    settings.setValue("opzioniFileEsterni/fileSQLITE", ui->leNomeFileDatabase->text());
}

void FormOpzioniFileEsterni::on_pbFileSqlite_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("Scegli file SQLITE del database."), ".", tr("SQLITE file (*.sqlite)"));
    ui->leNomeFileDatabase->setText(fileName);
}
