#ifndef FORMOPZIONIFILEESTERNI_H
#define FORMOPZIONIFILEESTERNI_H

#include <QWidget>
#include <QSqlRelationalTableModel>

 #include <QFileDialog>
#include <QString>
#include <QSettings>

namespace Ui {
class FormOpzioniFileEsterni;
}

class FormOpzioniFileEsterni : public QWidget
{
    Q_OBJECT

public:
    explicit FormOpzioniFileEsterni(QSqlDatabase db, QWidget *parent = 0);
    ~FormOpzioniFileEsterni();

private slots:
    void on_pbScegliFileMatriceTurni_clicked();

    void on_pbSalvaOpzioni_clicked();

    void on_pbFileSqlite_clicked();

private:
    Ui::FormOpzioniFileEsterni *ui;
    QSqlDatabase db;
};

#endif // FORMOPZIONIFILEESTERNI_H
