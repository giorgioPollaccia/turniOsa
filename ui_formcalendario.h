/********************************************************************************
** Form generated from reading UI file 'formcalendario.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCALENDARIO_H
#define UI_FORMCALENDARIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormCalendario
{
public:
    QGridLayout *gridLayout;
    QCalendarWidget *calendarWidget;

    void setupUi(QWidget *FormCalendario)
    {
        if (FormCalendario->objectName().isEmpty())
            FormCalendario->setObjectName(QStringLiteral("FormCalendario"));
        FormCalendario->setWindowModality(Qt::WindowModal);
        FormCalendario->resize(274, 173);
        gridLayout = new QGridLayout(FormCalendario);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        calendarWidget = new QCalendarWidget(FormCalendario);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));

        gridLayout->addWidget(calendarWidget, 0, 0, 1, 1);


        retranslateUi(FormCalendario);

        QMetaObject::connectSlotsByName(FormCalendario);
    } // setupUi

    void retranslateUi(QWidget *FormCalendario)
    {
        FormCalendario->setWindowTitle(QApplication::translate("FormCalendario", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class FormCalendario: public Ui_FormCalendario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCALENDARIO_H
