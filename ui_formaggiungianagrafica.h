/********************************************************************************
** Form generated from reading UI file 'formaggiungianagrafica.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMAGGIUNGIANAGRAFICA_H
#define UI_FORMAGGIUNGIANAGRAFICA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormAggiungiAnagrafica
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pbCambiaFoto;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout;
    QComboBox *cbMatricePredefinita;
    QPushButton *pbInserisci;
    QLineEdit *leCognome;
    QLineEdit *leMatricola;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QLineEdit *leNome;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *FormAggiungiAnagrafica)
    {
        if (FormAggiungiAnagrafica->objectName().isEmpty())
            FormAggiungiAnagrafica->setObjectName(QStringLiteral("FormAggiungiAnagrafica"));
        FormAggiungiAnagrafica->resize(718, 327);
        gridLayout_2 = new QGridLayout(FormAggiungiAnagrafica);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(FormAggiungiAnagrafica);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(200, 200));
        label->setMaximumSize(QSize(200, 200));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::Box);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pbCambiaFoto = new QPushButton(FormAggiungiAnagrafica);
        pbCambiaFoto->setObjectName(QStringLiteral("pbCambiaFoto"));

        verticalLayout->addWidget(pbCambiaFoto);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cbMatricePredefinita = new QComboBox(FormAggiungiAnagrafica);
        cbMatricePredefinita->setObjectName(QStringLiteral("cbMatricePredefinita"));

        gridLayout->addWidget(cbMatricePredefinita, 3, 1, 1, 1);

        pbInserisci = new QPushButton(FormAggiungiAnagrafica);
        pbInserisci->setObjectName(QStringLiteral("pbInserisci"));
        pbInserisci->setAutoDefault(true);
        pbInserisci->setDefault(true);

        gridLayout->addWidget(pbInserisci, 5, 1, 1, 1);

        leCognome = new QLineEdit(FormAggiungiAnagrafica);
        leCognome->setObjectName(QStringLiteral("leCognome"));

        gridLayout->addWidget(leCognome, 1, 1, 1, 1);

        leMatricola = new QLineEdit(FormAggiungiAnagrafica);
        leMatricola->setObjectName(QStringLiteral("leMatricola"));
        leMatricola->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));

        gridLayout->addWidget(leMatricola, 0, 1, 1, 1);

        label_3 = new QLabel(FormAggiungiAnagrafica);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        label_2 = new QLabel(FormAggiungiAnagrafica);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        leNome = new QLineEdit(FormAggiungiAnagrafica);
        leNome->setObjectName(QStringLiteral("leNome"));

        gridLayout->addWidget(leNome, 2, 1, 1, 1);

        label_4 = new QLabel(FormAggiungiAnagrafica);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(FormAggiungiAnagrafica);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        QWidget::setTabOrder(leMatricola, leCognome);
        QWidget::setTabOrder(leCognome, leNome);
        QWidget::setTabOrder(leNome, pbCambiaFoto);
        QWidget::setTabOrder(pbCambiaFoto, pbInserisci);

        retranslateUi(FormAggiungiAnagrafica);

        QMetaObject::connectSlotsByName(FormAggiungiAnagrafica);
    } // setupUi

    void retranslateUi(QWidget *FormAggiungiAnagrafica)
    {
        FormAggiungiAnagrafica->setWindowTitle(QApplication::translate("FormAggiungiAnagrafica", "Aggiungi Risorsa", 0));
        label->setText(QApplication::translate("FormAggiungiAnagrafica", "FOTO !!!", 0));
        pbCambiaFoto->setText(QApplication::translate("FormAggiungiAnagrafica", "Scegli foto ...", 0));
        pbInserisci->setText(QApplication::translate("FormAggiungiAnagrafica", "Inserisci nel database la nuova risorsa", 0));
        label_3->setText(QApplication::translate("FormAggiungiAnagrafica", "MATRICOLA:", 0));
        label_2->setText(QApplication::translate("FormAggiungiAnagrafica", "COGNOME:", 0));
        label_4->setText(QApplication::translate("FormAggiungiAnagrafica", "NOME:", 0));
        label_5->setText(QApplication::translate("FormAggiungiAnagrafica", "SESSO:", 0));
    } // retranslateUi

};

namespace Ui {
    class FormAggiungiAnagrafica: public Ui_FormAggiungiAnagrafica {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMAGGIUNGIANAGRAFICA_H
