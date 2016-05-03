/********************************************************************************
** Form generated from reading UI file 'formgenerazioneturno.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMGENERAZIONETURNO_H
#define UI_FORMGENERAZIONETURNO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormGenerazioneTurno
{
public:
    QGridLayout *gridLayout_2;
    QTableWidget *tw;
    QGridLayout *gridLayout;
    QDateEdit *dePermessiDal;
    QPushButton *pbValidaTurnoBase;
    QPushButton *pbDataDal;
    QDateEdit *dePermessiAl;
    QPushButton *pbDataAl;
    QPushButton *pbTurnoPrecedente;
    QSpacerItem *verticalSpacer;
    QComboBox *cbAnno;
    QLabel *label_2;
    QComboBox *cbMese;
    QLabel *label;
    QPushButton *pbTurnoPrecedente2;
    QLabel *label_4;
    QPushButton *pbTurnoP;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *label_5;
    QComboBox *cbreparti;
    QPushButton *pbSalvaExcel;
    QPushButton *pbInsertInDatabase;

    void setupUi(QWidget *FormGenerazioneTurno)
    {
        if (FormGenerazioneTurno->objectName().isEmpty())
            FormGenerazioneTurno->setObjectName(QStringLiteral("FormGenerazioneTurno"));
        FormGenerazioneTurno->resize(897, 499);
        gridLayout_2 = new QGridLayout(FormGenerazioneTurno);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tw = new QTableWidget(FormGenerazioneTurno);
        tw->setObjectName(QStringLiteral("tw"));
        QFont font;
        font.setPointSize(7);
        tw->setFont(font);
        tw->horizontalHeader()->setVisible(false);
        tw->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(tw, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        dePermessiDal = new QDateEdit(FormGenerazioneTurno);
        dePermessiDal->setObjectName(QStringLiteral("dePermessiDal"));

        gridLayout->addWidget(dePermessiDal, 7, 1, 1, 1);

        pbValidaTurnoBase = new QPushButton(FormGenerazioneTurno);
        pbValidaTurnoBase->setObjectName(QStringLiteral("pbValidaTurnoBase"));
        pbValidaTurnoBase->setEnabled(false);

        gridLayout->addWidget(pbValidaTurnoBase, 11, 0, 1, 1);

        pbDataDal = new QPushButton(FormGenerazioneTurno);
        pbDataDal->setObjectName(QStringLiteral("pbDataDal"));
        pbDataDal->setMaximumSize(QSize(20, 16777215));

        gridLayout->addWidget(pbDataDal, 7, 2, 1, 1);

        dePermessiAl = new QDateEdit(FormGenerazioneTurno);
        dePermessiAl->setObjectName(QStringLiteral("dePermessiAl"));

        gridLayout->addWidget(dePermessiAl, 8, 1, 1, 1);

        pbDataAl = new QPushButton(FormGenerazioneTurno);
        pbDataAl->setObjectName(QStringLiteral("pbDataAl"));
        pbDataAl->setMaximumSize(QSize(20, 16777215));

        gridLayout->addWidget(pbDataAl, 8, 2, 1, 1);

        pbTurnoPrecedente = new QPushButton(FormGenerazioneTurno);
        pbTurnoPrecedente->setObjectName(QStringLiteral("pbTurnoPrecedente"));
        pbTurnoPrecedente->setEnabled(false);

        gridLayout->addWidget(pbTurnoPrecedente, 9, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 15, 1, 1, 1);

        cbAnno = new QComboBox(FormGenerazioneTurno);
        cbAnno->setObjectName(QStringLiteral("cbAnno"));

        gridLayout->addWidget(cbAnno, 4, 1, 1, 1);

        label_2 = new QLabel(FormGenerazioneTurno);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        cbMese = new QComboBox(FormGenerazioneTurno);
        cbMese->setObjectName(QStringLiteral("cbMese"));
        cbMese->setMaxVisibleItems(12);

        gridLayout->addWidget(cbMese, 5, 1, 1, 1);

        label = new QLabel(FormGenerazioneTurno);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 4, 0, 1, 1);

        pbTurnoPrecedente2 = new QPushButton(FormGenerazioneTurno);
        pbTurnoPrecedente2->setObjectName(QStringLiteral("pbTurnoPrecedente2"));
        pbTurnoPrecedente2->setEnabled(false);

        gridLayout->addWidget(pbTurnoPrecedente2, 10, 0, 1, 1);

        label_4 = new QLabel(FormGenerazioneTurno);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 7, 0, 1, 1);

        pbTurnoP = new QPushButton(FormGenerazioneTurno);
        pbTurnoP->setObjectName(QStringLiteral("pbTurnoP"));
        pbTurnoP->setEnabled(false);

        gridLayout->addWidget(pbTurnoP, 12, 0, 1, 1);

        label_7 = new QLabel(FormGenerazioneTurno);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 8, 0, 1, 1);

        label_3 = new QLabel(FormGenerazioneTurno);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 6, 0, 1, 1);

        label_5 = new QLabel(FormGenerazioneTurno);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        cbreparti = new QComboBox(FormGenerazioneTurno);
        cbreparti->setObjectName(QStringLiteral("cbreparti"));

        gridLayout->addWidget(cbreparti, 3, 1, 1, 1);

        pbSalvaExcel = new QPushButton(FormGenerazioneTurno);
        pbSalvaExcel->setObjectName(QStringLiteral("pbSalvaExcel"));

        gridLayout->addWidget(pbSalvaExcel, 13, 0, 1, 1);

        pbInsertInDatabase = new QPushButton(FormGenerazioneTurno);
        pbInsertInDatabase->setObjectName(QStringLiteral("pbInsertInDatabase"));

        gridLayout->addWidget(pbInsertInDatabase, 14, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(FormGenerazioneTurno);

        cbAnno->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FormGenerazioneTurno);
    } // setupUi

    void retranslateUi(QWidget *FormGenerazioneTurno)
    {
        FormGenerazioneTurno->setWindowTitle(QApplication::translate("FormGenerazioneTurno", "Generazione Turno", 0));
        pbValidaTurnoBase->setText(QApplication::translate("FormGenerazioneTurno", "Valida TurnoBase", 0));
        pbDataDal->setText(QApplication::translate("FormGenerazioneTurno", "...", 0));
        pbDataAl->setText(QApplication::translate("FormGenerazioneTurno", "...", 0));
        pbTurnoPrecedente->setText(QApplication::translate("FormGenerazioneTurno", "Turno Precedente", 0));
        cbAnno->clear();
        cbAnno->insertItems(0, QStringList()
         << QApplication::translate("FormGenerazioneTurno", "2015", 0)
         << QApplication::translate("FormGenerazioneTurno", "2016", 0)
         << QApplication::translate("FormGenerazioneTurno", "2017", 0)
         << QApplication::translate("FormGenerazioneTurno", "2018", 0)
         << QApplication::translate("FormGenerazioneTurno", "2019", 0)
         << QApplication::translate("FormGenerazioneTurno", "2020", 0)
        );
        label_2->setText(QApplication::translate("FormGenerazioneTurno", "Mese", 0));
        cbMese->clear();
        cbMese->insertItems(0, QStringList()
         << QApplication::translate("FormGenerazioneTurno", "Gennaio", 0)
         << QApplication::translate("FormGenerazioneTurno", "Febbraio", 0)
         << QApplication::translate("FormGenerazioneTurno", "Marzo", 0)
         << QApplication::translate("FormGenerazioneTurno", "Aprile", 0)
         << QApplication::translate("FormGenerazioneTurno", "Maggio", 0)
         << QApplication::translate("FormGenerazioneTurno", "Giugno", 0)
         << QApplication::translate("FormGenerazioneTurno", "Luglio", 0)
         << QApplication::translate("FormGenerazioneTurno", "Agosto", 0)
         << QApplication::translate("FormGenerazioneTurno", "Settembre", 0)
         << QApplication::translate("FormGenerazioneTurno", "Ottombre", 0)
         << QApplication::translate("FormGenerazioneTurno", "Novembre", 0)
         << QApplication::translate("FormGenerazioneTurno", "Dicembre", 0)
        );
        label->setText(QApplication::translate("FormGenerazioneTurno", "Anno", 0));
        pbTurnoPrecedente2->setText(QApplication::translate("FormGenerazioneTurno", "Turno Predente 2", 0));
        label_4->setText(QApplication::translate("FormGenerazioneTurno", "Dal:", 0));
        pbTurnoP->setText(QApplication::translate("FormGenerazioneTurno", "PushButton", 0));
        label_7->setText(QApplication::translate("FormGenerazioneTurno", "Al:", 0));
        label_3->setText(QApplication::translate("FormGenerazioneTurno", "TextLabel", 0));
        label_5->setText(QApplication::translate("FormGenerazioneTurno", "Reparto", 0));
        pbSalvaExcel->setText(QApplication::translate("FormGenerazioneTurno", "Salva su Excel ....", 0));
        pbInsertInDatabase->setText(QApplication::translate("FormGenerazioneTurno", "Inserisci in database", 0));
    } // retranslateUi

};

namespace Ui {
    class FormGenerazioneTurno: public Ui_FormGenerazioneTurno {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMGENERAZIONETURNO_H
