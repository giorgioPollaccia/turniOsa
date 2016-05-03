/********************************************************************************
** Form generated from reading UI file 'formanagrafica.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMANAGRAFICA_H
#define UI_FORMANAGRAFICA_H

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
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormAnagrafica
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pbCambiaFoto;
    QSpacerItem *verticalSpacer_2;
    QTableView *tvanagrafica;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pbCancellaRisorsa;
    QLineEdit *leNome;
    QLabel *label_5;
    QLabel *label_2;
    QLineEdit *leCognome;
    QLabel *label_4;
    QLineEdit *leMatricola;
    QComboBox *cbGenere;
    QLabel *label_3;
    QLabel *label_6;
    QComboBox *cbReparto;
    QPushButton *pbCambiaReparto;

    void setupUi(QWidget *FormAnagrafica)
    {
        if (FormAnagrafica->objectName().isEmpty())
            FormAnagrafica->setObjectName(QStringLiteral("FormAnagrafica"));
        FormAnagrafica->resize(602, 767);
        gridLayout_2 = new QGridLayout(FormAnagrafica);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(FormAnagrafica);
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

        pbCambiaFoto = new QPushButton(FormAnagrafica);
        pbCambiaFoto->setObjectName(QStringLiteral("pbCambiaFoto"));

        verticalLayout->addWidget(pbCambiaFoto);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout_2->addLayout(verticalLayout, 1, 0, 1, 1);

        tvanagrafica = new QTableView(FormAnagrafica);
        tvanagrafica->setObjectName(QStringLiteral("tvanagrafica"));
        tvanagrafica->setAlternatingRowColors(true);
        tvanagrafica->setSelectionBehavior(QAbstractItemView::SelectRows);

        gridLayout_2->addWidget(tvanagrafica, 0, 0, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);

        pbCancellaRisorsa = new QPushButton(FormAnagrafica);
        pbCancellaRisorsa->setObjectName(QStringLiteral("pbCancellaRisorsa"));

        gridLayout->addWidget(pbCancellaRisorsa, 6, 1, 1, 1);

        leNome = new QLineEdit(FormAnagrafica);
        leNome->setObjectName(QStringLiteral("leNome"));

        gridLayout->addWidget(leNome, 2, 1, 1, 1);

        label_5 = new QLabel(FormAnagrafica);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_2 = new QLabel(FormAnagrafica);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        leCognome = new QLineEdit(FormAnagrafica);
        leCognome->setObjectName(QStringLiteral("leCognome"));

        gridLayout->addWidget(leCognome, 1, 1, 1, 1);

        label_4 = new QLabel(FormAnagrafica);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        leMatricola = new QLineEdit(FormAnagrafica);
        leMatricola->setObjectName(QStringLiteral("leMatricola"));
        leMatricola->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 127);"));

        gridLayout->addWidget(leMatricola, 0, 1, 1, 1);

        cbGenere = new QComboBox(FormAnagrafica);
        cbGenere->setObjectName(QStringLiteral("cbGenere"));

        gridLayout->addWidget(cbGenere, 3, 1, 1, 1);

        label_3 = new QLabel(FormAnagrafica);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        label_6 = new QLabel(FormAnagrafica);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        cbReparto = new QComboBox(FormAnagrafica);
        cbReparto->setObjectName(QStringLiteral("cbReparto"));

        gridLayout->addWidget(cbReparto, 4, 1, 1, 1);

        pbCambiaReparto = new QPushButton(FormAnagrafica);
        pbCambiaReparto->setObjectName(QStringLiteral("pbCambiaReparto"));

        gridLayout->addWidget(pbCambiaReparto, 4, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 1, 1, 1);

        QWidget::setTabOrder(tvanagrafica, leMatricola);
        QWidget::setTabOrder(leMatricola, leCognome);
        QWidget::setTabOrder(leCognome, leNome);
        QWidget::setTabOrder(leNome, pbCambiaFoto);
        QWidget::setTabOrder(pbCambiaFoto, pbCancellaRisorsa);

        retranslateUi(FormAnagrafica);

        QMetaObject::connectSlotsByName(FormAnagrafica);
    } // setupUi

    void retranslateUi(QWidget *FormAnagrafica)
    {
        FormAnagrafica->setWindowTitle(QApplication::translate("FormAnagrafica", "Anagrafica", 0));
        label->setText(QApplication::translate("FormAnagrafica", "TextLabel", 0));
        pbCambiaFoto->setText(QApplication::translate("FormAnagrafica", "Cambia foto ...", 0));
        pbCancellaRisorsa->setText(QApplication::translate("FormAnagrafica", "Cancella risorsa dal database ...", 0));
        label_5->setText(QApplication::translate("FormAnagrafica", "GENERE:", 0));
        label_2->setText(QApplication::translate("FormAnagrafica", "COGNOME:", 0));
        label_4->setText(QApplication::translate("FormAnagrafica", "NOME:", 0));
        label_3->setText(QApplication::translate("FormAnagrafica", "MATRICOLA:", 0));
        label_6->setText(QApplication::translate("FormAnagrafica", "REPARTO:", 0));
        pbCambiaReparto->setText(QApplication::translate("FormAnagrafica", "Cambia Reparto", 0));
    } // retranslateUi

};

namespace Ui {
    class FormAnagrafica: public Ui_FormAnagrafica {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMANAGRAFICA_H
