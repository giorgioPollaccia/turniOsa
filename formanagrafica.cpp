#include "formanagrafica.h"
#include "ui_formanagrafica.h"


#include <QSqlQuery>
#include <QSqlError>




FormAnagrafica::FormAnagrafica( QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAnagrafica)
{
    ui->setupUi(this);
    this->db= db;

        masterModel = new QSqlRelationalTableModel;
        masterModel->setTable("anagrafica");
      //  masterModel->setHeaderData(0, Qt::Horizontal, tr("Cognome"));
      //  masterModel->setHeaderData(1, Qt::Horizontal, tr("Nome"));
        masterModel->removeColumn(4);
        masterModel->select();
        ui->tvanagrafica->setModel(masterModel);
        //  ui->tvanagrafica->verticalHeader()->setResizeContentsPrecision(QHeaderView::ResizeToContents);
        ui->tvanagrafica->verticalHeader()->setDefaultSectionSize(20);
        connect( ui->tvanagrafica->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(updateDetailGrid()));
        ui->tvanagrafica->setSortingEnabled(1);
        ui->tvanagrafica->sortByColumn(1,Qt::AscendingOrder);

        ui->tvanagrafica->selectRow(0);

        //combo box per la scelta della matrice di turno da usare per la risorsa
        //viene riempita con l'IDMATRICE ottenuto dalla tabella "matriceTurni"
//        QSqlQuery query1(QString("select distinct IDMATRICE from matriceTurni"));
//        query1.exec();
//        while(query1.next())
//        {
//            ui->cbMatricePredefinita->addItem(query1.value(0).toString());
//        }

        ui->cbGenere->addItem("M");
        ui->cbGenere->addItem("F");


        QDataWidgetMapper *mapper = new QDataWidgetMapper;
        mapper->setModel(masterModel);
        mapper->setItemDelegate(new QSqlRelationalDelegate(this));
        mapper->addMapping(ui->leMatricola, 0);
        mapper->addMapping(ui->leCognome, 1);
        mapper->addMapping(ui->leNome, 2);

        //mapper->addMapping(ui->cbAbilitatoNotturno, 3);
        mapper->addMapping(ui->cbGenere, 3);
        mapper->toFirst();

        connect(ui->tvanagrafica->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), mapper, SLOT(setCurrentModelIndex(QModelIndex)));
        connect(ui->tvanagrafica->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(slot_visualizzaFoto(QModelIndex)));


        QSqlQuery query(QString("SELECT Foto FROM anagrafica where Matricola=\"%1\"").arg(ui->leMatricola->text()));
        query.next();
        QByteArray array = query.value(0).toByteArray();
        QPixmap pixmap = QPixmap();
        if(!array.isEmpty())
        {
            pixmap.loadFromData(array);
            ui->label->setPixmap(pixmap);
            ui->label->adjustSize();
        }
        else
            ui->label->setText("NO FOTO!!");


        QSqlQuery queryReparto1(QString("select idreparto,descrizione from reparti"));
        queryReparto1.exec();
        while(queryReparto1.next())
            ui->cbReparto->addItem(QString("%1 %2").arg(queryReparto1.value(0).toString()).arg(queryReparto1.value(1).toString()));

        QSqlQuery queryReparto(QString("select operatori.idreparto, descrizione from operatori, reparti where operatori.[IDREPARTO]=reparti.[IDREPARTO] and operatori.[MATRICOLA]=\"%1\"").arg(ui->leMatricola->text()));
        queryReparto.exec();
        queryReparto.next();
        ui->cbReparto->setCurrentText(QString("%1 %2").arg(queryReparto.value(0).toString()).arg(queryReparto.value(1).toString()));

}

 void FormAnagrafica::slot_visualizzaFoto(QModelIndex)
 {
     QSqlQuery query(QString("SELECT Foto FROM anagrafica where Matricola=\"%1\"").arg(ui->leMatricola->text()));
     query.next();
     QByteArray array = query.value(0).toByteArray();
     QPixmap pixmap = QPixmap();
     if(!array.isEmpty())
     {
         pixmap.loadFromData(array);
         ui->label->setPixmap(pixmap);
         ui->label->adjustSize();
     }
     else
         ui->label->setText("NO FOTO!!");
 }

FormAnagrafica::~FormAnagrafica()
{
    delete ui;
}

void FormAnagrafica::on_tvanagrafica_clicked(const QModelIndex &index)
{

}



 void FormAnagrafica::updateDetailGrid()
 {

 }

void FormAnagrafica::on_pbCambiaFoto_clicked()
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

    QByteArray byteArray = file.readAll();

    QSqlQuery query;
    // query.prepare("INSERT INTO anagrafica (Cognome, Nome, Matricola, AbilitatoNotte, Foto)" "VALUES (?, ?, ?, ?, ?)");
    query.prepare(QString("UPDATE anagrafica SET Foto = :foto WHERE  Matricola=\"%1\"").arg(ui->leMatricola->text()));
    query.bindValue(":foto", byteArray);
    if (!query.exec())
        qDebug() << "Errore. Update nel database: " << query.lastError();
    else
    {
        QSqlQuery query(QString("SELECT Foto FROM anagrafica where Matricola=\"%1\"").arg(ui->leMatricola->text()));
        query.next();
        QByteArray array = query.value(0).toByteArray();
        QPixmap pixmap = QPixmap();
        if(!array.isEmpty())
        {
            pixmap.loadFromData(array);
            ui->label->setPixmap(pixmap);
            ui->label->adjustSize();
        }
        else
            ui->label->setText("NO FOTO!!");


    }

}

void FormAnagrafica::on_pbCancellaRisorsa_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Conferma.");
    msgBox.setInformativeText(QString("Vuoi cancellare la risorsa %1 dal database?").arg(ui->leMatricola->text()));
    msgBox.setStandardButtons(QMessageBox::Yes |  QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setIcon(QMessageBox::Question);
    if(msgBox.exec()== QMessageBox::Yes)
   {

    QSqlQuery query(QString("DELETE FROM anagrafica where Matricola=\"%1\"").arg(ui->leMatricola->text()));
    query.exec();
    }

   slot_rinfrescaDati();

}


void FormAnagrafica::slot_rinfrescaDati()
{

    masterModel->setTable("anagrafica");
  //  masterModel->setHeaderData(0, Qt::Horizontal, tr("Cognome"));
  //  masterModel->setHeaderData(1, Qt::Horizontal, tr("Nome"));
    masterModel->removeColumn(4);
    masterModel->select();
    ui->tvanagrafica->setModel(masterModel);
    //  ui->tvanagrafica->verticalHeader()->setResizeContentsPrecision(QHeaderView::ResizeToContents);
    ui->tvanagrafica->verticalHeader()->setDefaultSectionSize(20);
    connect( ui->tvanagrafica->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(updateDetailGrid()));
    ui->tvanagrafica->setSortingEnabled(1);
    ui->tvanagrafica->sortByColumn(1,Qt::AscendingOrder);
    ui->tvanagrafica->selectRow(0);

}

void FormAnagrafica::on_leMatricola_textChanged(const QString &arg1)
{
    QSqlQuery queryReparto(QString("select operatori.idreparto, descrizione from operatori, reparti where operatori.[IDREPARTO]=reparti.[IDREPARTO] and operatori.[MATRICOLA]=\"%1\"").arg(arg1));
    queryReparto.exec();
    queryReparto.next();
    ui->cbReparto->setCurrentText(QString("%1 %2").arg(queryReparto.value(0).toString()).arg(queryReparto.value(1).toString()));

}

void FormAnagrafica::on_pbCambiaReparto_clicked()
{
    QSqlQuery queryReparto(QString("update operatori set idreparto where matricola=\"%1\"").arg(ui->leMatricola->text()));
    queryReparto.exec();
}
