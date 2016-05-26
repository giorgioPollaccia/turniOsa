/********************************************************************************
** Form generated from reading UI file 'formgestioneferie.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMGESTIONEFERIE_H
#define UI_FORMGESTIONEFERIE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormGestioneFerie
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QComboBox *cbTipoPermesso;
    QLabel *label_6;
    QLabel *label_4;
    QDateEdit *dePermessiDal;
    QDateEdit *dePermessiAl;
    QPushButton *pbDataAl;
    QPushButton *pbDataDal;
    QLabel *label_7;
    QLabel *label;
    QComboBox *cbCognome;
    QLabel *label_2;
    QLabel *lNome;
    QComboBox *cbMatricola;
    QPushButton *pbAggiungiPermesso;
    QLabel *label_3;
    QTableView *tvPermessi;

    void setupUi(QWidget *FormGestioneFerie)
    {
        if (FormGestioneFerie->objectName().isEmpty())
            FormGestioneFerie->setObjectName(QStringLiteral("FormGestioneFerie"));
        FormGestioneFerie->resize(567, 447);
        gridLayout_3 = new QGridLayout(FormGestioneFerie);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(FormGestioneFerie);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        groupBox->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cbTipoPermesso = new QComboBox(groupBox);
        cbTipoPermesso->setObjectName(QStringLiteral("cbTipoPermesso"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        cbTipoPermesso->setFont(font1);

        gridLayout->addWidget(cbTipoPermesso, 3, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        gridLayout->addWidget(label_6, 3, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        dePermessiDal = new QDateEdit(groupBox);
        dePermessiDal->setObjectName(QStringLiteral("dePermessiDal"));

        gridLayout->addWidget(dePermessiDal, 4, 1, 1, 1);

        dePermessiAl = new QDateEdit(groupBox);
        dePermessiAl->setObjectName(QStringLiteral("dePermessiAl"));

        gridLayout->addWidget(dePermessiAl, 5, 1, 1, 1);

        pbDataAl = new QPushButton(groupBox);
        pbDataAl->setObjectName(QStringLiteral("pbDataAl"));

        gridLayout->addWidget(pbDataAl, 5, 2, 1, 1);

        pbDataDal = new QPushButton(groupBox);
        pbDataDal->setObjectName(QStringLiteral("pbDataDal"));

        gridLayout->addWidget(pbDataDal, 4, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        cbCognome = new QComboBox(groupBox);
        cbCognome->setObjectName(QStringLiteral("cbCognome"));
        cbCognome->setFont(font1);
        cbCognome->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));

        gridLayout->addWidget(cbCognome, 1, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        lNome = new QLabel(groupBox);
        lNome->setObjectName(QStringLiteral("lNome"));
        lNome->setMinimumSize(QSize(150, 0));
        lNome->setFont(font1);
        lNome->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lNome, 1, 3, 1, 1);

        cbMatricola = new QComboBox(groupBox);
        cbMatricola->setObjectName(QStringLiteral("cbMatricola"));

        gridLayout->addWidget(cbMatricola, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        pbAggiungiPermesso = new QPushButton(groupBox);
        pbAggiungiPermesso->setObjectName(QStringLiteral("pbAggiungiPermesso"));
        pbAggiungiPermesso->setFont(font1);
        pbAggiungiPermesso->setDefault(true);

        gridLayout_2->addWidget(pbAggiungiPermesso, 1, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        label_3 = new QLabel(FormGestioneFerie);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        verticalLayout->addWidget(label_3);

        tvPermessi = new QTableView(FormGestioneFerie);
        tvPermessi->setObjectName(QStringLiteral("tvPermessi"));
        tvPermessi->setAlternatingRowColors(true);
        tvPermessi->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tvPermessi);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(FormGestioneFerie);

        QMetaObject::connectSlotsByName(FormGestioneFerie);
    } // setupUi

    void retranslateUi(QWidget *FormGestioneFerie)
    {
        FormGestioneFerie->setWindowTitle(QApplication::translate("FormGestioneFerie", "Gestione Permessi", 0));
        groupBox->setTitle(QApplication::translate("FormGestioneFerie", "Aggiungi un permesso", 0));
        cbTipoPermesso->clear();
        cbTipoPermesso->insertItems(0, QStringList()
         << QApplication::translate("FormGestioneFerie", "ferie", 0)
         << QApplication::translate("FormGestioneFerie", "malattia", 0)
         << QApplication::translate("FormGestioneFerie", "legge_104", 0)
        );
        label_6->setText(QApplication::translate("FormGestioneFerie", "Tipologia Permesso:", 0));
        label_4->setText(QApplication::translate("FormGestioneFerie", "Dal:", 0));
        pbDataAl->setText(QApplication::translate("FormGestioneFerie", "...", 0));
        pbDataDal->setText(QApplication::translate("FormGestioneFerie", "...", 0));
        label_7->setText(QApplication::translate("FormGestioneFerie", "Al:", 0));
        label->setText(QApplication::translate("FormGestioneFerie", "Matricola:", 0));
        label_2->setText(QApplication::translate("FormGestioneFerie", "Cognome:", 0));
        lNome->setText(QApplication::translate("FormGestioneFerie", "Nome:", 0));
        pbAggiungiPermesso->setText(QApplication::translate("FormGestioneFerie", "Aggiungi permesso nel database", 0));
        label_3->setText(QApplication::translate("FormGestioneFerie", "Assenze (Ferie, malattie, ecc.) caricati nel database", 0));
#ifndef QT_NO_TOOLTIP
        tvPermessi->setToolTip(QString());
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class FormGestioneFerie: public Ui_FormGestioneFerie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMGESTIONEFERIE_H
