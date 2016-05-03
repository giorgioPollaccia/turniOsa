#include "formvisualizzamatrici.h"
#include "ui_formvisualizzamatrici.h"

#include "xlsxdocument.h"

#include <QSqlQuery>
#include <QSqlError>

FormVisualizzaMatrici::FormVisualizzaMatrici(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormVisualizzaMatrici)
{
    ui->setupUi(this);

    QSettings settings("Pollaccia", "turniOSA");
    ui->label->setText(settings.value("opzioniFileEsterni/fileMatriciTurni","").toString());
    QXlsx::Document  xlsx1(ui->label->text());


    QMessageBox msgBox;
    msgBox.setText("Attenzione.");
    msgBox.setInformativeText(QString("La tebella matriceTurni nel database verrà sovrascritta con il contenuto del file excel %1").arg(ui->label->text()));
    msgBox.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    int ret = msgBox.exec();
    if (ret== QMessageBox::Ok)
    {
        this->db= db;
        QSqlQuery query;
        query.exec( QString("DELETE FROM matriceTurni"));
        query.exec( QString("VACUUM"));

        QApplication::setOverrideCursor(Qt::WaitCursor);


        //// LETTURA DEL FILE EXCEL DELLA TABELLA DELLE MATRICI DEI TURNI
        int row= 2;
        int col= 1;
        while(! (xlsx1.read(row , 1 ).toString().isEmpty()))
        {
            col= 1;
            query.prepare("INSERT INTO matriceTurni (IDMATRICE, PROGRESSIVO, LUN, MAR, MER, GIO, VEN, SAB, DOM, RisorseMinime, RisorseMassime, ParitaDiGenere, C04)" "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

            while(! (xlsx1.read(row , col ).toString().isEmpty()))
            {
                // qDebug()<< row <<" "<< col <<" "<< xlsx1.read(row , col ).toString();
                query.addBindValue( xlsx1.read(row , col ).toString());


                col++;
            }
            if (! (query.exec()))
               qDebug() <<  query.lastError();
            row++;
        }
        //  qDebug()<< xlsx1.read("A1").toString()<< xlsx1.read("B1").toString();
        ////





        masterModel = new QSqlRelationalTableModel;
        masterModel->setTable("matriceTurni");
        masterModel->select();
        ui->tvMatrici->verticalHeader()->setDefaultSectionSize(20);
        ui->tvMatrici->setModel(masterModel);
        ui->tvMatrici->resizeColumnsToContents();

        QApplication::restoreOverrideCursor();
    }
}

FormVisualizzaMatrici::~FormVisualizzaMatrici()
{
    delete ui;
}
