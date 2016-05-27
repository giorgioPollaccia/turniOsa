#include "formcaricaturnodaexcel.h"
#include "ui_formcaricaturnodaexcel.h"

#include "xlsxdocument.h"

#include <QDebug>

formCaricaTurnoDaExcel::formCaricaTurnoDaExcel(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::formCaricaTurnoDaExcel)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::SplashScreen);

     this->db= db;
}

formCaricaTurnoDaExcel::~formCaricaTurnoDaExcel()
{
    delete ui;
}

void formCaricaTurnoDaExcel::on_pbCaricaTurnoDaExcel_clicked()
{
    QSqlQuery query;

     QString matricola, turno, dt;



    QString fileName = QFileDialog::getOpenFileName(this, tr("Apri excel"), ".", tr("Excel File (*.xlsx)"));
    QXlsx::Document  xlsx1(fileName);
    //// LETTURA DEL FILE EXCEL


    int row_startMatricola= 3;
    int col_Matricola= 1;
    int col_Cognome= 2;
    int col_Nome= 3;
    int row_Data= 1;
    int col_startData= 4;
    int row_GiornoSettimana= 2;
    int col_GiornoSettimana= 3;
    int row_startTurno= 3;
    int col_startTurno= 4;

    int row= row_startMatricola;
    int col= col_startTurno;
    bool flagErrore= 0;


    this->setCursor(Qt::WaitCursor);
   // qDebug() << xlsx1.read(row , col_Cognome ).toString();
    while(! (xlsx1.read(row , 1 ).toString().isEmpty()))
    {
       col=  col_startTurno;
       matricola= xlsx1.read(row , col_Matricola ).toString();
       QString cgm=  xlsx1.read(row , col_Cognome ).toString();
       QString nm= xlsx1.read(row , col_Nome ).toString();
       //qDebug() <<  matricola <<" "<<  cgm <<" "<<  nm;
       while(! (xlsx1.read(row , col ).toString().isEmpty()))
       {
           //il formato della data che ritorna xlsx1 è "aaaa-mm-gg" invece a me serve gg/mm/aaaa
           qDebug() << "DATA: " << xlsx1.read(row_Data , col ).toString();
//           dt= QString("%1/%2/%3").arg( xlsx1.read(row_Data , col ).toString().mid(8,2) )
//                                          .arg( xlsx1.read(row_Data , col ).toString().mid(5,2) )
//                                          .arg( xlsx1.read(row_Data , col ).toString().mid(0,4) );
          // dt= QString("%1").arg(xlsx1.read(row_Data , col ).toString());
           QString turno= xlsx1.read(row , col ).toString();
//           QDate Data= QDate::fromString(xlsx1.read(row_Data , col ).toString(), "dd/MM/yyyy");
           QDate Data= QDate::fromString(xlsx1.read(row_Data , col ).toString(), "yyyy-MM-dd");
           int anno= Data.year();
           int week= Data.weekNumber();
           qDebug() << dt << Data.toString("yyyy-MM-dd") <<" "<<anno<<" "<<week<<" " <<  xlsx1.read(row , col ).toString();

           col++;



           QSqlQuery queryUpdate;
           QString giorno;
           switch (Data.dayOfWeek())
           {
             case 1 :  //giorno= "lun";
                       queryUpdate.prepare(QString("INSERT or replace INTO turnazione_operatore (id, matricola, idmatrice, progressivo, data_lun, week, anno, lun, mar, mer, gio, ven, sab, dom )"
                                                   "VALUES (:id, :matricola, :idmatrice, :progressivo , :data_lun, :week , :anno, :lun, :mar, :mer, :gio, :ven, :sab, :dom)"));
                       queryUpdate.bindValue(":id", QString("%1_%2").arg(matricola).arg(Data.toString("yyyy-MM-dd")));
                       queryUpdate.bindValue(":matricola", matricola);
                       queryUpdate.bindValue(":idmatrice", "OSA_NOTTURNO");
                       queryUpdate.bindValue(":progressivo", 1);
                       queryUpdate.bindValue(":data_lun", QString("%1").arg(Data.toString("yyyy-MM-dd")));
                       queryUpdate.bindValue(":week", week);
                       queryUpdate.bindValue(":anno", anno);
                       queryUpdate.bindValue(":lun", turno);
                       queryUpdate.bindValue(":mar", turno);
                       queryUpdate.bindValue(":mer", turno);
                       queryUpdate.bindValue(":gio", turno);
                       queryUpdate.bindValue(":ven", turno);
                       queryUpdate.bindValue(":sab", turno);
                       queryUpdate.bindValue(":dom", turno);
                       break;
             case 2 :  giorno= "mar";
                       queryUpdate.prepare(QString("update turnazione_operatore set %1=\"%2\" where matricola=\"%3\" and week=%4 and anno=%5").arg(giorno).arg(turno).arg(matricola).arg(week).arg(anno));
                       break;
             case 3 :  giorno= "mer";
                       queryUpdate.prepare(QString("update turnazione_operatore set %1=\"%2\" where matricola=\"%3\" and week=%4 and anno=%5").arg(giorno).arg(turno).arg(matricola).arg(week).arg(anno));
                       break;
             case 4 :  giorno= "gio";
                       queryUpdate.prepare(QString("update turnazione_operatore set %1=\"%2\" where matricola=\"%3\" and week=%4 and anno=%5").arg(giorno).arg(turno).arg(matricola).arg(week).arg(anno));
                       break;
             case 5 :  giorno= "ven";
                       queryUpdate.prepare(QString("update turnazione_operatore set %1=\"%2\" where matricola=\"%3\" and week=%4 and anno=%5").arg(giorno).arg(turno).arg(matricola).arg(week).arg(anno));
                       break;
             case 6 :  giorno= "sab";
                       queryUpdate.prepare(QString("update turnazione_operatore set %1=\"%2\" where matricola=\"%3\" and week=%4 and anno=%5").arg(giorno).arg(turno).arg(matricola).arg(week).arg(anno));
                       break;
             case 7 :  giorno= "dom";
                      queryUpdate.prepare(QString("update turnazione_operatore set %1=\"%2\" where matricola=\"%3\" and week=%4 and anno=%5").arg(giorno).arg(turno).arg(matricola).arg(week).arg(anno));
                      break;
           }

          // qDebug() << QString("INSERT or replace INTO turnazione_operatore (matricola, idmatrice, progressivo, week, anno, %1)"  "VALUES (?, ?, ?, ?, ?, ?)").arg(giorno);
          //  qDebug() << anno <<" "<<week<<" "<< giorno<<" "<<matricola << " "<<turno;

          queryUpdate.exec();
          qDebug() <<    queryUpdate.lastQuery();// executedQuery();




           /*

           //// INSERZIONE NEL DATABASE
           query.prepare("INSERT or replace INTO turno (ID, matricola, turno, data)" "VALUES (?, ?, ?, ?)");
           query.addBindValue( mat+"_"+dt);
           query.addBindValue( mat);
           query.addBindValue( t);
           query.addBindValue( dt);
           if(query.exec())
           {
//               QMessageBox msgBox;
//               msgBox.setText("Inserzione nel database.");
//               msgBox.setInformativeText(QString("Permesso per il giorno %1 inserito correttamente.").arg(a.toString("dd/MM/yyyy")));
//               msgBox.setStandardButtons(QMessageBox::Ok );
//               msgBox.setIcon(QMessageBox::Information);
//               msgBox.exec();
                 qDebug() << "turno inserito in database";
                 flagErrore= 0;
           }
           else
           {
               QMessageBox msgBox;
               msgBox.setText("Inserzione nel database tabella TURNO.");
               msgBox.setInformativeText(QString("Turno della matricola %1 per il giorno %2 NON inserito nel database. Probabilmente è gia stato inserito un turno per lo stesso giorno.").arg(mat).arg(dt));
               msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
               msgBox.setIcon(QMessageBox::Critical);
               switch (msgBox.exec())
               {
                 case QMessageBox::Cancel:
                     row= col= 10000;  /// IN CASO DI ERRORE NELLA INSERZIONE NEL DATABASE VIENE CONCLUSA L'OPERAZIONE
                     break;
                 default:
                     // should never be reached
                     break;
               }
                 qDebug() << "ERRORE !!! turno NON inserito in database";
              flagErrore= 1;
           }
           */
       }
        row++;
    }
    /*
    if ( ! flagErrore )
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Il file %1 contenente i turni è stato inserito nel database con successo.").arg(fileName));
        msgBox.setStandardButtons(QMessageBox::Ok );
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }


    */

   this->setCursor(Qt::ArrowCursor);






}
