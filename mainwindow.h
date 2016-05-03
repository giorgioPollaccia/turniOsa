#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "formanagrafica.h"
#include "formaggiungianagrafica.h"
#include "formopzionifileesterni.h"
#include "formvisualizzamatrici.h"
#include "formgestioneferie.h"
#include "formcaricaturnodaexcel.h"
#include "formgenerazioneturno.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAnagrafica_triggered();
   void slot_rinfrescaDati();
    void on_actionAggiungi_Risorse_triggered();

    void on_actionOpzioni_triggered();

    void on_actionTabella_Matrici_triggered();

    void on_actionPermessi_triggered();

    void on_actionCarica_un_turno_da_un_foglio_excel_triggered();

    void on_actionGenerazione_Tuno_triggered();

    
private:
    Ui::MainWindow *ui;


    FormAnagrafica *fAnagrafica;
    FormAggiungiAnagrafica *fAggiungiAnagrafica;
    FormOpzioniFileEsterni *fOpzioniFileEsterni;
    FormVisualizzaMatrici *fVisualizzaMatrici;
    FormGestioneFerie *fGestioneFerie;
    formCaricaTurnoDaExcel *fCaricaTurnoDaExcel;
    FormGenerazioneTurno *fGenerazioneTurno;

    QSqlDatabase db;
signals:
  void signal_rinfrescaDati();
};

#endif // MAINWINDOW_H
