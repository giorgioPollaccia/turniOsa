#ifndef FORMORELAVORATEPERDIPENDENTE_H
#define FORMORELAVORATEPERDIPENDENTE_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>

#include <QMessageBox>
#include <QDebug>
#include <QTime>

#include "formcalendario.h"

namespace Ui {
class FormOreLavoratePerDipendente;
}

class FormOreLavoratePerDipendente : public QWidget
{
    Q_OBJECT

public:
    explicit FormOreLavoratePerDipendente(QSqlDatabase db, QWidget *parent = 0);
    ~FormOreLavoratePerDipendente();

private slots:

    void on_pbLoad_clicked();

    void on_deDal_dateChanged(const QDate &date);

    void on_deAl_dateChanged(const QDate &date);

    void on_rbOreEffettuate_clicked();

private:
    Ui::FormOreLavoratePerDipendente *ui;
     QSqlDatabase db;

     QDate dataIniziale;
     QDate dataFinale;
};

#endif // FORMORELAVORATEPERDIPENDENTE_H
