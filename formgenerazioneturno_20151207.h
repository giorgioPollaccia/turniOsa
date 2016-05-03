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
    QString turnoPrecedente(QString matricola, int nSettPrecedenti); //ritorna il turno di nSettimanePrecedenti della matricola

    QList<allocazioneTurniBase> alTurniBase;

private slots:
    void slot_dataIniziale(QDate);
    void slot_dataFinale(QDate);

    void on_pbDataDal_clicked();
    void on_pbDataAl_clicked();
    void on_pbTurnoPrecedente_clicked();
    void on_cbMese_currentIndexChanged(int index);
    void on_cbAnno_currentIndexChanged(int index);
};

#endif // FORMGENERAZIONETURNO_H
