#ifndef FORMANAGRAFICA_H
#define FORMANAGRAFICA_H

#include <QWidget>

#include <QFileDialog>
#include <QDebug>

#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>

#include <QMessageBox>

namespace Ui {
class FormAnagrafica;
}

class FormAnagrafica : public QWidget
{
    Q_OBJECT

public:
    explicit FormAnagrafica(QSqlDatabase db, QWidget *parent = 0);
    ~FormAnagrafica();


private slots:
    void on_tvanagrafica_clicked(const QModelIndex &index);
    void updateDetailGrid();
    void slot_visualizzaFoto(QModelIndex);

    void on_pbCambiaFoto_clicked();

    void on_pbCancellaRisorsa_clicked();
    void on_leMatricola_textChanged(const QString &arg1);

    void on_pbCambiaReparto_clicked();

public slots:
    void slot_rinfrescaDati();
private:
    Ui::FormAnagrafica *ui;

    QSqlRelationalTableModel *masterModel;
     QSqlDatabase db;



};

#endif // FORMANAGRAFICA_H
