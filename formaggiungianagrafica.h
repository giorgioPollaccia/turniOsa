#ifndef FORMAGGIUNGIANAGRAFICA_H
#define FORMAGGIUNGIANAGRAFICA_H

#include <QWidget>


#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlError>


namespace Ui {
class FormAggiungiAnagrafica;
}

class FormAggiungiAnagrafica : public QWidget
{
    Q_OBJECT

public:
    explicit FormAggiungiAnagrafica(QSqlDatabase db, QWidget *parent = 0);
    ~FormAggiungiAnagrafica();

private slots:
    void on_pbCambiaFoto_clicked();

    void on_pbInserisci_clicked();

private:
    Ui::FormAggiungiAnagrafica *ui;

    QByteArray byteArray;
     QSqlDatabase db;
signals:
    void signal_rinfrescadati();
};

#endif // FORMAGGIUNGIANAGRAFICA_H
