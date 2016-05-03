#ifndef FORMCALENDARIO_H
#define FORMCALENDARIO_H

#include <QWidget>
#include <QDate>

namespace Ui {
class FormCalendario;
}

class FormCalendario : public QWidget
{
    Q_OBJECT

public:
    explicit FormCalendario(QString, QWidget *parent = 0);
    ~FormCalendario();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::FormCalendario *ui;
signals:
     void signal_data (QDate);
};

#endif // FORMCALENDARIO_H
