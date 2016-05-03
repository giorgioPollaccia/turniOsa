#include "formgenerazioneturno.h"
#include "ui_formgenerazioneturno.h"

#include <QSqlQuery>
#include <QSqlError>

FormGenerazioneTurno::FormGenerazioneTurno(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGenerazioneTurno)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->db= db;



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




    //ui->dePermessiDal->setDate(oggi.currentDate());
    //ui->dePermessiAl->setDate(oggi.currentDate());
    //dataIniziale.setDate(oggi.currentDate().year(),oggi.currentDate().month(),oggi.currentDate().day());
    //dataFinale.setDate(oggi.currentDate().year(),oggi.currentDate().month(),oggi.currentDate().day());
    //qDebug() << dataIniziale.toString("dd/MM/yyyy");
    //qDebug() << dataFinale.toString("dd/MM/yyyy");



    ui->tw->setColumnCount(7 +dataIniziale.daysTo(dataFinale)+1);
    /// Determina il numero di OSA disponibili dalla tabella "anagrafica"
    QSqlQuery query(QString("SELECT * FROM anagrafica"));
    if (!query.exec())
        qDebug() << "Errore! " << query.lastError();
    numeroRisorse= 0;
    while(query.next())
        numeroRisorse++;
    ui->tw->setRowCount(numeroRisorse+2);


    //Set Header Label Texts Here
  //  ui->tw->setHorizontalHeaderLabels(QString("ID;Cognome;Nome; ;Matrice;TBase;TPrec").split(";"));
    ui->tw->setItem(0,0, new QTableWidgetItem(QString("ID")));
    ui->tw->setItem(0,1, new QTableWidgetItem(QString("Cognome")));
    ui->tw->setItem(0,2, new QTableWidgetItem(QString("Nome")));
   // ui->tw->setItem(0,3, new QTableWidgetItem(QString("")));
    ui->tw->setItem(0,4, new QTableWidgetItem(QString("Matrice")));
    ui->tw->setItem(0,5, new QTableWidgetItem(QString("TBase")));
    ui->tw->setItem(0,6, new QTableWidgetItem(QString("Turno Precedente")));

    QDate comodo= dataIniziale;
    for(int j= 7; j < 7 +dataIniziale.daysTo(dataFinale)+1; j++, comodo= comodo.addDays(1))
    {
         ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM"))));
         ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));

    }



    /// dalla query ricavo le stringhe per popolare la tabella
    query.seek(0);
    for(int i= 2; i < numeroRisorse+2; i++)
    {
       QString Cognome=  query.value(0).toString();
       QString Nome=  query.value(1).toString();
       QString Matricola=  query.value(2).toString();
       ui->tw->setItem(i,0,new QTableWidgetItem(Matricola));
       ui->tw->setItem(i,1,new QTableWidgetItem(Cognome));
       ui->tw->setItem(i,2,new QTableWidgetItem(Nome));
       query.next();

       //CElla con il checkBox per abilitare o meno la risorsa
       QCheckBox *pCheckBox = new QCheckBox();
       pCheckBox->setChecked(1);
       ui->tw->setCellWidget(i,3,pCheckBox);

       //combo box per la scelta della matrice di turno da usare per la risorsa
       //viene riempita con l'IDMATRICE ottenuto dalla tabella "matriceTurni"
       QComboBox *pComboBox = new QComboBox();
       QSqlQuery query1(QString("select distinct IDMATRICE from matriceTurni"));
       query1.exec();
       while(query1.next())
       {
           pComboBox->addItem(query1.value(0).toString());
       }
       ui->tw->setCellWidget(i,4,pComboBox);

       //Imposto il valore del pComboBox con la stringa che identifica la matrice di default  (impostata nella anagrafica)
       QSqlQuery query2(QString("select MatricePredefinita  from anagrafica where matricola= \"%1\"").arg(Matricola));
       query2.exec();
       while(query2.next())
       {
         // qDebug() << QString("%1 MatriceTurno default: %2").arg(Matricola).arg(query2.value(0).toString());
          pComboBox->setCurrentText(query2.value(0).toString());
       }
    }




     ui->tw->resizeColumnsToContents();
    ui->tw->resizeRowsToContents();



 }




FormGenerazioneTurno::~FormGenerazioneTurno()
{
    delete ui;
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



        ui->tw->setColumnCount(7 +dataIniziale.daysTo(dataFinale)+1);
        QDate comodo= dataIniziale;
        for(int j= 7; j < 7 +dataIniziale.daysTo(dataFinale)+1; j++, comodo= comodo.addDays(1))
        {
             ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM"))));
             ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));

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
            for(int j= 7; j < 7 +dataIniziale.daysTo(dataFinale)+1; j++, comodo= comodo.addDays(1))
            {
                 ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM"))));
                 ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));

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
         if ( (str.at(i) == str1.at(i)) ||  (str1.at(i) =="F"))
             similitudine++;
         else
             similitudine--;
         if ( (str.at(i) == "N") && ( str1.at(i) =="N")  )
             similitudine +=10;
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
QString FormGenerazioneTurno::turnoPrecedente(QString matricola, int nSettPrecedenti)
{
    QString turno;
    for(int j= (-(7*(nSettPrecedenti-1))-7);j <= (-(7*(nSettPrecedenti-1))-1) ; j++)
    {
        QSqlQuery query(QString(" select turno from turno where matricola=\"%1\" and data=\"%2\"").arg(matricola).arg(dataIniziale.addDays(j).toString("dd/MM/yyyy")));
        query.exec();
        if(query.next())
        {
            turno.append(QString("%1 ").arg(query.value(0).toString()));
        }
    }
    qDebug() << QString("TurnoSettimana -%1: %2").arg(nSettPrecedenti).arg(turno);
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
    for(int i=2; (i < numeroRisorse+2 )  ; i++)
    {
        QComboBox *pComboBoxTBase = new QComboBox();
        ui->tw->setCellWidget(i,5,pComboBoxTBase);
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
             }

             QString turni4SettimanePrecedenti[4];
             for(int cont= 0; cont < 4; cont ++)
                 turni4SettimanePrecedenti[cont]= this->turnoPrecedente(ui->tw->item(i,0)->text(), cont + 1);










            /// Ricavo il turno -4 rispetto alla settimana iniziale
            QString turnoPrecedentePrecedentePrecedentePrecedente;
            for(int j= -28;j <= -22; j++)
            {
                QSqlQuery queryPrecPrecPrecPrec(QString(" select turno from turno where matricola=\"%1\" and data=\"%2\"").arg(ui->tw->item(i,0)->text()).arg(dataIniziale.addDays(j).toString("dd/MM/yyyy")));
                queryPrecPrecPrecPrec.exec();
                ///qDebug() << query1.executedQuery();
                if(queryPrecPrecPrecPrec.next())
                {
                    ///qDebug() <<   query1.value(0).toString();
                    turnoPrecedentePrecedentePrecedentePrecedente.append(QString("%1 ").arg(queryPrecPrecPrecPrec.value(0).toString()));
                    //ui->tw->setItem(i,6,new QTableWidgetItem( query1.value(0).toString()));
                    //      pComboBox->addItem(query1.value(0).toString());
                }
                ///  qDebug() <<"TurnPP: " << turnoPrecedentePrecedente;
                /// ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
            }








            /// Ricavo il turno precedentePrecedente rispetto alla settimana iniziale
            QString turnoPrecedentePrecedentePrecedente;
            for(int j= -21;j <= -15; j++)
            {
                QSqlQuery queryPrecPrecPrec(QString(" select turno from turno where matricola=\"%1\" and data=\"%2\"").arg(ui->tw->item(i,0)->text()).arg(dataIniziale.addDays(j).toString("dd/MM/yyyy")));
                queryPrecPrecPrec.exec();
                ///qDebug() << query1.executedQuery();
                if(queryPrecPrecPrec.next())
                {
                    ///qDebug() <<   query1.value(0).toString();
                    turnoPrecedentePrecedentePrecedente.append(QString("%1 ").arg(queryPrecPrecPrec.value(0).toString()));
                    //ui->tw->setItem(i,6,new QTableWidgetItem( query1.value(0).toString()));
                    //      pComboBox->addItem(query1.value(0).toString());
                }
                ///  qDebug() <<"TurnPP: " << turnoPrecedentePrecedente;
                /// ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
            }



            /// Ricavo il turno precedentePrecedente rispetto alla settimana iniziale
            QString turnoPrecedentePrecedente;
            for(int j= -14;j <= -8; j++)
            {
                QSqlQuery queryPrecPrec(QString(" select turno from turno where matricola=\"%1\" and data=\"%2\"").arg(ui->tw->item(i,0)->text()).arg(dataIniziale.addDays(j).toString("dd/MM/yyyy")));
                queryPrecPrec.exec();
                ///qDebug() << query1.executedQuery();
                if(queryPrecPrec.next())
                {
                    ///qDebug() <<   query1.value(0).toString();
                    turnoPrecedentePrecedente.append(QString("%1 ").arg(queryPrecPrec.value(0).toString()));
                    //ui->tw->setItem(i,6,new QTableWidgetItem( query1.value(0).toString()));
                    //      pComboBox->addItem(query1.value(0).toString());
                }
                ///  qDebug() <<"TurnPP: " << turnoPrecedentePrecedente;
                /// ui->tw->setItem(i,6,new QTableWidgetItem( turnoPrecedente));
            }







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
               /// qDebug() <<"TurnoP: " << turnoPrecedente;
           }













            qDebug()<< QString("Turni precedenti: %1 || %2 || %3 || %4" ).arg(turnoPrecedentePrecedentePrecedentePrecedente).arg(turnoPrecedentePrecedentePrecedente).arg(turnoPrecedentePrecedente).arg(turnoPrecedente);


            ////  CALCOLO PER SIMILITUDINE DELL'ID (MATRICE E ID) DEL TURNO PRECEDENTE
            QString turnoSeme;
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
        }/// FINE IF la risorsa e' checked
        else
           // ui->tw->setItem(i,6,new QTableWidgetItem("-"));
            pComboBoxTBase->addItem("-");


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
         ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM"))));
         ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));
    }
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
         ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1").arg(comodo.toString("dd/MM"))));
         ui->tw->setItem(1,j, new QTableWidgetItem(QString("%1").arg(comodo.shortDayName( comodo.dayOfWeek()))));
    }
    ui->tw->resizeColumnsToContents();
    ui->tw->resizeRowsToContents();

}
