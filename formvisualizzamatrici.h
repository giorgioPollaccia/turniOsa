#ifndef FORMVISUALIZZAMATRICI_H
#define FORMVISUALIZZAMATRICI_H

#include <QWidget>

#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>

#include <QMessageBox>

#include <QSettings>
#include <QDebug>

namespace Ui {
class FormVisualizzaMatrici;
}

class FormVisualizzaMatrici : public QWidget
{
    Q_OBJECT

public:
    explicit FormVisualizzaMatrici(QSqlDatabase db, QWidget *parent = 0);
    ~FormVisualizzaMatrici();

private:
    Ui::FormVisualizzaMatrici *ui;
     QSqlDatabase db;

    QSqlRelationalTableModel *masterModel;
};

#endif // FORMVISUALIZZAMATRICI_H
