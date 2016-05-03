#ifndef FORMGENERAZIONETURNO_H
#define FORMGENERAZIONETURNO_H

#include <QWidget>

#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>

#include <QMessageBox>

#include <QSettings>
#include <QDebug>

#include <QCheckBox>
#include <QComboBox>

#include <QMessageBox>
#include <QFileDialog>


#include "formcalendario.h"

namespace Ui {
class FormGenerazioneTurno;
}


class allocazioneTurniBase
{
public:
    QString Idturno;
    QString Progressivo;
    QString turnoSeme;
    int allocato;
    int numTurniBase;
};


class allocazioneTurniBaseSimilitudine
{
public:
    QString Idturno;
    QString Progressivo;
    QString turnoSeme;
    QString turnoSettimanaPrecedente;
    int simil;
    QString risorsa;
    bool allocato;
    bool operator<(const allocazioneTurniBaseSimilitudine &other) const;  //overload dell'operatore <() per fare il sorting della lista di oggetti allocazioneTurniBaseSimilitudine

};

class FormGenerazioneTurno : public QWidget
{
    Q_OBJECT

public:
    explicit FormGenerazioneTurno(QSqlDatabase db, QWidget *parent = 0);
    ~FormGenerazioneTurno();

private:
    Ui::FormGenerazioneTurno *ui;
    QSqlDatabase db;
    int numeroRisorse;

    FormCalendario *fCalendario(QString);

    QDate dataIniziale;
    QDate dataFinale;



    int similitudineTurni(QString turnoSeme, QString turnoPrecedente);
    QString turnoPrecedente(QString matricola, int nSettPrecedenti, QString *s, int *p); //ritorna il turno di nSettimanePrecedenti della matricola

    QList<allocazioneTurniBase> alTurniBase;

    void popolaLaTabella_tw();
    void generaTurniSequenziali(bool dallaMatriceTurni);



private slots:
    void slot_checkDoppioniAssociazioniTurnoBase();
    void slot_dataIniziale(QDate);
    void slot_dataFinale(QDate);

    void slot_cambioIdMatrice( QString);


    void on_pbDataDal_clicked();
    void on_pbDataAl_clicked();
    void on_pbTurnoPrecedente_clicked();
    void on_cbMese_currentIndexChanged(int index);
    void on_cbAnno_currentIndexChanged(int index);
    void on_pbTurnoPrecedente2_clicked();
    void on_pbTurnoP_clicked();
    void on_cbreparti_currentTextChanged(const QString &arg1);
    void on_pbSalvaExcel_clicked();
    void on_pbInsertInDatabase_clicked();
};

#endif // FORMGENERAZIONETURNO_H
