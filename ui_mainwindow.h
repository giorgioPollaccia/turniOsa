/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEsci;
    QAction *actionAnagrafica;
    QAction *actionAggiungi_Risorse;
    QAction *actionOpzioni;
    QAction *actionTabella_Matrici;
    QAction *actionPermessi;
    QAction *actionCarica_un_turno_da_un_foglio_excel;
    QAction *actionGenerazione_Tuno;
    QWidget *centralWidget;
    QGridLayout *_2;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuGestione_Risorse;
    QMenu *menuAvanzate;
    QMenu *menuGestioni_Permessi;
    QMenu *menuGestione_Turni;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(871, 604);
        actionEsci = new QAction(MainWindow);
        actionEsci->setObjectName(QStringLiteral("actionEsci"));
        actionAnagrafica = new QAction(MainWindow);
        actionAnagrafica->setObjectName(QStringLiteral("actionAnagrafica"));
        actionAggiungi_Risorse = new QAction(MainWindow);
        actionAggiungi_Risorse->setObjectName(QStringLiteral("actionAggiungi_Risorse"));
        actionOpzioni = new QAction(MainWindow);
        actionOpzioni->setObjectName(QStringLiteral("actionOpzioni"));
        actionTabella_Matrici = new QAction(MainWindow);
        actionTabella_Matrici->setObjectName(QStringLiteral("actionTabella_Matrici"));
        actionPermessi = new QAction(MainWindow);
        actionPermessi->setObjectName(QStringLiteral("actionPermessi"));
        actionCarica_un_turno_da_un_foglio_excel = new QAction(MainWindow);
        actionCarica_un_turno_da_un_foglio_excel->setObjectName(QStringLiteral("actionCarica_un_turno_da_un_foglio_excel"));
        actionGenerazione_Tuno = new QAction(MainWindow);
        actionGenerazione_Tuno->setObjectName(QStringLiteral("actionGenerazione_Tuno"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        actionGenerazione_Tuno->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        _2 = new QGridLayout(centralWidget);
        _2->setSpacing(2);
        _2->setContentsMargins(10, 10, 10, 10);
        _2->setObjectName(QStringLiteral("_2"));
        _2->setContentsMargins(2, 2, 2, 2);
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        _2->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 871, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuGestione_Risorse = new QMenu(menuBar);
        menuGestione_Risorse->setObjectName(QStringLiteral("menuGestione_Risorse"));
        menuAvanzate = new QMenu(menuBar);
        menuAvanzate->setObjectName(QStringLiteral("menuAvanzate"));
        menuGestioni_Permessi = new QMenu(menuBar);
        menuGestioni_Permessi->setObjectName(QStringLiteral("menuGestioni_Permessi"));
        menuGestione_Turni = new QMenu(menuBar);
        menuGestione_Turni->setObjectName(QStringLiteral("menuGestione_Turni"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuGestione_Risorse->menuAction());
        menuBar->addAction(menuGestioni_Permessi->menuAction());
        menuBar->addAction(menuGestione_Turni->menuAction());
        menuBar->addAction(menuAvanzate->menuAction());
        menuFile->addAction(actionEsci);
        menuGestione_Risorse->addAction(actionAnagrafica);
        menuGestione_Risorse->addAction(actionAggiungi_Risorse);
        menuAvanzate->addAction(actionTabella_Matrici);
        menuAvanzate->addAction(actionOpzioni);
        menuGestioni_Permessi->addAction(actionPermessi);
        menuGestione_Turni->addAction(actionGenerazione_Tuno);
        menuGestione_Turni->addAction(actionCarica_un_turno_da_un_foglio_excel);

        retranslateUi(MainWindow);
        QObject::connect(actionEsci, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TurniOSA", 0));
        actionEsci->setText(QApplication::translate("MainWindow", "Esci", 0));
        actionAnagrafica->setText(QApplication::translate("MainWindow", "Modifica Anagrafica", 0));
        actionAggiungi_Risorse->setText(QApplication::translate("MainWindow", "Aggiungi Risorse", 0));
        actionOpzioni->setText(QApplication::translate("MainWindow", "Opzioni file esterni", 0));
        actionTabella_Matrici->setText(QApplication::translate("MainWindow", "Tabella Matrici", 0));
        actionPermessi->setText(QApplication::translate("MainWindow", "Inserisci e/o modifica Permessi", 0));
        actionCarica_un_turno_da_un_foglio_excel->setText(QApplication::translate("MainWindow", "Carica un turno da un foglio excel...", 0));
        actionGenerazione_Tuno->setText(QApplication::translate("MainWindow", "Generazione Turno ...", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuGestione_Risorse->setTitle(QApplication::translate("MainWindow", "Risorse", 0));
        menuAvanzate->setTitle(QApplication::translate("MainWindow", "Avanzate", 0));
        menuGestioni_Permessi->setTitle(QApplication::translate("MainWindow", "Permessi", 0));
        menuGestione_Turni->setTitle(QApplication::translate("MainWindow", "Turni", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
