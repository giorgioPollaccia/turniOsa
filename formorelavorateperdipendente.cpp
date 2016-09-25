#include "formorelavorateperdipendente.h"
#include "ui_formorelavorateperdipendente.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include "xlsxdocument.h"

FormOreLavoratePerDipendente::FormOreLavoratePerDipendente(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormOreLavoratePerDipendente)
{
    ui->setupUi(this);
    this->db= db;

    QDate oggi;
   // dataIniziale.setDate(oggi.currentDate().year(),oggi.currentDate().month(), oggi.currentDate().day());
   // dataFinale.setDate(oggi.currentDate().year(),oggi.currentDate().month(), oggi.currentDate().day());
    ui->deDal->setDate(oggi.currentDate());
    ui->deDal->setCalendarPopup(1);
    ui->deAl->setDate(oggi.currentDate());
    ui->deAl->setCalendarPopup(1);

    ui->tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw->setSelectionBehavior(QAbstractItemView::SelectRows);
}

FormOreLavoratePerDipendente::~FormOreLavoratePerDipendente()
{
    delete ui;
}





void FormOreLavoratePerDipendente::on_pbLoad_clicked()
{
    ui->rbTurniEffettuati->setChecked(1);
    QString dataDal=  ui->deDal->text();
    QDate DataDal;
    DataDal= QDate::fromString(dataDal,"dd/MM/yyyy");
    int weekDal= DataDal.weekNumber();
    QString dataAl=  ui->deAl->text();
    QDate DataAl= QDate::fromString(dataAl,"dd/MM/yyyy");
    int weekAl= DataAl.weekNumber();

    QFont font;
    font.setBold(true);

    // ui->tw->setColumnCount(7 +dataIniziale.daysTo(dataFinale)+1);
     ui->tw->setColumnCount(4 + weekAl - weekDal);
     ui->tw->setRowCount(2);
     //Set Header Label Texts Here
   //  ui->tw->setHorizontalHeaderLabels(QString("ID;Cognome;Nome; ;Matrice;TBase;TPrec").split(";"));
     ui->tw->setItem(0,0, new QTableWidgetItem(QString("ID")));
     ui->tw->setItem(0,1, new QTableWidgetItem(QString("Cognome")));
     ui->tw->setItem(0,2, new QTableWidgetItem(QString("Nome")));

    // for (int i= weekDal, j=3; i <= weekAl; i++, j++)

     QDate comodo= DataDal;
     int j=3;
    // ui->tw->setRowCount(100);

     while (comodo.operator <(DataAl) )
     {
         int week= comodo.weekNumber();
         int anno= comodo.year();
         ui->tw->setItem(0,j, new QTableWidgetItem(QString("%1_%2").arg(week).arg(anno)));
         comodo= comodo.addDays(7);

         int riga= 1;
         QSqlQuery queryMatricole(QString("select matricola, cognome, nome from anagrafica order by cognome"));
         while (queryMatricole.next())
         {
             if (ui->tw->rowCount()< riga+1)
                 ui->tw->setRowCount(riga+1);
             QString Matricola=  queryMatricole.value(0).toString();
             QString Cognome=  queryMatricole.value(1).toString();
             QString Nome=  queryMatricole.value(2).toString();

             ui->tw->setItem(riga,0,new QTableWidgetItem(Matricola));
             ui->tw->setItem(riga,1,new QTableWidgetItem(Cognome));
             ui->tw->setItem(riga,2,new QTableWidgetItem(Nome));
             ui->tw->setItem(0,j,new QTableWidgetItem("-"));
             ui->tw->setItem(riga,j,new QTableWidgetItem("-"));


             QSqlQuery queryOreLavorate(QString("select matricola, week, data_lun, lun, mar, mer, gio, ven, sab, dom from turnazione_operatore where matricola=%1 and week = '%2' and anno= '%3'").arg(Matricola).arg(week).arg(anno));
             //qDebug() << queryOreLavorate.executedQuery();
             while (queryOreLavorate.next())
             {
                 ui->tw->setItem(0,j, new QTableWidgetItem(QString("w%1 %2").arg(queryOreLavorate.value(1).toString()).arg(queryOreLavorate.value(2).toString())));
                 ui->tw->setItem(riga,j,new QTableWidgetItem(QString("%1 %2 %3 %4 %5 %6 %7")
                          .arg(queryOreLavorate.value(3).toString())
                          .arg(queryOreLavorate.value(4).toString())
                          .arg(queryOreLavorate.value(5).toString())
                          .arg(queryOreLavorate.value(6).toString())
                          .arg(queryOreLavorate.value(7).toString())
                          .arg(queryOreLavorate.value(8).toString())
                          .arg(queryOreLavorate.value(9).toString())));
             }
             riga++;
         }
         j++;

    }

     for(int i=0; i< ui->tw->columnCount();i++)
         ui->tw->item(0, i)->setFont(font);
     for(int i=0; i< ui->tw->rowCount();i++)
     {
          ui->tw->item(i, 0)->setFont(font);
          ui->tw->item(i, 1)->setFont(font);
          ui->tw->item(i, 2)->setFont(font);
     }

     ui->tw->resizeColumnsToContents();
     ui->tw->resizeRowsToContents();
}

void FormOreLavoratePerDipendente::on_deDal_dateChanged(const QDate &date)
{
    QDate dataIniziale= date;
    while (dataIniziale.dayOfWeek()!=1)  ///PRIMO LUNEDI DEL MESE CORRENTE
      dataIniziale=  dataIniziale.addDays(-1);
    ui->deDal->setDate(dataIniziale);
}

void FormOreLavoratePerDipendente::on_deAl_dateChanged(const QDate &date)
{
    QDate dataIniziale= date;
    while (dataIniziale.dayOfWeek()!=7)  ///PRIMO LUNEDI DEL MESE CORRENTE
      dataIniziale=  dataIniziale.addDays(1);
    ui->deAl->setDate(dataIniziale);
}

void FormOreLavoratePerDipendente::on_rbOreEffettuate_clicked()
{
 //   ui->tw->setColumnCount(ui->tw->columnCount()+1);
    for(int riga=1; riga< ui->tw->rowCount();riga++)
    {
        int minutiTotaliNelPeriodo= 0;
        for(int colonna=3; colonna< ui->tw->columnCount();colonna++)
        {
            QString turno= ui->tw->item(riga, colonna)->text();
            if (turno =="")
                continue;
            QStringList turniDay =turno.split(" ");

            int minutiFatti= 0;

            for (int k=0; k< turniDay.count(); k++)
            {
                //qDebug() << turniDay.at(k);
                if ( (turniDay.at(k)=="M") || (turniDay.at(k)=="P") || (turniDay.at(k)=="F")  )
                     minutiFatti += 420;
                else
                    if ( (turniDay.at(k)=="M1") || (turniDay.at(k)=="P1") )
                        minutiFatti += 320;
                    else
                        if ( (turniDay.at(k)=="N")  )
                             minutiFatti += 600;
            }
            // ui->tw->setItem(riga, colonna,new QTableWidgetItem(QString("%1").arg(oreFatte.toString("hh:mm"))));
            // qDebug() << t.fromTime_t(ore*60).toString("hh:mm");
            minutiTotaliNelPeriodo += minutiFatti;
            int ore= minutiFatti / 60;
            int minuti= minutiFatti % 60;

            ui->tw->setItem(riga, colonna,new QTableWidgetItem(QString("%1:%2").arg(ore,2,10,0,'0').arg(minuti,2,10,0,'0')));
            //qDebug() << minutiFatti << ore << minuti;
        }

        int oreTotaliNelPeriodo= minutiTotaliNelPeriodo / 60;
        int minTotaliNelPeriodo= minutiTotaliNelPeriodo % 60;

       // ui->tw->setItem(riga, ui->tw->columnCount()-1,new QTableWidgetItem(QString("%1:%2").arg(oreTotaliNelPeriodo,2,10,0,'0').arg(minTotaliNelPeriodo,2,10,0,'0')));
    }

    ui->tw->resizeColumnsToContents();
    ui->tw->resizeRowsToContents();
}

void FormOreLavoratePerDipendente::on_pbSalvaExcel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva in excel file"), ".", tr("Excel File (*.xlsx)"));
    if (!fileName.isEmpty())
    {
         qDebug() << fileName;
        QXlsx::Document  xlsx(fileName);

        for(int i=1; (i <= ui->tw->rowCount() )  ; i++)
        {
            for(int j=1; (j <= ui->tw->columnCount() )  ; j++)
            {
                qDebug() << ui->tw->item(i-1,j-1)->text();
                xlsx.write(i,j, ui->tw->item(i-1,j-1)->text());
            }
            // for(int j=2; (j < ui->tw->columnCount()-3 )  ; j++)
            // {
            //      xlsx.write(i,j, ui->tw->item(i-1,j+3)->text());
            // }
        }

        xlsx.save();
     }
}
