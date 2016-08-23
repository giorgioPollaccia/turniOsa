#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QMdiSubWindow>
#include <QFileDialog>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    db =  QSqlDatabase::addDatabase("QSQLITE");
    QSettings settings("Pollaccia", "turniOSA");
    if (! settings.value("opzioniFileEsterni/fileSQLITE","").toString().isEmpty())
    {
        db.setDatabaseName(settings.value("opzioniFileEsterni/fileSQLITE","").toString());
        db.open();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.critical(this,"Errore scelta file SQLITE","Scegli nelle opzioni il file del database da aprire all'avvio dell'applicazione!", QMessageBox::Ok);
    }

}

MainWindow::~MainWindow()
{
    ui->mdiArea->closeAllSubWindows();
    delete ui;
}

void MainWindow::slot_rinfrescaDati()
{
 emit this->signal_rinfrescaDati();
}

void MainWindow::on_actionAnagrafica_triggered()
{
    bool isOpen= false;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
      if (window->windowTitle().contains("Anagrafica") )
      {
          ui->mdiArea->setActiveSubWindow(window);
          isOpen= true;
      }
    }
    if (! isOpen )
    {
        FormAnagrafica *fAnagrafica = new FormAnagrafica(db);
        connect(this, SIGNAL(signal_rinfrescaDati()), fAnagrafica, SLOT(slot_rinfrescaDati()));
        fAnagrafica->setAttribute(Qt::WA_DeleteOnClose);
        ui->mdiArea->addSubWindow(fAnagrafica);
        fAnagrafica->show();

    }
}

void MainWindow::on_actionAggiungi_Risorse_triggered()
{
    bool isOpen= false;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
      if (window->windowTitle().contains("Aggiungi Risorsa") )
      {
          ui->mdiArea->setActiveSubWindow(window);
          isOpen= true;
      }
    }
    if (! isOpen )
    {
        FormAggiungiAnagrafica *fAggiungiAnagrafica = new FormAggiungiAnagrafica(db);
        connect(fAggiungiAnagrafica, SIGNAL(signal_rinfrescadati()), this, SLOT(slot_rinfrescaDati()));
        fAggiungiAnagrafica->setAttribute(Qt::WA_DeleteOnClose);
        ui->mdiArea->addSubWindow(fAggiungiAnagrafica);
        fAggiungiAnagrafica->show();


    }
}

void MainWindow::on_actionOpzioni_triggered()
{
    bool isOpen= false;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
      if (window->windowTitle().contains("Opzioni file esterni") )
      {
          ui->mdiArea->setActiveSubWindow(window);
          isOpen= true;
      }
    }
    if (! isOpen )
    {
        FormOpzioniFileEsterni *fOpzioniFileEsterni = new FormOpzioniFileEsterni(db);
        fOpzioniFileEsterni->setAttribute(Qt::WA_DeleteOnClose);
        ui->mdiArea->addSubWindow(fOpzioniFileEsterni);
        fOpzioniFileEsterni->show();
    }
}

void MainWindow::on_actionTabella_Matrici_triggered()
{
    bool isOpen= false;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
      if (window->windowTitle().contains("Tabella Matrici") )
      {
          ui->mdiArea->setActiveSubWindow(window);
          isOpen= true;
      }
    }
    if (! isOpen )
    {
        FormVisualizzaMatrici *fOpzioniFileEsterni = new FormVisualizzaMatrici(db);
        fOpzioniFileEsterni->setAttribute(Qt::WA_DeleteOnClose);
        ui->mdiArea->addSubWindow(fOpzioniFileEsterni);
        fOpzioniFileEsterni->show();
    }
}

void MainWindow::on_actionPermessi_triggered()
{
    bool isOpen= false;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
      if (window->windowTitle().contains("Gestione Permessi") )
      {
          ui->mdiArea->setActiveSubWindow(window);
          isOpen= true;
      }
    }
    if (! isOpen )
    {
        FormGestioneFerie *fGestioneFerie = new FormGestioneFerie(db);
        fGestioneFerie->setAttribute(Qt::WA_DeleteOnClose);
        ui->mdiArea->addSubWindow(fGestioneFerie);
        fGestioneFerie->show();
    }
}

void MainWindow::on_actionCarica_un_turno_da_un_foglio_excel_triggered()
{
    bool isOpen= false;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
      if (window->windowTitle().contains("Carica turno da foglio excel.") )
      {
          ui->mdiArea->setActiveSubWindow(window);
          isOpen= true;
      }
    }
    if (! isOpen )
    {
        formCaricaTurnoDaExcel *fCaricaTurnoDaExcel = new formCaricaTurnoDaExcel(db);
        fCaricaTurnoDaExcel->setAttribute(Qt::WA_DeleteOnClose);
        ui->mdiArea->addSubWindow(fCaricaTurnoDaExcel);
        fCaricaTurnoDaExcel->show();
    }
}

void MainWindow::on_actionGenerazione_Tuno_triggered()
{
    bool isOpen= false;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
      if (window->windowTitle().contains("Generazione Turno") )
      {
          ui->mdiArea->setActiveSubWindow(window);
          isOpen= true;
      }
    }
    if (! isOpen )
    {
        FormGenerazioneTurno *fGenerazioneTurno= new FormGenerazioneTurno(db);
        fGenerazioneTurno->setAttribute(Qt::WA_DeleteOnClose);
        ui->mdiArea->addSubWindow(fGenerazioneTurno);
        fGenerazioneTurno->show();
    }
}

//void MainWindow::on_actionGrafici_per_risorsa_triggered()
//{
//    bool isOpen= false;
//       foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
//       {
//         if (window->windowTitle().contains("Generazione Turno") )
//         {
//             ui->mdiArea->setActiveSubWindow(window);
//             isOpen= true;
//         }
//       }
//       if (! isOpen )
//       {
//           FormGenerazioneTurno *fGenerazioneTurno= new FormGenerazioneTurno(db);
//           fGenerazioneTurno->setAttribute(Qt::WA_DeleteOnClose);
//           ui->mdiArea->addSubWindow(fGenerazioneTurno);
//           fGenerazioneTurno->show();
//       }
//}



void MainWindow::on_actionReport_generale_triggered()
{
    bool isOpen= false;
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList())
    {
      if (window->windowTitle().contains("Report generale") )
      {
          ui->mdiArea->setActiveSubWindow(window);
          isOpen= true;
      }
    }
    if (! isOpen )
    {
         FormOreLavoratePerDipendente *fOreLavoratePerDipendente= new FormOreLavoratePerDipendente(db);
         fOreLavoratePerDipendente->setAttribute(Qt::WA_DeleteOnClose);
         ui->mdiArea->addSubWindow(fOreLavoratePerDipendente);
         fOreLavoratePerDipendente->show();
    }
}
