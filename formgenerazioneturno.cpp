#include "formgenerazioneturno.h"
#include "ui_formgenerazioneturno.h"

#include <QSqlQuery>
#include <QSqlError>
#include "xlsxdocument.h"


FormGenerazioneTurno::FormGenerazioneTurno(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGenerazioneTurno)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->db= db;



    ui->tw->setSelectionBehavior(QAbstractItemView::SelectRows);


    QDate oggi;

    if(oggi.currentDate().month()==12)  ///Seil mese corrente è dicembre il turno da fare è gennaio del nuovo anno
    {
          ui->cbAnno->setCurrentIndex(oggi.currentDate().year()-2015+1);
          ui->cbMese->setCurrentIndex(0);
    }
    else  ///altrimenti il turno da fare è il mese successivo dell'anno in corso
    {
          ui->cbAnno->setCurrentIndex(oggi.currentDate().year()-2015);
          ui->cbMese->setCurrentIndex(oggi.currentDate().month());
    }
    dataIniziale.setDate(ui->cbAnno->currentIndex()+2015, ui->cbMese->currentIndex()+1 ,1);
    dataFinale.setDate(ui->cbAnno->currentIndex()+2015, ui->cbMese->currentIndex()+1 , dataIniziale.daysInMonth() );
    while (dataIniziale.dayOfWeek()!=1)  ///PRIMO LUNEDI DEL MESE CORRENTE
      dataIniziale=  dataIniziale.addDays(1);
    ui->dePermessiDal->setDate(dataIniziale);

    while (dataFinale.dayOfWeek()!=7)  ///ULTIMA DOMENICA DEL MESE CORRENTE OPPURE PRIMA DOMENICA DEL MESE SUCCESSIVO
      dataFinale=  dataFinale.addDays(1);
    ui->dePermessiAl->setDate(dataFinale);


    ui->tw->setColumnCount(7 +dataIniziale.daysTo(dataFinale)+1);
    ui->tw->setRowCount(2);
    //Set Header Label Texts Here
  //  ui->tw->setHorizontalHeaderLabels(QString("ID;Cognome;Nome; ;Matrice;TBase;TPrec").split(";"));
    ui->tw->setItem(0,0, new QTableWidgetItem(QString("ID")));
    ui->tw->setItem(0,1, new QTableWidgetItem(QString("Cognome")));
    ui->tw->setItem(0,2, new QTableWidgetItem(QString("Nome")));
    ui->tw->setItem(0,3, new QTableWidgetItem(QString("Turno Precedente")));
    ui->tw->setItem(0,4, new QTableWidgetItem(QString("Abilita")));
    ui->tw->setItem(0,5, new QTableWidgetItem(QString("Tipo Turno Succ.")));
    ui->tw->setItem(0,6, new QTableWidgetItem(QString("Turno Succ.")));



    QFont font;
    font.setBold(true);
    ui->tw->item(0, 0)->setFont(font);
    ui->tw->item(0, 1)->setFont(font);
    ui->tw->item(0, 2)->setFont(font);
    ui->tw->item(0, 3)->setFont(font);
    ui->tw->item(0, 4)->setFont(font);
    ui->tw->item(0, 5)->setFont(font);
    ui->tw->item(0, 6)->setFont(font);


    QDate comodo= dataIniziale;
    for(int j= 7; j < 7 +dataIniziale.daysTo(dataFinale)+1; j++, comodo= comodo.addDays(1))
    {
         ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM/yyyy"))));
         ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));
         ui->tw->item(0, j)->setFont(font);
         ui->tw->item(1, j)->setFont(font);
    }





    /////////////////////////////////////////  reparti disponibili /////////////
    QSqlQuery queryReparti("SELECT descrizione FROM reparti");
    qDebug() << queryReparti.lastQuery() << queryReparti.lastError();
    while (queryReparti.next())
    {
       ui->cbreparti->addItem(queryReparti.value(0).toString());
       qDebug() << queryReparti.value(0).toString();
    }
    /////////////////////////////////////////////



    popolaLaTabella_tw();
    generaTurniSequenziali(0);

    //connect(ui->pbValidaTurnoBase, SIGNAL(clicked()),this, SLOT(slot_checkDoppioniAssociazioniTurnoBase()));
}




void FormGenerazioneTurno::popolaLaTabella_tw()
{
    //////////////////////////////// si popola l'interfaccia con le persone allocate al reparto scelto nel comboBox
    QSqlQuery queryOperatoriRepartiCount(QString(" SELECT count(*) from (SELECT operatori.matricola,cognome,nome FROM reparti join operatori  on operatori.idreparto=reparti.idreparto join anagrafica on operatori.matricola=anagrafica.matricola where descrizione=\"%1\" order by cognome )").arg(ui->cbreparti->currentText()));
    queryOperatoriRepartiCount.first();
    qDebug() << queryOperatoriRepartiCount.lastQuery() << queryOperatoriRepartiCount.lastError();
    ui->tw->setRowCount(queryOperatoriRepartiCount.value(0).toInt()+2);

    QFont font;
    font.setBold(true);

    int riga =2;
    QSqlQuery queryOperatoriReparti(QString("SELECT operatori.matricola,cognome,nome FROM reparti join operatori  on operatori.idreparto=reparti.idreparto join anagrafica on operatori.matricola=anagrafica.matricola where descrizione=\"%1\" order by cognome").arg(ui->cbreparti->currentText()));
    qDebug() << queryOperatoriReparti.lastQuery() << queryOperatoriReparti.lastError();
    while (queryOperatoriReparti.next())
    {
        QString Matricola=  queryOperatoriReparti.value(0).toString();
        QString Cognome=  queryOperatoriReparti.value(1).toString();
        QString Nome=  queryOperatoriReparti.value(2).toString();
        qDebug() << Matricola <<" "<< Cognome <<" "<<Nome;
        ui->tw->setItem(riga,0,new QTableWidgetItem(Matricola));
        ui->tw->setItem(riga,1,new QTableWidgetItem(Cognome));
        ui->tw->setItem(riga,2,new QTableWidgetItem(Nome));
        ui->tw->item(riga, 0)->setFont(font);
        ui->tw->item(riga, 1)->setFont(font);
        ui->tw->item(riga, 2)->setFont(font);


        ////////////////  RICAVO il turno precedente
        QSqlQuery queryWeekTurnoPrecedente(QString("select * from turnazione_operatore where week=(select strftime('%W', '%1','localtime', 'weekday 0', '-6 days')) and anno=%2 and matricola=\"%3\"").arg(dataIniziale.addDays(-1).toString("yyyy-MM-dd")).arg(dataIniziale.year()).arg(Matricola));
        queryWeekTurnoPrecedente.next();

        ui->tw->setItem(riga,3,new QTableWidgetItem(QString("%1 %2 -- %3 %4 %5 %6 %7 %8 %9")
                                                    .arg(queryWeekTurnoPrecedente.value(2).toString())
                                                    .arg(queryWeekTurnoPrecedente.value(3).toInt())
                                                    .arg(queryWeekTurnoPrecedente.value(7).toString())
                                                    .arg(queryWeekTurnoPrecedente.value(8).toString())
                                                    .arg(queryWeekTurnoPrecedente.value(9).toString())
                                                    .arg(queryWeekTurnoPrecedente.value(10).toString())
                                                    .arg(queryWeekTurnoPrecedente.value(11).toString())
                                                    .arg(queryWeekTurnoPrecedente.value(12).toString())
                                                    .arg(queryWeekTurnoPrecedente.value(13).toString())));



        qDebug() << queryWeekTurnoPrecedente.lastQuery() << queryWeekTurnoPrecedente.lastError();




        //////////////////////////////////////////////CElla con il checkBox per abilitare o meno la risorsa
        QCheckBox *pCheckBox = new QCheckBox();
        pCheckBox->setChecked(1);
        ui->tw->setCellWidget(riga,4,pCheckBox);


    //////////////////////////////////////////////////////////////////////////////















    //ui->dePermessiDal->setDate(oggi.currentDate());
    //ui->dePermessiAl->setDate(oggi.currentDate());
    //dataIniziale.setDate(oggi.currentDate().year(),oggi.currentDate().month(),oggi.currentDate().day());
    //dataFinale.setDate(oggi.currentDate().year(),oggi.currentDate().month(),oggi.currentDate().day());
    //qDebug() << dataIniziale.toString("dd/MM/yyyy");
    //qDebug() << dataFinale.toString("dd/MM/yyyy");










//    QSqlQuery queryTurnoPrecedente(QString("select  anagrafica.matricola,cognome, nome, turno, data from anagrafica join turnazione on anagrafica.matricola=turnazione.matricola where anagrafica.matricola=1 and datasqlite >= '%1' and datasqlite <= '%2'").arg(dataIniziale.addDays(-7).toString("yyyy-MM-dd")).arg(dataIniziale.addDays(-1).toString("yyyy-MM-dd")));
//    queryTurnoPrecedente.exec();
//    while(queryTurnoPrecedente.next())
//    {
//        qDebug() << queryTurnoPrecedente.value(0).toString();
//        qDebug() << queryTurnoPrecedente.value(1).toString();
//        qDebug() << queryTurnoPrecedente.value(2).toString();
//        qDebug() << queryTurnoPrecedente.value(3).toString();
//        qDebug() << queryTurnoPrecedente.value(4).toString();
//    }
//    qDebug() << queryTurnoPrecedente.lastQuery();







//    /// dalla query ricavo le stringhe per popolare la tabella
////////    query.seek(0);
////////    for(int i= 2; i < numeroRisorse+2; i++)
////////{
////////       QString Matricola=  query.value(0).toString();
////////       QString Cognome=  query.value(1).toString();
////////       QString Nome=  query.value(2).toString();
////////
////////       ui->tw->setItem(i,0,new QTableWidgetItem(Matricola));
////////       ui->tw->setItem(i,1,new QTableWidgetItem(Cognome));
////////       ui->tw->setItem(i,2,new QTableWidgetItem(Nome));
////////       ui->tw->item(i, 0)->setFont(font);
////////       ui->tw->item(i, 1)->setFont(font);
////////       ui->tw->item(i, 2)->setFont(font);
////////       query.next();
////////
////////
////////       QString turnoPrec;
////////       QSqlQuery queryTurnoPrecedente1(QString("select  turno from turnazione  where matricola=%1 and datasqlite >= '%2' and datasqlite <= '%3'").arg(Matricola).arg(dataIniziale.addDays(-7).toString("yyyy-MM-dd")).arg(dataIniziale.addDays(-1).toString("yyyy-MM-dd")));
////////       queryTurnoPrecedente1.exec();
////////       while(queryTurnoPrecedente1.next())
////////       {
////////            turnoPrec.append(QString("%1 ").arg(queryTurnoPrecedente1.value(0).toString()));
////////       }
////////        qDebug() << turnoPrec;



//       QString StringaTurnoPrecedente, TipoTurnoPrecedente;
//       int progressivoTurnoPrecedente;
//       StringaTurnoPrecedente= turnoPrecedente(Matricola, 1, &TipoTurnoPrecedente,&progressivoTurnoPrecedente);

//       QSqlQuery queryTurnoPrec(QString("select IDMATRICE, progressivo from UltimoTipoTurno where matricola=\"%1\"").arg(Matricola));
//       queryTurnoPrec.exec();
//       queryTurnoPrec.next();
//       TipoTurnoPrecedente= queryTurnoPrec.value(0).toString();
//       progressivoTurnoPrecedente= queryTurnoPrec.value(1).toInt();
//       ui->tw->setItem(i,3,new QTableWidgetItem(QString("%1 %2 -- %3").arg(TipoTurnoPrecedente).arg(progressivoTurnoPrecedente).arg(StringaTurnoPrecedente)));
//       //ui->tw->setItem(i,3,new QTableWidgetItem(TipoTurnoPrecedente));
//       //ui->tw->setItem(i,4,new QTableWidgetItem(QString("%1").arg(progressivoTurnoPrecedente)));

////       QComboBox *pComboBoxTurnoPrec = new QComboBox();
////       QSqlQuery queryTurnoPrec(QString("select IDMATRICE, progressivo from matriceTurni"));
////       queryTurnoPrec.exec();
////       while(queryTurnoPrec.next())
////       {
////           pComboBoxTurnoPrec->addItem(QString("%1 %2").arg(queryTurnoPrec.value(0).toString()).arg(queryTurnoPrec.value(1).toInt()));
////       }
////      ui->tw->setCellWidget(i,3,pComboBoxTurnoPrec);
////      pComboBoxTurnoPrec->setCurrentText(QString("%1 %2").arg(TipoTurnoPrecedente).arg(progressivoTurnoPrecedente));













       //combo box per la scelta della matrice di turno da usare per la risorsa
       //viene riempita con l'IDMATRICE ottenuto dalla tabella "matriceTurni"
       QComboBox *pComboBox = new QComboBox();
       //combo box per la scelta del progressivo del turno da usare per la risorsa
       //QComboBox *pComboBox1 = new QComboBox();

       QSqlQuery query1(QString("select distinct IDMATRICE from matriceTurni"));
       query1.exec();
       while(query1.next())
       {
          // pComboBox->addItem(query1.value(0).toString());
           QSqlQuery query2(QString("select progressivo, Lun from matriceTurni where IDMatrice=\"%1\"").arg(query1.value(0).toString()));
           query2.exec();
           while(query2.next())
           {
             ///  pComboBox->addItem(QString("%1 %2 -- %3").arg(query1.value(0).toString()).arg(query2.value(0).toString()).arg(query2.value(1).toString()));
               pComboBox->addItem(QString("%1 %2").arg(query1.value(0).toString()).arg(query2.value(0).toString()));

               // pComboBox1->addItem(query2.value(0).toString());
           }
          // ui->tw->setCellWidget(i,8,pComboBox1);
       }
       ui->tw->setCellWidget(riga,5,pComboBox);

       QString turnosuccessivo;
       // viene ricavato il progressivo massimo per quella tipologiaDiMatrice (ad esempio OSA_NOTTURNO ha un modulo =11
       query1.exec(QString("select count(*) from matriceturni where IDMatrice=\"%1\"").arg(queryWeekTurnoPrecedente.value(2).toString()));
       query1.next();
       int progressivoTurnoSuccessivo,progressivoTurnoPrecedente ;
       progressivoTurnoPrecedente= queryWeekTurnoPrecedente.value(3).toInt();
       if (progressivoTurnoPrecedente==query1.value(0).toInt())
            progressivoTurnoSuccessivo= 1;  //il turno successivo saraà il progressivo 1 se il progressivo precedente era uguale al modulo
       else
            progressivoTurnoSuccessivo= progressivoTurnoPrecedente + 1;


       query1.exec(QString("select Lun, mar, mer, gio, ven, sab, dom from matriceTurni where IDMatrice=\"%1\" and progressivo=\"%2\"").arg(queryWeekTurnoPrecedente.value(2).toString()).arg(progressivoTurnoSuccessivo));
       query1.next();
       turnosuccessivo= QString("%1 %2 %3 %4 %5 %6 %7").arg(query1.value(0).toString())
                                                       .arg(query1.value(1).toString())
                                                       .arg(query1.value(2).toString())
                                                       .arg(query1.value(3).toString())
                                                       .arg(query1.value(4).toString())
                                                       .arg(query1.value(5).toString())
                                                       .arg(query1.value(6).toString());
       ///pComboBox->setCurrentText(QString("%1 %2 -- %3").arg(TipoTurnoPrecedente).arg(progressivoTurnoSuccessivo).arg(query1.value(0).toString()));
       pComboBox->setCurrentText(QString("%1 %2").arg(queryWeekTurnoPrecedente.value(2).toString()).arg(progressivoTurnoSuccessivo));
       ui->tw->setItem(riga,6,new QTableWidgetItem(QString("%1").arg(turnosuccessivo)));


  ///     connect(pComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_cambioIdMatrice(QString)));






////       //Imposto il valore del pComboBox con la stringa che identifica la matrice di default  (impostata nella anagrafica)
////       QSqlQuery query2(QString("select MatricePredefinita  from anagrafica where matricola= \"%1\"").arg(Matricola));
////       query2.exec();
////       while(query2.next())
////       {
////         // qDebug() << QString("%1 MatriceTurno default: %2").arg(Matricola).arg(query2.value(0).toString());
////          pComboBox->setCurrentText(query2.value(0).toString());
////       }
////////    }


       riga++;
   }

     ui->tw->resizeColumnsToContents();
    ui->tw->resizeRowsToContents();
}


void FormGenerazioneTurno::generaTurniSequenziali(bool dallaMatriceTurni)
{
    QFont font;
    font.setBold(true);

    for(int i=2; (i < ui->tw->rowCount() )  ; i++)
    {
        QString matricola= ui->tw->item(i,0)->text();

        QComboBox *pComboBox = new QComboBox();
        pComboBox= ( QComboBox * )ui->tw->cellWidget(i,5);
        QStringList IDMatriceScelta= pComboBox->currentText().split(' ');
        QString Idmatrice= IDMatriceScelta.at(0);
        int progressivo= IDMatriceScelta.at(1).toInt();


        // viene ricavato il progressivo massimo per quella tipologiaDiMatrice (ad esempio OSA_NOTTURNO ha un modulo =11
        QSqlQuery queryMaxProgressivo(QString("select count(*) from matriceturni where IDMatrice=\"%1\"").arg(Idmatrice));
        queryMaxProgressivo.next();
        int progressivoMax= queryMaxProgressivo.value(0).toInt();



        QCheckBox *pCheckBox = new QCheckBox();
        pCheckBox= (QCheckBox *) ui->tw->cellWidget(i,4);
       /// qDebug() << "Matricola: " << matricola<<"IDMatrice: "<< IDMatriceScelta.at(0) <<"progressivo: "<<IDMatriceScelta.at(1);

        for (int j=7;j< ui->tw->columnCount(); j+= 7)
        {


            QString data=  ui->tw->item(0,j)->text();


            QDate Data;
            Data= QDate::fromString(data,"dd/MM/yyyy");
            int week= Data.weekNumber();
            int day= Data.dayOfWeek();
            ///qDebug() << "data: "<<data<< week<<day;

            QString turnosuccessivo;

            QSqlQuery query1;

           // query1.exec(QString("select lun, mar, mer, gio, ven, sab, dom from turnazione_operatore where week=%1 and matricola=\"%2\"").arg(week).arg(matricola));
           // query1.next();
           // if ((query1.value(0).toString()==NULL) ||  dallaMatriceTurni) ///se il turno non e' presente nella turnazione_operatore ma va preso direttamente dalla matriceTurni ad esempio perche' e' una nuova generazione
           // {
                query1.exec(QString("select Lun, mar, mer, gio, ven, sab, dom from matriceTurni where IDMatrice=\"%1\" and progressivo=\"%2\"").arg(IDMatriceScelta.at(0)).arg(progressivo));
                query1.next();
                qDebug() <<"Sequenza nuova da matriceTurni";
           // }
           // else
           //     qDebug() <<"Sequenza da turnazione_operatore";
            turnosuccessivo= QString("%1 %2 %3 %4 %5 %6 %7").arg(query1.value(0).toString())
                                                            .arg(query1.value(1).toString())
                                                            .arg(query1.value(2).toString())
                                                            .arg(query1.value(3).toString())
                                                            .arg(query1.value(4).toString())
                                                            .arg(query1.value(5).toString())
                                                            .arg(query1.value(6).toString());

            for (int d=0 ; d<7; d++)
            {
                ui->tw->setItem(i,j+d,new QTableWidgetItem(QString("%1").arg(query1.value(d).toString())));
                QBrush brush1;
                if (query1.value(d).toString()=="R")
                {
                    brush1.setColor(QColor(Qt::darkRed));
                    ui->tw->item(i,j+d)->setForeground(brush1);
                }
                if (query1.value(d).toString()=="N")
                {
                    brush1.setColor(QColor(Qt::darkBlue));
                    ui->tw->item(i,j+d)->setForeground(brush1);
                }
                if (query1.value(d).toString()=="S")
                {
                    brush1.setColor(QColor(Qt::darkGreen));
                    ui->tw->item(i,j+d)->setForeground(brush1);
                }
                if(d==6)
                {
                    brush1.setStyle(Qt::Dense5Pattern);
                    brush1.setColor(Qt::lightGray);
                    ui->tw->item(i,j+d)->setBackground(brush1);
                }
            }

            if (progressivo==progressivoMax)
                progressivo= 1;  //il turno successivo saraà il progressivo 1 se il progressivo precedente era uguale al modulo
            else
                progressivo++;



        }
    }
}



FormGenerazioneTurno::~FormGenerazioneTurno()
{
    delete ui;
}


void FormGenerazioneTurno::slot_cambioIdMatrice( QString str)
{
    QModelIndexList selectedList = ui->tw->selectionModel()->selectedRows(); ///RIga seleziona della ui->tw
 //   for( int i=0; i<selectedList.count(); i++)
 //          QMessageBox::information(this,"", QString::number(selectedList.at(i).row()));

//    //combo box per la scelta del progressivo del turno da usare per la risorsa
//    QComboBox *pComboBox1 = new QComboBox();
//    QSqlQuery query2(QString("select progressivo from matriceTurni where IDMatrice=\"%1\"").arg(str));
//    query2.exec();
//    qDebug()<< query2.lastQuery();
//    while(query2.next())
//    {
//        pComboBox1->addItem(query2.value(0).toString());
//    }
//    ui->tw->setCellWidget(selectedList.at(0).row(),8,pComboBox1);



    QStringList strList = str.split(QRegExp(" "));
    QString TipoTurnoPrecedente= strList.at(0);
    QString progressivoTurnoSuccessivo= strList.at(1);
    QString turnosuccessivo;
    QSqlQuery query1;
    query1.exec(QString("select Lun, mar, mer, gio, ven, sab, dom from matriceTurni where IDMatrice=\"%1\" and progressivo=\"%2\"").arg(TipoTurnoPrecedente).arg(progressivoTurnoSuccessivo));
    query1.next();
    turnosuccessivo= QString("%1 %2 %3 %4 %5 %6 %7").arg(query1.value(0).toString())
                                                    .arg(query1.value(1).toString())
                                                    .arg(query1.value(2).toString())
                                                    .arg(query1.value(3).toString())
                                                    .arg(query1.value(4).toString())
                                                    .arg(query1.value(5).toString())
                                                    .arg(query1.value(6).toString());
     ui->tw->setItem(selectedList.at(0).row(),6,new QTableWidgetItem(QString("%1").arg(turnosuccessivo)));



     generaTurniSequenziali(1);
     ui->tw->resizeColumnsToContents();
     ui->tw->resizeRowsToContents();


}

void FormGenerazioneTurno::on_pbDataDal_clicked()
{
    FormCalendario *fCalendario = new FormCalendario("Generazione Turno dal ...");
    fCalendario->setAttribute(Qt::WA_DeleteOnClose);
    connect(fCalendario, SIGNAL(signal_data(QDate)),this,SLOT( slot_dataIniziale(QDate)));
    fCalendario->setWindowModality(Qt::ApplicationModal);
    fCalendario->setWindowFlags(Qt::Tool);
    fCalendario->show();
}

void  FormGenerazioneTurno::slot_dataIniziale(QDate data)
{
    if(data.dayOfWeek()!=1)
    {
        QMessageBox msgBox;
        msgBox.setText("La data di INIZIO deve essere un LUNEDI.");
        msgBox.setStandardButtons( QMessageBox::Close);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    {
        ui->dePermessiDal->setDate(data);
        ui->dePermessiAl->setDate(data);
        dataIniziale.setDate(data.year(),data.month(),data.day());
        dataFinale.setDate(data.year(),data.month(),data.day());
        qDebug() << dataIniziale.toString("dd/MM/yyyy");
        qDebug() << dataFinale.toString("dd/MM/yyyy");


         QFont font;
        ui->tw->setColumnCount(7 +dataIniziale.daysTo(dataFinale)+1);
        QDate comodo= dataIniziale;
        for(int j= 7; j < 7 +dataIniziale.daysTo(dataFinale)+1; j++, comodo= comodo.addDays(1))
        {
             ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM/yyyy"))));
             ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));
             ui->tw->item(0, j)->setFont(font);
             ui->tw->item(1, j)->setFont(font);
        }
        ui->tw->resizeColumnsToContents();
        ui->tw->resizeRowsToContents();


    }
}

void FormGenerazioneTurno::on_pbDataAl_clicked()
{
    FormCalendario *fCalendario = new FormCalendario("Generazione turno fino al ...");
    fCalendario->setAttribute(Qt::WA_DeleteOnClose);
    connect(fCalendario, SIGNAL(signal_data(QDate)),this,SLOT( slot_dataFinale(QDate)));
    fCalendario->setWindowModality(Qt::ApplicationModal);
    fCalendario->setWindowFlags(Qt::Tool);
    fCalendario->show();
}
void  FormGenerazioneTurno::slot_dataFinale(QDate data)
{

    if(data.dayOfWeek()!=7)
    {
        QMessageBox msgBox;
        msgBox.setText("La data di FINE deve essere una DOMENICA.");
        msgBox.setStandardButtons( QMessageBox::Close);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
    else
    {
        if  (data.operator <(ui->dePermessiDal->date()))
        {
            QMessageBox msgBox;

            msgBox.setText(QString("La data di fine del periodo di cui si vuole generare il turno non può essere antecedente a quella di inizio."));
            msgBox.setStandardButtons( QMessageBox::Cancel);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            ui->dePermessiAl->setDate( ui->dePermessiDal->date());
        }
        else
        {
            ui->dePermessiAl->setDate(data);


            dataFinale.setDate(data.year(),data.month(),data.day());
            qDebug() << dataFinale.toString("dd/MM/yyyy");


            ui->tw->setColumnCount(7 +dataIniziale.daysTo(dataFinale)+1);
            QDate comodo= dataIniziale;
             QFont font;
            for(int j= 7; j < 7 +dataIniziale.daysTo(dataFinale)+1; j++, comodo= comodo.addDays(1))
            {
                 ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM/yyyy"))));
                 ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));
                 ui->tw->item(0, j)->setFont(font);
                 ui->tw->item(1, j)->setFont(font);
            }
            ui->tw->resizeColumnsToContents();
            ui->tw->resizeRowsToContents();
        }


    }
}


int FormGenerazioneTurno::similitudineTurni(QString turnoSeme, QString turnoPrecedente)
{
    int similitudine=0;

   /// qDebug()<< "TurnoSeme: "<< turnoSeme<< "    TurnoPrec: "<< turnoPrecedente;
    QStringList str, str1;
    str = turnoSeme.split(QRegExp(" "));
    str1 = turnoPrecedente.split(QRegExp(" "));
   /// qDebug() << "Str cont: " << str.count();
   /// for (int i=0; i < str.count(); i++)
    for (int i=0; i < (str.count() -1); i++)
    {
     //    qDebug() << str.at(i);
     //    qDebug() << str1.at(i);
         if ( (str.at(i) == str1.at(i)) ||  (str1.at(i) =="F") ||
              ((str.at(i) == "M") && (str1.at(i) == "P")   ) ||
              ((str.at(i) == "P") && (str1.at(i) == "M")   ) ||
              ((str.at(i) == "M1") && (str1.at(i) == "P1") ) ||
              ((str.at(i) == "M2") && (str1.at(i) == "P2") ) ||
              ((str.at(i) == "P1") && (str1.at(i) == "M1") ) ||
              ((str.at(i) == "P2") && (str1.at(i) == "M2") ) )
             similitudine++;
         else
             similitudine--;
         if ( (str.at(i) == "N") && ( str1.at(i) =="N")  )
             similitudine +=10;
         if ( ((str.at(i) == "N") && ( str1.at(i) !="N")) ||
              ((str.at(i) != "N") && ( str1.at(i) =="N")) )
             similitudine -=10;
         if ( (str.at(i) == "S") && ( str1.at(i) =="S")  )
             similitudine +=10;
       ///  qDebug() << similitudine << str.at(i) << str1.at(i) ;
    }

    ///for (int i=str.count()-1; ((i >= 0) && (str.at(i)!="R") ) ; i--)
    for (int i=str.count()-2; ((i >= 0)  ) ; i--)
    {
        if ( (str.at(i) == "R") && ( str1.at(i) =="R")  )
            similitudine +=10;

      ///  qDebug() << "cerca R " << similitudine << str.at(i) << str1.at(i) ;
    }

   ///do minor peso al turnoSeme con R > al turnoPrecedente
    int giornoRNelTurnoSeme, giornoRNelTurnoSettimanaPrecedente;
    for (int i=str.count()-2; ((i >= 0)  ) ; i--)
    {
        if ( (str.at(i) == "R") )
            giornoRNelTurnoSeme= i;
        if ( ( str1.at(i) =="R")  )
            giornoRNelTurnoSettimanaPrecedente=i;
    }
    if (giornoRNelTurnoSeme > giornoRNelTurnoSettimanaPrecedente)
        similitudine -=5;


/*
 ///    qDebug() << QString("posizione N in turnoPrec: %1").arg(turnoPrecedente.indexOf('N'));
 ///    qDebug() << QString("posizione N in turnoSeme: %1").arg(turnoSeme.indexOf('N'));
     if(turnoPrecedente.indexOf('N')==turnoSeme.indexOf('N'))
         similitudine= 100;

 ///    qDebug() << QString("posizione S in turnoPrec: %1").arg(turnoPrecedente.indexOf('S'));
 ///    qDebug() << QString("posizione S in turnoSeme: %1").arg(turnoSeme.indexOf('S'));
     if(turnoPrecedente.indexOf('S')==turnoSeme.indexOf('S'))
         similitudine= 100;

//     qDebug() << QString("posizione R in turnoPrec: %1").arg(turnoPrecedente.indexOf('R'));
//     qDebug() << QString("posizione R in turnoSeme: %1").arg(turnoSeme.indexOf('R'));
//     if(turnoPrecedente.indexOf('R')==turnoSeme.indexOf('R'))
//         similitudine++;

     qDebug() << QString("posizione R in turnoPrec: %1").arg(turnoPrecedente.lastIndexOf( 'R'));
     qDebug() << QString("posizione R in turnoSeme: %1").arg(turnoSeme.lastIndexOf('R'));
     if(turnoPrecedente.lastIndexOf('R') ==turnoSeme.lastIndexOf('R'))
         similitudine += 10;
     if(turnoPrecedente.lastIndexOf('R') > turnoSeme.lastIndexOf('R'))
         similitudine ++;

     */

     ///qDebug() << "Similitudine: "<<similitudine;
     return similitudine;
}


///////////////////////////////// //ritorna il turno di nSettimanePrecedenti
QString FormGenerazioneTurno::turnoPrecedente(QString matricola, int nSettPrecedenti, QString *IDMatrice, int *progressivo)
{
    QString turno;
    for(int j= (-(7*(nSettPrecedenti-1))-7);j <= (-(7*(nSettPrecedenti-1))-1) ; j++)
    {
        QSqlQuery query(QString(" select turno,IDMatrice, Progressivo from turno where matricola=\"%1\" and data=\"%2\"").arg(matricola).arg(dataIniziale.addDays(j).toString("dd/MM/yyyy")));
        query.exec();
        if(query.next())
        {
            turno.append(QString("%1 ").arg(query.value(0).toString()));
            *IDMatrice= query.value(1).toString();
            *progressivo= query.value(2).toInt();
        }
        else
        {
          turno="";
          *IDMatrice="";
          *progressivo= 0;
        }

    }
    ///qDebug() << QString("TurnoSettimana -%1: %2").arg(nSettPrecedenti).arg(turno);
    return turno;
}



void FormGenerazioneTurno::on_pbTurnoPrecedente_clicked()
{
    for(int i=2; i < numeroRisorse+2; i++)
         ui->tw->setItem(i,5,new QTableWidgetItem( "."));


    ///  Ricava dal database matriceTurni; inizializza il bool "allocazioni" per permettere di scegliere un turno univoco per risorsa
    QSqlQuery querymatriceTurni(QString("select * from matriceTurni"));
    querymatriceTurni.exec();
    while(querymatriceTurni.next())
    {
        allocazioneTurniBase alTurniBase_i;

        alTurniBase_i.Idturno= querymatriceTurni.value(0).toString();
        alTurniBase_i.Progressivo=  querymatriceTurni.value(1).toString();
        for (int l=0; l<7; l++)
                alTurniBase_i.turnoSeme.append((QString("%1 ").arg(querymatriceTurni.value(l+2).toString())));
        alTurniBase_i.allocato= 0;
        this->alTurniBase.append(alTurniBase_i);
    }







    //for (int k; k < this->alTurniBase.size(); k++)
    //    qDebug() << this->alTurniBase.at(k).Idturno+" "+this->alTurniBase.at(k).Progressivo+" "+this->alTurniBase.at(k).turnoSeme+" "+QString("%1").arg(this->alTurniBase.at(k).allocato);



    ///numero di TURNI nella matriceTurni
    int numTurniBaseOSA1=0;
    QSqlQuery query2(QString("select * from matriceTurni"));
//    QSqlQuery query2(QString("select * from matriceTurni where IdMatrice=\"OSA1\""));
    query2.exec();
    while(query2.next())
    {
        numTurniBaseOSA1++;

    }

//    QByteArray turniBaseScelti;             //gestisce i turni base gia scelti (ogni turno base deve essere occupato da una risorsa)
//    turniBaseScelti.resize(numTurniBaseOSA1);
//    turniBaseScelti.clear();

//    qDebug() << QString("TurniBase Osa1: %1").arg( numTurniBaseOSA1 );

//    ///numero di TURNI nella matriceTurni
//    int numTurniBaseOSA2=0;
//    QSqlQuery query3(QString("select * from matriceTurni where IdMatrice=\"OSA2\""));
//    query3.exec();
//    while(query3.next())
//        numTurniBaseOSA2++;
//    qDebug() << QString("TurniBase Osa2: %1").arg( numTurniBaseOSA2 );


    QString Progressivo;
    QString IdMatrice;
    QString turnoPrecedente;///stringa che contiene il turno SEME


     QList<int> turnoAllocato;
     for(int t=0; t<100;t++) turnoAllocato.append(0);

    for(int i=2; (i < numeroRisorse+2 )  ; i++)
    {
        QComboBox *pComboBoxTBase = new QComboBox();
        ui->tw->setCellWidget(i,5,pComboBoxTBase);
        pComboBoxTBase->setInsertPolicy(QComboBox::InsertAtTop);
        //pComboBoxTBase= ( QComboBox * )ui->tw->cellWidget(i,6);

        QComboBox *pComboBox = new QComboBox();
        pComboBox= ( QComboBox * )ui->tw->cellWidget(i,4);
        QString IDMatriceScelta= pComboBox->currentText();


        QCheckBox *pCheckBox = new QCheckBox();
        pCheckBox= (QCheckBox *) ui->tw->cellWidget(i,3);



        if (pCheckBox->isChecked())
        {
            ///Ricavo l'IDMax del tipo di turno scelto per la risorsa  (ad esempio OSA3 idmax= 23)
             int IDMax= 0;
             QSqlQuery queryIDmax(QString("select distinct PROGRESSIVO from matriceTurni where IdMatrice=\"%1\"").arg(IDMatriceScelta));
             queryIDmax.exec();
             while(queryIDmax.next())
             {
                 IDMax++;
               //  turnoAllocato.append(0);
             }

             qDebug() << "Turno allocato "<< turnoAllocato;

             ///Calcolo la similitudine tra i turni precedenti e i possibili turni del tipo di quello scelto per la risorsa
             QString turni4SettimanePrecedenti[4];
             QList<int> similitudineNturniPrecedenti[4];
             QList<int> IdTurniPrecedentiPerSimilitudine[4];
             int ProgressivoIpotesi= 0;
             //for(int cont= 0; cont < 4; cont ++)
             //{
                int cont=0;
              //  turni4SettimanePrecedenti[cont]= this->turnoPrecedente(ui->tw->item(i,0)->text(), cont + 1);
                 if (turni4SettimanePrecedenti[cont] !="")
                 {
                     similitudineNturniPrecedenti[cont].clear();
                     QString turnoDaMatriceOSA;

                     QSqlQuery queryPossibiliTurni(QString("select * from matriceTurni where IdMatrice=\"%1\"").arg(IDMatriceScelta));
                     queryPossibiliTurni.exec();
                     while(queryPossibiliTurni.next())
                     {
                         IdMatrice=  queryPossibiliTurni.value(0).toString();
                         Progressivo=  queryPossibiliTurni.value(1).toString();
                         turnoDaMatriceOSA.clear();
                         for (int l=0; l<7; l++)
                             turnoDaMatriceOSA.append((QString("%1 ").arg(queryPossibiliTurni.value(l+2).toString())));

                         int simil= similitudineTurni(turnoDaMatriceOSA, turni4SettimanePrecedenti[cont]);
                         if (  similitudineNturniPrecedenti[cont].last() <= simil)
                         {
                             similitudineNturniPrecedenti[cont].append(simil);
                             IdTurniPrecedentiPerSimilitudine[cont].append(Progressivo.toInt());
                             if ((cont==0) && (turnoAllocato.operator [](Progressivo.toInt()-1))== 0)
                             {
                                 ProgressivoIpotesi= Progressivo.toInt();
                                 pComboBoxTBase->addItem( QString("%1 %2 %3").arg(IdMatrice).arg(IdTurniPrecedentiPerSimilitudine[cont].last()).arg(simil));
                                 turnoAllocato.operator [](Progressivo.toInt() -1)= 1;

                                 break;
                             }
                            // else
                            //       turnoAllocato.operator [](Progressivo.toInt())= 0;
                         }

                     }
                 }
             //}


             qDebug() << "Turno allocato "<< turnoAllocato;


             pComboBoxTBase->setCurrentIndex(pComboBoxTBase->count()-1);

             qDebug()<< QString("IdMatrice: %1 ProgressivoMax: %2").arg(IDMatriceScelta).arg(IDMax);
             qDebug()<< QString("Turni precedenti: %1 || %2 || %3 || %4" ).arg(turni4SettimanePrecedenti[3]).arg(turni4SettimanePrecedenti[2]).arg(turni4SettimanePrecedenti[1]).arg(turni4SettimanePrecedenti[0]);
             ///qDebug()<< QString("IdTurniPrecedentiPerSimilitudine %1: %2 || %3 || %4 || %5" ).arg(IDMatriceScelta).arg(IdTurniPrecedentiPerSimilitudine[3].last()).arg(IdTurniPrecedentiPerSimilitudine[2].last()).arg(IdTurniPrecedentiPerSimilitudine[1].last()).arg(IdTurniPrecedentiPerSimilitudine[0].last());
             ///qDebug()<< QString("Similitudini %1: %2 || %3 || %4 || %5" ).arg(IDMatriceScelta).arg(similitudineNturniPrecedenti[3].last()).arg(similitudineNturniPrecedenti[2].last()).arg(similitudineNturniPrecedenti[1].last()).arg(similitudineNturniPrecedenti[0].last());


             //for (int n=0 ; n<4 ; n++)
                for (int m= 0 ; m < IdTurniPrecedentiPerSimilitudine[0].size(); m++)
                {
                    qDebug()<< QString("TurnoP: %1 || Simil: %2" ).arg(IdTurniPrecedentiPerSimilitudine[0].operator [](m)).arg(similitudineNturniPrecedenti[0].operator [](m));
                }

             ui->tw->setItem(i,6,new QTableWidgetItem( turni4SettimanePrecedenti[0]));





 //        qDebug() << QString("turnoPPPP: %1 turnoPPP: %2 turnoPP: %3  turnoP: %4").arg(ProgressivoPPPP).arg(ProgressivoPPP).arg(ProgressivoPP).arg(ProgressivoP);
     //        qDebug() << QString("simil_maxPPPP: %1  simil_maxPPP: %2  simil_maxPP: %3  simil_maxP: %4").arg(simil_maxPPPP).arg(simil_maxPPP).arg(simil_maxPP).arg(simil_maxP);



     /*

            ////  CALCOLO PER SIMILITUDINE DELL'ID (MATRICE E ID) DEL TURNO PRECEDENTE
           // QString turnoSeme;
            if (pCheckBox->isChecked() && (turnoPrecedente!="") )
            {
                //  if (IDMatriceScelta=="OSA1")
                //  {

                int simil= 0, simil_max= 0, similP= 0, simil_maxP= 0, ProgressivoP= 0, similPP= 0, simil_maxPP= 0, ProgressivoPP= 0, similPPP= 0, simil_maxPPP= 0, ProgressivoPPP= 0,tbase=0;
                int similPPPP= 0, simil_maxPPPP= 0, ProgressivoPPPP= 0;


                query2.seek(0);
                for (int j=0; (j < numTurniBaseOSA1)  ;j++ )
                {
                    IdMatrice=  query2.value(0).toString();
                    Progressivo=  query2.value(1).toString();
                    turnoSeme.clear();
                    for (int l=0; l<7; l++)
                        turnoSeme.append((QString("%1 ").arg(query2.value(l+2).toString())));
                    query2.next();

                    if (IDMatriceScelta == IdMatrice) ///la similitudine viene calcolata tra i possibili ID con MATRICE uguale a quella scelta nel comboBox
                    {
                        /// qDebug() << "SEME: " <<j+1 <<" "<< IdMatrice<<" "<<Progressivo<<" "<<turnoSeme;

                        ///SIMILITUDINE SETTIMANA -3
                        similPPPP= similitudineTurni(turnoSeme, turnoPrecedentePrecedentePrecedentePrecedente);
                        if ( similPPPP > simil_maxPPPP)
                        {
                            simil_maxPPPP= similPPPP;
                            ///qDebug() << QString("Similitudine %1 %2 = %3").arg(turnoSeme).arg(turnoPrecedentePrecedentePrecedente).arg(simil_maxPPP);
                            //qDebug() << QString("Mat scelta %1  Mat %2").arg(IDMatriceScelta).arg(IdMatrice);
                            //ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
                            //ui->tw->setItem(i,5,new QTableWidgetItem( IdMatrice+" "+Progressivo));
                            ProgressivoPPPP= Progressivo.toInt();

                            ///  qDebug() << QString("turnoPPP individuato: %1 %2").arg(IdMatrice).arg(ProgressivoPPP);
                        }
                    }
                }




            query2.seek(0);
            for (int j=0; (j < numTurniBaseOSA1)  ;j++ )
            {
                IdMatrice=  query2.value(0).toString();
                Progressivo=  query2.value(1).toString();
                turnoSeme.clear();
                for (int l=0; l<7; l++)
                    turnoSeme.append((QString("%1 ").arg(query2.value(l+2).toString())));
                query2.next();

                if (IDMatriceScelta == IdMatrice) ///la similitudine viene calcolata tra i possibili ID con MATRICE uguale a quella scelta nel comboBox
                {
                    /// qDebug() << "SEME: " <<j+1 <<" "<< IdMatrice<<" "<<Progressivo<<" "<<turnoSeme;

                    ///SIMILITUDINE SETTIMANA -3
                    similPPP= similitudineTurni(turnoSeme, turnoPrecedentePrecedentePrecedente);
                    if ( similPPP > simil_maxPPP)
                    {
                        simil_maxPPP= similPPP;
                        ///qDebug() << QString("Similitudine %1 %2 = %3").arg(turnoSeme).arg(turnoPrecedentePrecedentePrecedente).arg(simil_maxPPP);
                        //qDebug() << QString("Mat scelta %1  Mat %2").arg(IDMatriceScelta).arg(IdMatrice);
                        //ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
                        //ui->tw->setItem(i,5,new QTableWidgetItem( IdMatrice+" "+Progressivo));
                        ProgressivoPPP= Progressivo.toInt();

                      ///  qDebug() << QString("turnoPPP individuato: %1 %2").arg(IdMatrice).arg(ProgressivoPPP);
                    }
                }
            }

            query2.seek(0);
            for (int j=0; (j < numTurniBaseOSA1)  ;j++ )
            {
                IdMatrice=  query2.value(0).toString();
                Progressivo=  query2.value(1).toString();
                turnoSeme.clear();
                for (int l=0; l<7; l++)
                    turnoSeme.append((QString("%1 ").arg(query2.value(l+2).toString())));
                query2.next();

                if (IDMatriceScelta == IdMatrice) ///la similitudine viene calcolata tra i possibili ID con MATRICE uguale a quella scelta nel comboBox
                {
                    /// qDebug() << "SEME: " <<j+1 <<" "<< IdMatrice<<" "<<Progressivo<<" "<<turnoSeme;

                    ///SIMILITUDINE SETTIMANA -2
                    similPP= similitudineTurni(turnoSeme, turnoPrecedentePrecedente);
                    if ( similPP > simil_maxPP)
                    {
                        simil_maxPP= similPP;
                        ///qDebug() << QString("Similitudine %1 %2 = %3").arg(turnoSeme).arg(turnoPrecedentePrecedente).arg(simil_maxPP);
                        //qDebug() << QString("Mat scelta %1  Mat %2").arg(IDMatriceScelta).arg(IdMatrice);
                        //ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
                        //ui->tw->setItem(i,5,new QTableWidgetItem( IdMatrice+" "+Progressivo));
                        ProgressivoPP= Progressivo.toInt();

                       /// qDebug() << QString("turnoPP individuato: %1 %2").arg(IdMatrice).arg(ProgressivoPP);
                    }
                }
            }



            query2.seek(0);
            for (int j=0; (j < numTurniBaseOSA1)  ;j++ )
            {
                   IdMatrice=  query2.value(0).toString();
                    Progressivo=  query2.value(1).toString();
                    turnoSeme.clear();
                    for (int l=0; l<7; l++)
                        turnoSeme.append((QString("%1 ").arg(query2.value(l+2).toString())));
                    query2.next();
                    if (!(this->alTurniBase.at(j).allocato))
                    {

                        if (IDMatriceScelta == IdMatrice) ///la similitudine viene calcolata tra i possibili ID con MATRICE uguale a quella scelta nel comboBox
                        {
                            /// qDebug() << "SEME: " <<j+1 <<" "<< IdMatrice<<" "<<Progressivo<<" "<<turnoSeme;

                            ///SIMILITUDINE SETTIMANA -1
                            similP= similitudineTurni(turnoSeme, turnoPrecedente);
                            if ( similP > simil_maxP)
                            {
                                simil_maxP= similP;
                                ///qDebug() << QString("Similitudine %1 %2 = %3").arg(turnoSeme).arg(turnoPrecedente).arg(simil_maxP);
                                ///qDebug() << QString("Mat scelta %1  Mat %2").arg(IDMatriceScelta).arg(IdMatrice);
                                ///ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
                                ///ui->tw->setItem(i,5,new QTableWidgetItem( IdMatrice+" "+Progressivo));
                                ProgressivoP= Progressivo.toInt();

                                ///qDebug() << QString("turnoP individuato: %1 %2").arg(IdMatrice).arg(ProgressivoP);
                            }

                        }
                    }
            }



             ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
//            ui->tw->setItem(i,5,new QTableWidgetItem( QString("%1 %2").arg(IdMatrice).arg(ProgressivoP)) );
//            turniBaseScelti.operator [](i-2)= 1;




            if (  ((ProgressivoP == (ProgressivoPP + 1)) && (ProgressivoP == (ProgressivoPPP + 2)) && (ProgressivoP == (ProgressivoPPP + 3)) ) )
            {
               // ui->tw->setItem(i,5,new QTableWidgetItem( QString("%1 %2").arg(IdMatrice).arg(ProgressivoP)) );
                pComboBoxTBase->addItem( QString("%1 %2").arg(IdMatrice).arg(ProgressivoP));
                this->alTurniBase.operator [](ProgressivoP).allocato= 1;

            }
            if (  (ProgressivoP != 1) && ((ProgressivoPPP == (ProgressivoPPPP + 1)) && (ProgressivoPP == (ProgressivoPPPP + 2)) && (ProgressivoPP == (ProgressivoPPP + 1)) ) )
            {
                // ui->tw->setItem(i,5,new QTableWidgetItem( QString("%1 %2").arg(IdMatrice).arg(ProgressivoP)) );
                pComboBoxTBase->addItem( QString("Ipotesi: %1 %2").arg(IdMatrice).arg(ProgressivoPP + 1));
                this->alTurniBase.operator [](ProgressivoPP + 1).allocato= 1;

            }

            if ((ProgressivoP == (ProgressivoPP + 1)) && (ProgressivoP > (ProgressivoPPP)) )
            {
                 pComboBoxTBase->addItem( QString("Ipotesi_1: %1 %2").arg(IdMatrice).arg(ProgressivoP));
                   this->alTurniBase.operator [](ProgressivoP).allocato= 1;
            }
            if (  ((ProgressivoP == (ProgressivoPP + 1))  ) )
            {
                 pComboBoxTBase->addItem( QString("Ipotesi_2: %1 %2").arg(IdMatrice).arg(ProgressivoP));
                   this->alTurniBase.operator [](ProgressivoP).allocato= 1;
            }
            if ((ProgressivoP != 1) && (ProgressivoPP == (ProgressivoPPP + 1))   )
            {
                //ui->tw->setItem(i,5,new QTableWidgetItem( QString("Ipotesei_1: %1 %2").arg(IdMatrice).arg(ProgressivoPP + 1)) );
                pComboBoxTBase->addItem(QString("Ipotesi_3: %1 %2").arg(IdMatrice).arg(ProgressivoPP + 1));
                  this->alTurniBase.operator [](ProgressivoPP + 1).allocato= 1;
            }
            if ((ProgressivoP == (ProgressivoPPP + 2)) && (ProgressivoPP <ProgressivoPPP )  )
            {
                //ui->tw->setItem(i,5,new QTableWidgetItem( QString("Ipotesei_1: %1 %2").arg(IdMatrice).arg(ProgressivoPP + 1)) );
                pComboBoxTBase->addItem(QString("Ipotesi_4: %1 %2").arg(IdMatrice).arg(ProgressivoP));
                this->alTurniBase.operator [](ProgressivoP).allocato= 1;
            }
            if ((ProgressivoP == 1) && (ProgressivoPP ==(ProgressivoPPP +1))  )
            {
                //ui->tw->setItem(i,5,new QTableWidgetItem( QString("Ipotesei_1: %1 %2").arg(IdMatrice).arg(ProgressivoPP + 1)) );
                pComboBoxTBase->addItem(QString("Ipotesi_5: %1 %2").arg(IdMatrice).arg(ProgressivoP));
                this->alTurniBase.operator [](ProgressivoP).allocato= 1;
            }
            if ((ProgressivoP == (ProgressivoPPP +2) ) && (ProgressivoPP >ProgressivoP )  )
            {
                //ui->tw->setItem(i,5,new QTableWidgetItem( QString("Ipotesei_1: %1 %2").arg(IdMatrice).arg(ProgressivoPP + 1)) );
                pComboBoxTBase->addItem(QString("Ipotesi_6: %1 %2").arg(IdMatrice).arg(ProgressivoP));
                this->alTurniBase.operator [](ProgressivoP).allocato= 1;
            }

                //ui->tw->setItem(i,5,new QTableWidgetItem( QString("FORSE: %1 %2").arg(IdMatrice).arg(ProgressivoP)) );
              //  pComboBoxTBase->addItem( QString("FORSE: %1 %2").arg(IdMatrice).arg(ProgressivoP));


            qDebug() << QString("turnoPPPP: %1 turnoPPP: %2 turnoPP: %3  turnoP: %4").arg(ProgressivoPPPP).arg(ProgressivoPPP).arg(ProgressivoPP).arg(ProgressivoP);
            qDebug() << QString("simil_maxPPPP: %1  simil_maxPPP: %2  simil_maxPP: %3  simil_maxP: %4").arg(simil_maxPPPP).arg(simil_maxPPP).arg(simil_maxPP).arg(simil_maxP);


            //  }
        }
        */
        }/// FINE IF la risorsa e' checked
        else
        {
            ui->tw->setItem(i,6,new QTableWidgetItem("-"));
            pComboBoxTBase->addItem("-");
        }

        // qDebug() << QString("%1%2%3%4").arg(turniBaseScelti.at(0)).arg(turniBaseScelti.at(1)).arg(turniBaseScelti.at(2)).arg(turniBaseScelti.at(3));

    }///  FINE CICLO FOR SULLE RISORSE



/*



    QString turnoPrecedente;///stringa che contiene il turno SEME

    ///numero di TURNI nella matriceTurni
    int numTurniBase=0;
    QSqlQuery query2(QString("select * from matriceTurni"));
    query2.exec();
    while(query2.next())
        numTurniBase++;
    qDebug() << QString("TurniBase: %1").arg( numTurniBase );

//    qDebug() << QString("Numero risorse: %1").arg(numeroRisorse);
//    for(int i=2; i < numeroRisorse+2; i++)
//    {

//        turnoPrecedente.clear();
//        //Ritrovo per ogni risorsa il turno della settimana precedente
//        for(int j= -7;j <= -1; j++)
//        {
//            QSqlQuery query1(QString(" select turno from turno where matricola=\"%1\" and data=\"%2\"").arg(ui->tw->item(i,0)->text()).arg(dataIniziale.addDays(j).toString("dd/MM/yyyy")));
//            query1.exec();
//            ///qDebug() << query1.executedQuery();
//            if(query1.next())
//            {
//                ///qDebug() <<   query1.value(0).toString();
//                turnoPrecedente.append(QString("%1 ").arg(query1.value(0).toString()));
//                //ui->tw->setItem(i,6,new QTableWidgetItem( query1.value(0).toString()));
//                //      pComboBox->addItem(query1.value(0).toString());
//            }
//            qDebug() << turnoPrecedente;
//            ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
//        }



      //  turnoPrecedente= "R M M R N S R ";
      //  turnoPrecedente= "M1 P1 P1 R R P1 M1 ";
      //  turnoPrecedente= "104 M N S R P P ";
      //  ui->tw->setItem(2,6,new QTableWidgetItem( turnoPrecedente));

        ///determino usando la matriceTurni l'ID del turno che piu' si avvicina a quello della settimana SEME
        query2.seek(0);
        int simil=0, tbase=0;
        QString tbaseStr="";
        QString id;
        //for(int k=0; k < numTurniBase; k++)
        for(int k=0; k < 1; k++)
        {
               QString IdMatrice=  query2.value(0).toString();
               QString Progressivo=  query2.value(1).toString();
               QString turnoSeme;
               for (int l=0; l<7; l++)
                   turnoSeme.append((QString("%1 ").arg(query2.value(l+2).toString())));
               query2.next();
               qDebug() << "SEME: " <<k+1 <<" "<< IdMatrice<<" "<<Progressivo<<" "<<turnoSeme;

               tbaseStr="";


               //for(int i=2; i < numeroRisorse+2; i++)
               for(int i=2;( i < (4+2) ); i++)
               {

                   ///verifico il turno piu' simile solo tra quelli con ID uguale a quello scelto nel combo della risorsa (OSA2, OSA2 ecc)
                   QComboBox *pComboBox = new QComboBox();
                   pComboBox= (QComboBox *) ui->tw->cellWidget(i, 4);
                   QString matriceSceltaPerLaRisorsa= pComboBox->currentText();
                   ///qDebug()<< matriceSceltaPerLaRisorsa;
                   ///qDebug() << IdMatrice;
                   if (matriceSceltaPerLaRisorsa != IdMatrice)
                           return;

                //   if ( ui->tw->item(i, 5)->text() !="." )
                //       return;

                   turnoPrecedente.clear();
                   //Ritrovo per ogni risorsa il turno della settimana precedente
                   for(int j= -7;j <= -1; j++)
                   {
                       QSqlQuery query1(QString(" select turno from turno where matricola=\"%1\" and data=\"%2\"").arg(ui->tw->item(i,0)->text()).arg(dataIniziale.addDays(j).toString("dd/MM/yyyy")));
                       query1.exec();
                       ///qDebug() << query1.executedQuery();
                       if(query1.next())
                       {
                           ///qDebug() <<   query1.value(0).toString();
                           turnoPrecedente.append(QString("%1 ").arg(query1.value(0).toString()));
                           //ui->tw->setItem(i,6,new QTableWidgetItem( query1.value(0).toString()));
                           //      pComboBox->addItem(query1.value(0).toString());
                       }
                      /// qDebug() << turnoPrecedente;
                       ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
                   }
                   /// determina la similitudine tra turnoSeme e turnoPrecedente
                   simil= similitudineTurni(turnoSeme, turnoPrecedente);

                   if (simil > tbase)
                   {
                       tbase= simil;
                       tbaseStr= Progressivo;
                       id= IdMatrice;
                       ui->tw->setItem(i,5,new QTableWidgetItem(QString("%1 %2").arg(id).arg(tbaseStr)));
                   }


               }

               qDebug() << "simMax "<<tbase<< " tbasestr " << tbaseStr << " prog  "<< tbaseStr;


        }

  //  }

*/
   ui->tw->resizeColumnsToContents();
   ui->tw->resizeRowsToContents();





}

void FormGenerazioneTurno::on_cbMese_currentIndexChanged(int index)
{
//    QDate inizioMese, fineMese;
//    inizioMese.setDate(ui->cbAnno->currentIndex()+2015, ui->cbMese->currentIndex()+1 ,1);
//     qDebug() << inizioMese.toString("dd/MM/yyyy");
//    while (inizioMese.dayOfWeek()!=1)
//      inizioMese=  inizioMese.addDays(1);
//    qDebug() <<  inizioMese.dayOfWeek();
//    qDebug() << inizioMese.toString("dd/MM/yyyy");
 //   QFont font;
 //   font.setBold(true);

    dataIniziale.setDate(ui->cbAnno->currentIndex()+2015, ui->cbMese->currentIndex()+1 ,1);
    dataFinale.setDate(ui->cbAnno->currentIndex()+2015, ui->cbMese->currentIndex()+1 , dataIniziale.daysInMonth() );
    while (dataIniziale.dayOfWeek()!=1)  ///PRIMO LUNEDI DEL MESE CORRENTE
      dataIniziale=  dataIniziale.addDays(1);
    ui->dePermessiDal->setDate(dataIniziale);

    while (dataFinale.dayOfWeek()!=7)  ///ULTIMA DOMENICA DEL MESE CORRENTE OPPURE PRIMA DOMENICA DEL MESE SUCCESSIVO
      dataFinale=  dataFinale.addDays(1);
    ui->dePermessiAl->setDate(dataFinale);

    ui->tw->setColumnCount(7 +dataIniziale.daysTo(dataFinale)+1);
    QDate comodo= dataIniziale;

    for(int j= 7; j < 7 +dataIniziale.daysTo(dataFinale)+1; j++, comodo= comodo.addDays(1))
    {
         ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM/yyyy"))));
         ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));
        // ui->tw->item(0, j)->setFont(font);
        // ui->tw->item(1, j)->setFont(font);
    }


     popolaLaTabella_tw();
      generaTurniSequenziali(0);

    ui->tw->resizeColumnsToContents();
    ui->tw->resizeRowsToContents();


}

void FormGenerazioneTurno::on_cbAnno_currentIndexChanged(int index)
{    
    dataIniziale.setDate(ui->cbAnno->currentIndex()+2015, ui->cbMese->currentIndex()+1 ,1);
    dataFinale.setDate(ui->cbAnno->currentIndex()+2015, ui->cbMese->currentIndex()+1 , dataIniziale.daysInMonth() );
    while (dataIniziale.dayOfWeek()!=1)  ///PRIMO LUNEDI DEL MESE CORRENTE
      dataIniziale=  dataIniziale.addDays(1);
    ui->dePermessiDal->setDate(dataIniziale);

    while (dataFinale.dayOfWeek()!=7)  ///ULTIMA DOMENICA DEL MESE CORRENTE OPPURE PRIMA DOMENICA DEL MESE SUCCESSIVO
      dataFinale=  dataFinale.addDays(1);
    ui->dePermessiAl->setDate(dataFinale);

    ui->tw->setColumnCount(7 +dataIniziale.daysTo(dataFinale)+1);
    QDate comodo= dataIniziale;

    for(int j= 7; j < 7 +dataIniziale.daysTo(dataFinale)+1; j++, comodo= comodo.addDays(1))
    {
         ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM/yyyy"))));
         ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));
       //  ui->tw->item(0, j)->setFont(font);
       //  ui->tw->item(1, j)->setFont(font);
    }


     popolaLaTabella_tw();
     generaTurniSequenziali(0);


    ui->tw->resizeColumnsToContents();
    ui->tw->resizeRowsToContents();

}



////  Funzione di overload dell'operatore <() per il sorting della lista di oggetti
bool allocazioneTurniBaseSimilitudine::operator<(const allocazioneTurniBaseSimilitudine &other) const
{
    return simil > other.simil;
}




void FormGenerazioneTurno::slot_checkDoppioniAssociazioniTurnoBase()
{
    QStringList turniBaseAssegnati;  ///ID e Progressivo ad esempio OSA3 2
    QComboBox *pComboBox = new QComboBox();
    QStringList str;
    for(int i=2; (i < numeroRisorse+2 )  ; i++)
    {
        pComboBox= ( QComboBox * )ui->tw->cellWidget(i,5);

        str = pComboBox->currentText().split(QRegExp("---"));
        qDebug() << str.at(0) <<" " << str.at(1); ///str.at(0) contiene idmatrice e progressivo del turno, ad esempio OSA3 2
        turniBaseAssegnati.append(str.at(0));
    }

    //qDebug() << turniBaseAssegnati;

    for (int i=0; i < turniBaseAssegnati.count(); i++)
    {
        //qDebug() << turniBaseAssegnati.at(i)<< " "<< turniBaseAssegnati.count(turniBaseAssegnati.at(i));
        QComboBox *pComboBoxTBase = new QComboBox();
        pComboBoxTBase= ( QComboBox * )ui->tw->cellWidget(i+2,5); ///la prima riga nella tw che contiene il prima persona e' la 2!!!
        QPalette palette = pComboBoxTBase->palette();
        palette.setColor(QPalette::Text, (turniBaseAssegnati.count(turniBaseAssegnati.at(i))) > 1 ? Qt::red : Qt::black);
        pComboBoxTBase->setPalette(palette);               
    }

    ///Ricavo quali idMatrici non sono stati coperti a causa di doppioni (ogni turno deve avere una risorsa allocata)

    ///Ricavo l'IDMax del tipo di turno scelto per la risorsa  (ad esempio OSA3 idmax= 23)
//     int IDMax= 0;
//     QSqlQuery queryIDmax(QString("select distinct PROGRESSIVO from matriceTurni where IdMatrice=\"%1\"").arg(IDMatriceScelta));
//     queryIDmax.exec();
//     while(queryIDmax.next())
//     {
//         IDMax++;
//     }


}

void FormGenerazioneTurno::on_pbTurnoPrecedente2_clicked()
{

    this->setCursor(Qt::WaitCursor);


    for(int i=2; (i < numeroRisorse+2 )  ; i++)
    {
        ui->tw->setItem(i,5,new QTableWidgetItem(""));
        ui->tw->setItem(i,6,new QTableWidgetItem(""));
    }



    // Per ogni turno definito nella matriceTurni verifica l'allocazione.
    // Estratto il turno lo si confronta con il turno precedente della risorsa (la risorsa deve essere selezionata e con matriceScelta uguale a quella della matriceTurno es OSA_3 con OSA_3)
    // Viene creata una lista ordinata per similitudine e si alloca la risorsa che ha il maggior grado di similitudine, questa risorsa ALLOCA un turno
    QString IdMatrice, Progressivo;

    QList<allocazioneTurniBaseSimilitudine> listaSimilitudineMigliori;
//    allocazioneTurniBaseSimilitudine l;
//    l.simil= 0;
//    l.risorsa= 0;
//    listaSimilitudineMigliori.prepend(l);

    QSqlQuery querymatriceTurni(QString("select * from matriceTurni"));
    querymatriceTurni.exec();
    while(querymatriceTurni.next())
    {
        IdMatrice=  querymatriceTurni.value(0).toString();
        Progressivo=  querymatriceTurni.value(1).toString();
        QString turnoDaMatriceOSA;
        turnoDaMatriceOSA.clear();
        for (int l=0; l<7; l++)
            turnoDaMatriceOSA.append((QString("%1 ").arg(querymatriceTurni.value(l+2).toString())));

        QList<allocazioneTurniBaseSimilitudine> listaSimilitudine;

        for(int i=2; ((i < numeroRisorse+2) ) ; i++)
        {
            QCheckBox *pCheckBox = new QCheckBox();
            pCheckBox= (QCheckBox *) ui->tw->cellWidget(i,3);
            QComboBox *pComboBox = new QComboBox();

            pComboBox= ( QComboBox * )ui->tw->cellWidget(i,4);
            QString IDMatriceScelta= pComboBox->currentText();

            int simil;
            QString turnoSettimanaPrecedente;
            bool checked;


            if (pCheckBox->isChecked() && (IdMatrice == IDMatriceScelta) )
            {
                //turnoSettimanaPrecedente= this->turnoPrecedente(ui->tw->item(i,0)->text(), 1);
                ui->tw->setItem(i,6,new QTableWidgetItem( turnoSettimanaPrecedente));
                if(turnoSettimanaPrecedente !="")
                {
                    simil= similitudineTurni(turnoDaMatriceOSA, turnoSettimanaPrecedente);
                    checked= true;
                }
                else
                {
                    simil= -100;
                    turnoSettimanaPrecedente="-";
                    checked= false;
                }
            }
            else
            {
                simil= -100;
                turnoSettimanaPrecedente="-";
                checked= false;
            }

            allocazioneTurniBaseSimilitudine l;
            l.Idturno= IdMatrice;
            l.Progressivo= Progressivo;
            l.simil= simil;
            l.risorsa= ui->tw->item(i,0)->text();
            l.turnoSeme= turnoDaMatriceOSA;
            l.turnoSettimanaPrecedente= turnoSettimanaPrecedente;
            l.allocato= checked;
            listaSimilitudine.append(l);
          //  if (listaSimilitudine.count() > 1)
          //     if ( (listaSimilitudine.at(0).simil < listaSimilitudine.last().simil)   )
          //      {
          //          listaSimilitudine.swap(listaSimilitudine.count()-1, 0 );
          //          qDebug()<< "Swap: " << listaSimilitudine.at(0).simil <<" con " << listaSimilitudine.at(listaSimilitudine.count()-1 ).simil;
//                            l.Idturno= IdMatrice;
//                            l.Progressivo= Progressivo;
//                            l.simil= simil;
//                            l.risorsa= i;
//                            l.turnoSeme= turnoDaMatriceOSA;
//                            l.turnoSettimanaPrecedente= turnoSettimanaPrecedente;
//                            l.allocato= true;
//                            listaSimilitudine.first().allocato= false;  ///il primo della lista viene indicato come non allocato
//                            listaSimilitudine.prepend( l);              ///si aggiunge come primo della lista come allocato
//                            //  ui->tw->setItem(i,5,new QTableWidgetItem( IdMatrice+" "+Progressivo));
                            //  ui->tw->setItem(i,6,new QTableWidgetItem( turnoSettimanaPrecedente));
                            ///  qDebug() << IdMatrice <<" "<< Progressivo << " " << turnoDaMatriceOSA << " check " << turnoSettimanaPrecedente<<" simil= " << simil;
                            //  qDebug() <<"Risorsa: " << listaSimilitudine.first().risorsa << " TurnoSeme: " << listaSimilitudine.first().turnoSeme << listaSimilitudine.first().simil;
           //             }
           //        else
           //         qDebug()<< "NO Swap: " << listaSimilitudine.at(0).Idturno <<" con " << listaSimilitudine.at(listaSimilitudine.count()-1 ).Idturno;

//                    {
//                            l.Idturno= IdMatrice;
//                            l.Progressivo= Progressivo;
//                            l.simil= simil;
//                            l.risorsa= i;
//                            l.turnoSeme= turnoDaMatriceOSA;
//                            l.turnoSettimanaPrecedente= turnoSettimanaPrecedente;
//                            l.allocato= false;

//                            listaSimilitudine.append(l);
            //                     }
        }
        ///else
        ///   qDebug() << IdMatrice <<" "<< Progressivo << " " << turnoDaMatriceOSA << "saltato";
        ///
//        for (int j= 0; j < listaSimilitudine.count(); j++)
//        {
//            qDebug() <<  listaSimilitudine.at(j).allocato<<" "<<listaSimilitudine.at(j).Idturno<<" "<<listaSimilitudine.at(j).Progressivo<<" "<< listaSimilitudine.at(j).risorsa <<" "<<listaSimilitudine.at(j).simil;
//        }
//        qDebug() <<"Risorsa: " << listaSimilitudine.first().risorsa <<" TurnoSeme: "<<listaSimilitudine.first().Idturno <<" "<<listaSimilitudine.first().Progressivo<< " " << listaSimilitudine.first().turnoSeme <<" simil= " << listaSimilitudine.first().simil;


        qSort(listaSimilitudine);       /// ordina la lista per valori decrescenti di SIMIL
//        for (int j= 0; j < listaSimilitudine.count(); j++)
//        {
//            qDebug() <<  listaSimilitudine.at(j).allocato<<" "<<listaSimilitudine.at(j).Idturno<<" "<<listaSimilitudine.at(j).Progressivo<<" "<< listaSimilitudine.at(j).risorsa <<" "<<listaSimilitudine.at(j).simil;
//        }
        listaSimilitudineMigliori.append(listaSimilitudine);

        qDebug() <<"Risorsa: " << listaSimilitudine.first().risorsa <<" TurnoSeme: "<<listaSimilitudine.first().Idturno <<" "<<listaSimilitudine.first().Progressivo<< " " << listaSimilitudine.first().turnoSeme <<" simil= " << listaSimilitudine.first().simil;
//        ui->tw->setItem(listaSimilitudine.first().risorsa,5,new QTableWidgetItem( QString("%1 %2 %3").arg(listaSimilitudine.first().Idturno).arg(listaSimilitudine.first().Progressivo).arg(listaSimilitudine.first().simil)));
    }

    qSort(listaSimilitudineMigliori);       /// ordina la lista per valori decrescenti di SIMIL
     for (int j= 0; j < listaSimilitudineMigliori.count(); j++)
    {
     //   qDebug() <<  listaSimilitudineMigliori.at(j).allocato<<" "<<listaSimilitudineMigliori.at(j).Idturno<<" "<<listaSimilitudineMigliori.at(j).Progressivo<<" "<< listaSimilitudineMigliori.at(j).risorsa <<" "<<listaSimilitudineMigliori.at(j).simil;

          qDebug() << "SCELTA per la risorsa: "<< listaSimilitudineMigliori.at(j).risorsa <<"-->"<< listaSimilitudineMigliori.at(j).Idturno <<" "<< listaSimilitudineMigliori.at(j).Progressivo << " " << listaSimilitudineMigliori.at(j).turnoSeme << " check " << listaSimilitudineMigliori.at(j).turnoSettimanaPrecedente<<" simil= " << listaSimilitudineMigliori.at(j).simil;
     //   ui->tw->setItem(listaSimilitudineMigliori.at(j).risorsa,5,new QTableWidgetItem( listaSimilitudineMigliori.at(j).Idturno+" "+listaSimilitudineMigliori.at(j).Progressivo));
    }




//    qDebug()<< "SCELTA: "<< listaSimilitudineMigliori.first().Idturno <<" "<< listaSimilitudineMigliori.first().Progressivo << " " << listaSimilitudineMigliori.first().turnoSeme << " check " << listaSimilitudineMigliori.first().turnoSettimanaPrecedente<<" simil= " << listaSimilitudineMigliori.first().simil;
//    ui->tw->setItem(listaSimilitudineMigliori.first().risorsa,5,new QTableWidgetItem( listaSimilitudineMigliori.first().Idturno+" "+listaSimilitudineMigliori.first().Progressivo));


     //   }

       // if (listaSimilitudine.first().allocato)
       // {
          ///  ui->tw->setItem(listaSimilitudine.first().risorsa,5,new QTableWidgetItem( listaSimilitudine.first().Idturno+" "+listaSimilitudine.first().Progressivo));
           /// ui->tw->setItem(listaSimilitudine.first().risorsa,6,new QTableWidgetItem( listaSimilitudine.first().turnoSettimanaPrecedente));
          //  qDebug() <<"Risorsa: " << listaSimilitudine.first().risorsa << " TurnoSeme: " << listaSimilitudine.first().turnoSettimanaPrecedente << listaSimilitudine.first().simil;
            //if (listaSimilitudine.first().simil > listaSimilitudineMigliori.first().simil)
            //  listaSimilitudineMigliori.prepend(listaSimilitudine.first());
            //else
          //   listaSimilitudineMigliori.append(listaSimilitudine.first());
       // }
//        for (int j= 0; j < listaSimilitudine.count(); j++)
//        {
//            qDebug() << listaSimilitudine.at(j).risorsa << "||" << listaSimilitudine.at(j).Idturno << "||" << listaSimilitudine.at(j).Progressivo  << "||" << listaSimilitudine.at(j).simil << "||" << listaSimilitudine.at(j).allocato;
//            //qDebug() << listaSimilitudine.at(j).turnoSeme;
//            //qDebug() << listaSimilitudine.at(j).turnoSettimanaPrecedente;


//        }


 //   }


//    for (int j= 0; j < listaSimilitudineMigliori.count(); j++)
//    {
//        qDebug() << "SCELTA per la risorsa: "<< listaSimilitudineMigliori.at(j).risorsa <<"-->"<< listaSimilitudineMigliori.at(j).Idturno <<" "<< listaSimilitudineMigliori.at(j).Progressivo << " " << listaSimilitudineMigliori.at(j).turnoSeme << " check " << listaSimilitudineMigliori.at(j).turnoSettimanaPrecedente<<" simil= " << listaSimilitudineMigliori.at(j).simil;
//        ui->tw->setItem(listaSimilitudineMigliori.at(j).risorsa,5,new QTableWidgetItem( listaSimilitudineMigliori.at(j).Idturno+" "+listaSimilitudineMigliori.at(j).Progressivo));
//    }

//    qDebug()<< "SCELTA: "<< listaSimilitudineMigliori.first().Idturno <<" "<< listaSimilitudineMigliori.first().Progressivo << " " << listaSimilitudineMigliori.first().turnoSeme << " check " << listaSimilitudineMigliori.first().turnoSettimanaPrecedente<<" simil= " << listaSimilitudineMigliori.first().simil;
//    ui->tw->setItem(listaSimilitudineMigliori.first().risorsa,5,new QTableWidgetItem( listaSimilitudineMigliori.first().Idturno+" "+listaSimilitudineMigliori.first().Progressivo));
//    ui->tw->setItem(listaSimilitudineMigliori.first().risorsa,6,new QTableWidgetItem( listaSimilitudineMigliori.first().turnoSettimanaPrecedente));




     /// RIEMPIMENTO DEL COMBOBOX PER LA SCELTA DEL TBASE
     for(int i=2; (i < numeroRisorse+2 )  ; i++)
     {
         QComboBox *pComboBox = new QComboBox();
         pComboBox= ( QComboBox * )ui->tw->cellWidget(i,4);
         QString IDMatriceScelta= pComboBox->currentText();


         QComboBox *pComboBoxTBase = new QComboBox();
         ui->tw->setCellWidget(i,5,pComboBoxTBase);
         pComboBoxTBase->setInsertPolicy(QComboBox::InsertAtTop);
         for (int j= 0; j < listaSimilitudineMigliori.count(); j++)
         {
             if ( (listaSimilitudineMigliori.at(j).risorsa == ui->tw->item(i,0)->text()) && (listaSimilitudineMigliori.at(j).allocato) && (listaSimilitudineMigliori.at(j).simil > 3) )
                 pComboBoxTBase->addItem( QString("%1 %2 --- %3 %4").arg(listaSimilitudineMigliori.at(j).Idturno).arg(listaSimilitudineMigliori.at(j).Progressivo).arg(listaSimilitudineMigliori.at(j).simil).arg(listaSimilitudineMigliori.at(j).turnoSeme));
             //   qDebug() <<  listaSimilitudineMigliori.at(j).allocato<<" "<<listaSimilitudineMigliori.at(j).Idturno<<" "<<listaSimilitudineMigliori.at(j).Progressivo<<" "<< listaSimilitudineMigliori.at(j).risorsa <<" "<<listaSimilitudineMigliori.at(j).simil;
             //     qDebug() << "SCELTA per la risorsa: "<< listaSimilitudineMigliori.at(j).risorsa <<"-->"<< listaSimilitudineMigliori.at(j).Idturno <<" "<< listaSimilitudineMigliori.at(j).Progressivo << " " << listaSimilitudineMigliori.at(j).turnoSeme << " check " << listaSimilitudineMigliori.at(j).turnoSettimanaPrecedente<<" simil= " << listaSimilitudineMigliori.at(j).simil;
             //   ui->tw->setItem(listaSimilitudineMigliori.at(j).risorsa,5,new QTableWidgetItem( listaSimilitudineMigliori.at(j).Idturno+" "+listaSimilitudineMigliori.at(j).Progressivo));
         }
         pComboBoxTBase->addItem("________ --- _______");
         QSqlQuery querymatriceTurni(QString("select * from matriceTurni where IdMatrice=\"%1\"").arg(IDMatriceScelta));
         querymatriceTurni.exec();
         while(querymatriceTurni.next())
         {
             QString IdMatrice=  querymatriceTurni.value(0).toString();
             QString Progressivo=  querymatriceTurni.value(1).toString();
             QString turnoDaMatriceOSA;
             turnoDaMatriceOSA.clear();
             for (int l=0; l<7; l++)
                 turnoDaMatriceOSA.append((QString("%1 ").arg(querymatriceTurni.value(l+2).toString())));
             pComboBoxTBase->addItem(QString("%1 %2 %3").arg(querymatriceTurni.value(0).toString()).arg(querymatriceTurni.value(1).toString()).arg(turnoDaMatriceOSA));
         }

     }
     this->slot_checkDoppioniAssociazioniTurnoBase();


    ui->tw->resizeColumnsToContents();
    ui->tw->resizeRowsToContents();
    this->setCursor(Qt::ArrowCursor);

}

void FormGenerazioneTurno::on_pbTurnoP_clicked()
{

}

void FormGenerazioneTurno::on_cbreparti_currentTextChanged(const QString &arg1)
{
    QFont font;
    font.setBold(true);
    ui->tw->setRowCount(2);
    //////////////////////////////// si popola l'interfaccia con le persone allocate al reparto scelto nel comboBox
    QSqlQuery queryOperatoriRepartiCount(QString(" SELECT count(*) from (SELECT operatori.matricola,cognome,nome FROM reparti join operatori  on operatori.idreparto=reparti.idreparto join anagrafica on operatori.matricola=anagrafica.matricola where descrizione=\"%1\" order by cognome )").arg(ui->cbreparti->currentText()));
    queryOperatoriRepartiCount.first();
    qDebug() << queryOperatoriRepartiCount.lastQuery() << queryOperatoriRepartiCount.lastError();
    ui->tw->setRowCount(queryOperatoriRepartiCount.value(0).toInt()+2);


    int riga =2;
    QSqlQuery queryOperatoriReparti(QString("SELECT operatori.matricola,cognome,nome FROM reparti join operatori  on operatori.idreparto=reparti.idreparto join anagrafica on operatori.matricola=anagrafica.matricola where descrizione=\"%1\" order by cognome").arg(ui->cbreparti->currentText()));
    qDebug() << queryOperatoriReparti.lastQuery() << queryOperatoriReparti.lastError();
    while (queryOperatoriReparti.next())
    {
        QString Matricola=  queryOperatoriReparti.value(0).toString();
        QString Cognome=  queryOperatoriReparti.value(1).toString();
        QString Nome=  queryOperatoriReparti.value(2).toString();
        qDebug() << Matricola <<" "<< Cognome <<" "<<Nome;
        ui->tw->setItem(riga,0,new QTableWidgetItem(Matricola));
        ui->tw->setItem(riga,1,new QTableWidgetItem(Cognome));
        ui->tw->setItem(riga,2,new QTableWidgetItem(Nome));
        ui->tw->item(riga, 0)->setFont(font);
        ui->tw->item(riga, 1)->setFont(font);
        ui->tw->item(riga, 2)->setFont(font);

        riga++;
    }
    //////////////////////////////////////////////////////////////////////////////
    popolaLaTabella_tw();
    generaTurniSequenziali(0);


    ui->tw->resizeColumnsToContents();
    ui->tw->resizeRowsToContents();
}

void FormGenerazioneTurno::on_pbSalvaExcel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva in excel file"), ".", tr("Excel File (*.xlsx)"));
    QXlsx::Document  xlsx(fileName);

    for(int i=3; (i <= ui->tw->rowCount() )  ; i++)
    {
        for(int j=1; (j < 4 )  ; j++)
        {
             xlsx.write(i,j, ui->tw->item(i-1,j-1)->text());
        }
        for(int j=4; (j < ui->tw->columnCount()-3 )  ; j++)
        {
             xlsx.write(i,j, ui->tw->item(i-1,j+3)->text());
        }
    }

    xlsx.save();
}

void FormGenerazioneTurno::on_pbInsertInDatabase_clicked()
{
    this->setCursor(Qt::WaitCursor);
    QString matricola, idmatrice,  data_lun, lun, mar, mer, gio, ven,sab, dom;
    int progressivo,week, anno;
    for(int i=2; (i < ui->tw->rowCount() )  ; i++)
   // for(int i=2; (i < 3 )  ; i++)
    {
        matricola= ui->tw->item(i,0)->text();
        QComboBox *pComboBox = new QComboBox();
        pComboBox= ( QComboBox * )ui->tw->cellWidget(i,5);
        QStringList IDMatrice= pComboBox->currentText().split(' ');
        idmatrice= IDMatrice.at(0);
        progressivo= IDMatrice.at(1).toInt();

        // viene ricavato il progressivo massimo per quella tipologiaDiMatrice (ad esempio OSA_NOTTURNO ha un modulo =11
        QSqlQuery queryMaxProgressivo(QString("select count(*) from matriceturni where IDMatrice=\"%1\"").arg(idmatrice));
        queryMaxProgressivo.next();
        int progressivoMax= queryMaxProgressivo.value(0).toInt();


        for(int j=7; (j < ui->tw->columnCount() )  ; j+= 7)
        {
           QDate data;
           data =QDate::fromString(ui->tw->item(0,j)->text(),"dd/MM/yyyy");
           week= data.weekNumber();
           anno= data.year();

           if (data.dayOfWeek()==1)
                data_lun= data.toString("yyyy-MM-dd");

           lun= ui->tw->item(i,j)->text();
           mar= ui->tw->item(i,j+1)->text();
           mer= ui->tw->item(i,j+2)->text();
           gio= ui->tw->item(i,j+3)->text();
           ven= ui->tw->item(i,j+4)->text();
           sab= ui->tw->item(i,j+5)->text();
           dom= ui->tw->item(i,j+6)->text();

           QString id;
           id=QString("%1_%2").arg(matricola).arg(data_lun);
           qDebug()<< id << matricola<< idmatrice<< progressivo << week<< anno<< data_lun<< lun<< mar<< mer<< gio<< ven << sab << dom;
           QSqlQuery queryInsertInDatabaseTurni;
           queryInsertInDatabaseTurni.prepare("INSERT or replace INTO turnazione_operatore (id,matricola,idmatrice,progressivo,data_lun,week,anno,lun,mar,mer,gio,ven,sab,dom)" "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
           queryInsertInDatabaseTurni.addBindValue( id);
           queryInsertInDatabaseTurni.addBindValue( matricola);
           queryInsertInDatabaseTurni.addBindValue( idmatrice);
           queryInsertInDatabaseTurni.addBindValue( progressivo);
           queryInsertInDatabaseTurni.addBindValue( data_lun);
           queryInsertInDatabaseTurni.addBindValue( week);
           queryInsertInDatabaseTurni.addBindValue( anno);
           queryInsertInDatabaseTurni.addBindValue( lun);
           queryInsertInDatabaseTurni.addBindValue( mar);
           queryInsertInDatabaseTurni.addBindValue( mer);
           queryInsertInDatabaseTurni.addBindValue( gio);
           queryInsertInDatabaseTurni.addBindValue( ven);
           queryInsertInDatabaseTurni.addBindValue( sab);
           queryInsertInDatabaseTurni.addBindValue( dom);
           queryInsertInDatabaseTurni.exec();
           ///qDebug() <<  queryInsertInDatabaseTurni.lastQuery() << queryInsertInDatabaseTurni.lastError();

           if (progressivo==progressivoMax)
               progressivo= 1;  //il turno successivo saraà il progressivo 1 se il progressivo precedente era uguale al modulo
           else
               progressivo++;
        }
    }
    this->setCursor(Qt::ArrowCursor);
    QMessageBox::information(this,"Informazione!!", "Turnazione inserita in database.");


}
