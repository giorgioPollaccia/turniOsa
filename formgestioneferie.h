#ifndef FORMGESTIONEFERIE_H
#define FORMGESTIONEFERIE_H

#include <QWidget>

#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>

#include <QMessageBox>

#include "formcalendario.h"

namespace Ui {
class FormGestioneFerie;
}

class FormGestioneFerie : public QWidget
{
    Q_OBJECT

public:
    explicit FormGestioneFerie(QSqlDatabase db, QWidget *parent = 0);
    ~FormGestioneFerie();

private slots:
    void on_pbDataDal_clicked();
    void slot_dataIniziale(QDate);
    void slot_dataFinale(QDate);

    void on_pbDataAl_clicked();

    void on_cbMatricola_currentIndexChanged(const QString &arg1);

    void on_cbCognome_currentIndexChanged(const QString &arg1);


    void on_pbAggiungiPermesso_clicked();

private:
    Ui::FormGestioneFerie *ui;
    QSqlDatabase db;
    FormCalendario *fCalendario(QString);
};

#endif // FORMGESTIONEFERIE_H
