#include "formgestioneferie.h"
#include "ui_formgestioneferie.h"
#include <QDebug>



FormGestioneFerie::FormGestioneFerie(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGestioneFerie)
{
    ui->setupUi(this);

    QDate oggi;
    ui->dePermessiDal->setDate(oggi.currentDate());
    ui->dePermessiAl->setDate(oggi.currentDate());

    this->db= db;



    QSqlQuery query(QString("SELECT Matricola,cognome FROM anagrafica"));
    while (query.next())
    {
     ui->cbMatricola->addItem(  query.value(0).toString() );
     ui->cbCognome->addItem(  query.value(1).toString() );
     ui->lNome->setText( query.value(2).toString() );
    }
    QSqlQuery query1(QString("SELECT nome FROM anagrafica where Matricola=\"%1\"").arg(ui->cbMatricola->currentText()));
    query1.next();
    ui->lNome->setText( query1.value(0).toString() );



    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery query2("Select tipoPermesso, data from permessi");

    model->setQuery(query2);
    model->setHeaderData(0, Qt::Horizontal, tr("Tipo Permesso"));
    model->setHeaderData(1, Qt::Horizontal, tr("Data"));

    ui->tvPermessi->setModel(model);

}

FormGestioneFerie::~FormGestioneFerie()
{
    delete ui;
}

void FormGestioneFerie::on_pbDataDal_clicked()
{
    FormCalendario *fCalendario = new FormCalendario("Permesso dal ...");
    fCalendario->setAttribute(Qt::WA_DeleteOnClose);
    connect(fCalendario, SIGNAL(signal_data(QDate)),this,SLOT( slot_dataIniziale(QDate)));
    fCalendario->setWindowModality(Qt::ApplicationModal);
    fCalendario->setWindowFlags(Qt::Tool);
    fCalendario->show();
}

void  FormGestioneFerie::slot_dataIniziale(QDate data)
{
    ui->dePermessiDal->setDate(data);
    ui->dePermessiAl->setDate(data);
}

void FormGestioneFerie::on_pbDataAl_clicked()
{
    FormCalendario *fCalendario = new FormCalendario("Permesso fino al ...");
    fCalendario->setAttribute(Qt::WA_DeleteOnClose);
    connect(fCalendario, SIGNAL(signal_data(QDate)),this,SLOT( slot_dataFinale(QDate)));
    fCalendario->setWindowModality(Qt::ApplicationModal);
    fCalendario->setWindowFlags(Qt::Tool);
    fCalendario->show();
}
void  FormGestioneFerie::slot_dataFinale(QDate data)
{
    if  (data.operator <(ui->dePermessiDal->date()))
    {
        QMessageBox msgBox;
        msgBox.setText("Errore.");
        msgBox.setInformativeText(QString("La data di fine del permesso non può essere antecedente a quella di inizio."));
        msgBox.setStandardButtons( QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        ui->dePermessiAl->setDate( ui->dePermessiDal->date());
    }
    else
        ui->dePermessiAl->setDate(data);
}

void FormGestioneFerie::on_cbMatricola_currentIndexChanged(const QString &arg1)
{

    ui->cbCognome->setCurrentIndex(ui->cbMatricola->currentIndex());
    QSqlQuery query1(QString("SELECT nome FROM anagrafica where Matricola=\"%1\"").arg(ui->cbMatricola->currentText()));
    query1.next();
    ui->lNome->setText( query1.value(0).toString() );


}

void FormGestioneFerie::on_cbCognome_currentIndexChanged(const QString &arg1)
{

    ui->cbMatricola->setCurrentIndex(ui->cbCognome->currentIndex());
    QSqlQuery query1(QString("SELECT nome FROM anagrafica where Matricola=\"%1\"").arg(ui->cbMatricola->currentText()));
    query1.next();
    ui->lNome->setText( query1.value(0).toString() );

}


void FormGestioneFerie::on_pbAggiungiPermesso_clicked()
{
    for(QDate a=ui->dePermessiDal->date(); a.operator <=( ui->dePermessiAl->date());a= a.addDays(1) )
   {

    qDebug() << "Permesso per "+ui->cbMatricola->currentText()+" per il giorno "+a.toString("dd/MM/yyyy");


    QSqlQuery query;
    query.prepare("INSERT INTO permessi (ID, matricola, tipoPermesso, data)" "VALUES (?, ?, ?, ?)");
   // query.addBindValue( ui->cbMatricola->currentText()+"_"+ui->dePermessiDal->date().toString("dd/MM/yyyy"));
    query.addBindValue( ui->cbMatricola->currentText()+"_"+a.toString("dd/MM/yyyy"));
    query.addBindValue( ui->cbMatricola->currentText());
    query.addBindValue( ui->cbTipoPermesso->currentText());
   // query.addBindValue( ui->dePermessiDal->date().toString("dd/MM/yyyy"));
    query.addBindValue( a.toString("dd/MM/yyyy"));
    if(query.exec())
    {
        QMessageBox msgBox;
        msgBox.setText("Inserzione nel database.");
        msgBox.setInformativeText(QString("Permesso per il giorno %1 inserito correttamente.").arg(a.toString("dd/MM/yyyy")));
        msgBox.setStandardButtons(QMessageBox::Ok );
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Inserzione nel database.");
        msgBox.setInformativeText(QString("Permesso per il giorno %1 NON inserito nel database. Probabilmente è gia stato inserito un permesso per lo stesso giorno.").arg(a.toString("dd/MM/yyyy")));
        msgBox.setStandardButtons(QMessageBox::Ok );
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
  }
}
