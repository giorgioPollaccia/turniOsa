#include "formcalendario.h"
#include "ui_formcalendario.h"

FormCalendario::FormCalendario(QString titolo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCalendario)
{
    ui->setupUi(this);
    this->setWindowTitle(titolo);
}

FormCalendario::~FormCalendario()
{
    delete ui;
}

void FormCalendario::on_calendarWidget_clicked(const QDate &date)
{
    emit signal_data(date);
    close();
}
