/********************************************************************************
** Form generated from reading UI file 'formcaricaturnodaexcel.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCARICATURNODAEXCEL_H
#define UI_FORMCARICATURNODAEXCEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formCaricaTurnoDaExcel
{
public:
    QGridLayout *gridLayout;
    QPushButton *pbCaricaTurnoDaExcel;
    QLabel *label;
    QTableWidget *tableWidget;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *formCaricaTurnoDaExcel)
    {
        if (formCaricaTurnoDaExcel->objectName().isEmpty())
            formCaricaTurnoDaExcel->setObjectName(QStringLiteral("formCaricaTurnoDaExcel"));
        formCaricaTurnoDaExcel->resize(495, 314);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(formCaricaTurnoDaExcel->sizePolicy().hasHeightForWidth());
        formCaricaTurnoDaExcel->setSizePolicy(sizePolicy);
        formCaricaTurnoDaExcel->setMinimumSize(QSize(495, 314));
        formCaricaTurnoDaExcel->setMaximumSize(QSize(495, 314));
        gridLayout = new QGridLayout(formCaricaTurnoDaExcel);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pbCaricaTurnoDaExcel = new QPushButton(formCaricaTurnoDaExcel);
        pbCaricaTurnoDaExcel->setObjectName(QStringLiteral("pbCaricaTurnoDaExcel"));
        pbCaricaTurnoDaExcel->setAutoDefault(true);
        pbCaricaTurnoDaExcel->setDefault(true);

        gridLayout->addWidget(pbCaricaTurnoDaExcel, 0, 0, 1, 1);

        label = new QLabel(formCaricaTurnoDaExcel);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        tableWidget = new QTableWidget(formCaricaTurnoDaExcel);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(1, 3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(1, 4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(2, 3, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(2, 4, __qtablewidgetitem17);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEnabled(false);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(8);
        tableWidget->setFont(font);
        tableWidget->setFrameShape(QFrame::NoFrame);
        tableWidget->setFrameShadow(QFrame::Plain);
        tableWidget->horizontalHeader()->setDefaultSectionSize(70);
        tableWidget->horizontalHeader()->setStretchLastSection(false);
        tableWidget->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(formCaricaTurnoDaExcel);

        QMetaObject::connectSlotsByName(formCaricaTurnoDaExcel);
    } // setupUi

    void retranslateUi(QWidget *formCaricaTurnoDaExcel)
    {
        formCaricaTurnoDaExcel->setWindowTitle(QApplication::translate("formCaricaTurnoDaExcel", "Carica turno da foglio excel.", 0));
        pbCaricaTurnoDaExcel->setText(QApplication::translate("formCaricaTurnoDaExcel", "Carica un turno da floglio excel", 0));
        label->setText(QApplication::translate("formCaricaTurnoDaExcel", "La struttura del foglio excel deve essere del tipo seguente:", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("formCaricaTurnoDaExcel", "Matricola", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("formCaricaTurnoDaExcel", "Cognome", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("formCaricaTurnoDaExcel", "Nome", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("formCaricaTurnoDaExcel", "gg/mm/aa", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("formCaricaTurnoDaExcel", "gg/mm/aa", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("formCaricaTurnoDaExcel", "11000", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("formCaricaTurnoDaExcel", "New Row", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("formCaricaTurnoDaExcel", "Caio", 0));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(0, 3);
        ___qtablewidgetitem8->setText(QApplication::translate("formCaricaTurnoDaExcel", "06/11/2014", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(0, 4);
        ___qtablewidgetitem9->setText(QApplication::translate("formCaricaTurnoDaExcel", "07/11/2014", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(1, 3);
        ___qtablewidgetitem10->setText(QApplication::translate("formCaricaTurnoDaExcel", "lun", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(1, 4);
        ___qtablewidgetitem11->setText(QApplication::translate("formCaricaTurnoDaExcel", "mar", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(2, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("formCaricaTurnoDaExcel", "10000", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(2, 1);
        ___qtablewidgetitem13->setText(QApplication::translate("formCaricaTurnoDaExcel", "Tizio", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(2, 2);
        ___qtablewidgetitem14->setText(QApplication::translate("formCaricaTurnoDaExcel", "Caio", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(2, 3);
        ___qtablewidgetitem15->setText(QApplication::translate("formCaricaTurnoDaExcel", "M", 0));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(2, 4);
        ___qtablewidgetitem16->setText(QApplication::translate("formCaricaTurnoDaExcel", "P", 0));
        tableWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class formCaricaTurnoDaExcel: public Ui_formCaricaTurnoDaExcel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCARICATURNODAEXCEL_H
