/********************************************************************************
** Form generated from reading UI file 'formvisualizzamatrici.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMVISUALIZZAMATRICI_H
#define UI_FORMVISUALIZZAMATRICI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormVisualizzaMatrici
{
public:
    QLabel *label;
    QTableView *tvMatrici;

    void setupUi(QWidget *FormVisualizzaMatrici)
    {
        if (FormVisualizzaMatrici->objectName().isEmpty())
            FormVisualizzaMatrici->setObjectName(QStringLiteral("FormVisualizzaMatrici"));
        FormVisualizzaMatrici->resize(722, 408);
        label = new QLabel(FormVisualizzaMatrici);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 661, 16));
        tvMatrici = new QTableView(FormVisualizzaMatrici);
        tvMatrici->setObjectName(QStringLiteral("tvMatrici"));
        tvMatrici->setGeometry(QRect(10, 50, 631, 301));

        retranslateUi(FormVisualizzaMatrici);

        QMetaObject::connectSlotsByName(FormVisualizzaMatrici);
    } // setupUi

    void retranslateUi(QWidget *FormVisualizzaMatrici)
    {
        FormVisualizzaMatrici->setWindowTitle(QApplication::translate("FormVisualizzaMatrici", "Tabella Matrici", 0));
        label->setText(QApplication::translate("FormVisualizzaMatrici", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class FormVisualizzaMatrici: public Ui_FormVisualizzaMatrici {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMVISUALIZZAMATRICI_H
