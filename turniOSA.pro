#-------------------------------------------------
#
# Project created by QtCreator 2014-09-07T18:44:16
#
#-------------------------------------------------

QT       += core gui
QT += sql


###include(C:/Qt/QtXlsxWriter-master/QtXlsxWriter-master/src/xlsx/qtxlsx.pri)
include(C:/Qt/QtXlsxWriter-master/src/xlsx/qtxlsx.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = turniOSA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    formanagrafica.cpp \
    formaggiungianagrafica.cpp \
    formopzionifileesterni.cpp \
    formvisualizzamatrici.cpp \
    formgestioneferie.cpp \
    formcalendario.cpp \
    formcaricaturnodaexcel.cpp \
    formgenerazioneturno.cpp \
    formorelavorateperdipendente.cpp

HEADERS  += mainwindow.h \
    formanagrafica.h \
    formaggiungianagrafica.h \
    formopzionifileesterni.h \
    formvisualizzamatrici.h \
    formgestioneferie.h \
    formcalendario.h \
    formcaricaturnodaexcel.h \
    formgenerazioneturno.h \
    formorelavorateperdipendente.h

FORMS    += mainwindow.ui \
    formanagrafica.ui \
    formaggiungianagrafica.ui \
    formopzionifileesterni.ui \
    formvisualizzamatrici.ui \
    formgestioneferie.ui \
    formcalendario.ui \
    formcaricaturnodaexcel.ui \
    formgenerazioneturno.ui \
    formorelavorateperdipendente.ui
