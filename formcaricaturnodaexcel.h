#ifndef FORMCARICATURNODAEXCEL_H
#define FORMCARICATURNODAEXCEL_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>

#include <QMessageBox>
#include <QFileDialog>

#include <QDate>

namespace Ui {
class formCaricaTurnoDaExcel;
}

class formCaricaTurnoDaExcel : public QWidget
{
    Q_OBJECT

public:
    explicit formCaricaTurnoDaExcel(QSqlDatabase db, QWidget *parent = 0);
    ~formCaricaTurnoDaExcel();

private slots:
    void on_pbCaricaTurnoDaExcel_clicked();

private:
    Ui::formCaricaTurnoDaExcel *ui;
    QSqlDatabase db;
};

#endif // FORMCARICATURNODAEXCEL_H
