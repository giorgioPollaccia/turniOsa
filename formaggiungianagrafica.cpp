#include "formaggiungianagrafica.h"
#include "ui_formaggiungianagrafica.h"

FormAggiungiAnagrafica::FormAggiungiAnagrafica( QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAggiungiAnagrafica)
{
    ui->setupUi(this);
    this->db= db;

    //combo box per la scelta della matrice di turno da usare per la risorsa
    //viene riempita con l'IDMATRICE ottenuto dalla tabella "matriceTurni"
//    QSqlQuery query1(QString("select distinct IDMATRICE from matriceTurni"));
//    query1.exec();
//    while(query1.next())
//    {
//      ui->cbMatricePredefinita->addItem(query1.value(0).toString());
//    }
     ui->cbMatricePredefinita->addItem("M");
     ui->cbMatricePredefinita->addItem("F");
}

FormAggiungiAnagrafica::~FormAggiungiAnagrafica()
{
    delete ui;
}

void FormAggiungiAnagrafica::on_pbCambiaFoto_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
         qDebug() << "Errore. file della foto non aperto."  ;
         return;
    }

    byteArray = file.readAll();
    QPixmap pixmap = QPixmap();
    if(!byteArray.isEmpty())
    {
        pixmap.loadFromData(byteArray);
        ui->label->setPixmap(pixmap);
        ui->label->adjustSize();
    }
    else
        ui->label->setText("NO FOTO!!");

}

void FormAggiungiAnagrafica::on_pbInserisci_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO anagrafica (Matricola, Cognome, Nome, Sesso, Foto)" "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(ui->leMatricola->text());
    query.addBindValue(ui->leCognome->text());
    query.addBindValue(ui->leNome->text());
    query.addBindValue(ui->cbMatricePredefinita->currentText() );//  cbAbilitatoNotturno->isChecked());
    query.addBindValue(byteArray);
    if (!query.exec())
    {
        QMessageBox msgBox;
        msgBox.setText("Errore.");
        msgBox.setInformativeText(QString("Errore. Insert nel database: %1").arg(query.lastError().text()));
        msgBox.setStandardButtons( QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        qDebug() << "Errore. Insert nel database: " << query.lastError();
    }
    else
    {
          QMessageBox msgBox;
          //msgBox.setText("Insert nel database.");
          msgBox.setInformativeText(QString("Insert nel database."));
          msgBox.setStandardButtons( QMessageBox::Ok);
          msgBox.setIcon(QMessageBox::Information);
          msgBox.exec();
          qDebug() << "Insert nel database: " << query.lastError();
           emit signal_rinfrescadati();
      }

}
