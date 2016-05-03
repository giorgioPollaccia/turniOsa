/********************************************************************************
** Form generated from reading UI file 'formopzionifileesterni.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMOPZIONIFILEESTERNI_H
#define UI_FORMOPZIONIFILEESTERNI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormOpzioniFileEsterni
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QCheckBox *cbFileMatriceTurni;
    QLineEdit *leNomeFileExcelMatriceTurni;
    QPushButton *pbScegliFileMatriceTurni;
    QSpacerItem *verticalSpacer;
    QPushButton *pbSalvaOpzioni;
    QLabel *label_2;
    QLineEdit *leNomeFileDatabase;
    QPushButton *pbFileSqlite;

    void setupUi(QWidget *FormOpzioniFileEsterni)
    {
        if (FormOpzioniFileEsterni->objectName().isEmpty())
            FormOpzioniFileEsterni->setObjectName(QStringLiteral("FormOpzioniFileEsterni"));
        FormOpzioniFileEsterni->resize(784, 300);
        gridLayout = new QGridLayout(FormOpzioniFileEsterni);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(FormOpzioniFileEsterni);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        cbFileMatriceTurni = new QCheckBox(FormOpzioniFileEsterni);
        cbFileMatriceTurni->setObjectName(QStringLiteral("cbFileMatriceTurni"));
        cbFileMatriceTurni->setChecked(true);

        gridLayout->addWidget(cbFileMatriceTurni, 2, 3, 1, 1);

        leNomeFileExcelMatriceTurni = new QLineEdit(FormOpzioniFileEsterni);
        leNomeFileExcelMatriceTurni->setObjectName(QStringLiteral("leNomeFileExcelMatriceTurni"));

        gridLayout->addWidget(leNomeFileExcelMatriceTurni, 2, 1, 1, 1);

        pbScegliFileMatriceTurni = new QPushButton(FormOpzioniFileEsterni);
        pbScegliFileMatriceTurni->setObjectName(QStringLiteral("pbScegliFileMatriceTurni"));

        gridLayout->addWidget(pbScegliFileMatriceTurni, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        pbSalvaOpzioni = new QPushButton(FormOpzioniFileEsterni);
        pbSalvaOpzioni->setObjectName(QStringLiteral("pbSalvaOpzioni"));
        pbSalvaOpzioni->setAutoDefault(true);
        pbSalvaOpzioni->setDefault(true);

        gridLayout->addWidget(pbSalvaOpzioni, 0, 3, 1, 1);

        label_2 = new QLabel(FormOpzioniFileEsterni);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        leNomeFileDatabase = new QLineEdit(FormOpzioniFileEsterni);
        leNomeFileDatabase->setObjectName(QStringLiteral("leNomeFileDatabase"));

        gridLayout->addWidget(leNomeFileDatabase, 1, 1, 1, 1);

        pbFileSqlite = new QPushButton(FormOpzioniFileEsterni);
        pbFileSqlite->setObjectName(QStringLiteral("pbFileSqlite"));

        gridLayout->addWidget(pbFileSqlite, 1, 2, 1, 1);


        retranslateUi(FormOpzioniFileEsterni);

        QMetaObject::connectSlotsByName(FormOpzioniFileEsterni);
    } // setupUi

    void retranslateUi(QWidget *FormOpzioniFileEsterni)
    {
        FormOpzioniFileEsterni->setWindowTitle(QApplication::translate("FormOpzioniFileEsterni", "Opzioni file esterni", 0));
        label->setText(QApplication::translate("FormOpzioniFileEsterni", "File EXCEL descrittivo delle matrici dei turni", 0));
        cbFileMatriceTurni->setText(QApplication::translate("FormOpzioniFileEsterni", "Leggi all'avvio dell'applicazione", 0));
        leNomeFileExcelMatriceTurni->setText(QString());
        pbScegliFileMatriceTurni->setText(QApplication::translate("FormOpzioniFileEsterni", "...", 0));
        pbSalvaOpzioni->setText(QApplication::translate("FormOpzioniFileEsterni", "Salva Opzioni", 0));
        label_2->setText(QApplication::translate("FormOpzioniFileEsterni", "File SQLITE del database", 0));
        pbFileSqlite->setText(QApplication::translate("FormOpzioniFileEsterni", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class FormOpzioniFileEsterni: public Ui_FormOpzioniFileEsterni {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMOPZIONIFILEESTERNI_H
