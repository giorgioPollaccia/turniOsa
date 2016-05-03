#ifndef CLASSI_H
#define CLASSI_H
#include <QString>


class turno
{
private:
     QList <QString> t;
};

class impiegatoOsa
{
public:
    impiegatoOsa(QString, QString, QString,  bool);
    QString get_matricola();
    QString get_cognome();
    QString get_sesso();
private:
    QString matricola, cognome, sesso;
    bool abilitatoTurno;
    QString idMatriceTurno;
    QString turnoSeme;
};


class osa
{
private:
    QList<impiegatoOsa> osaList;
public:
    osa();
    caricaDaDataBase();
};




#endif // CLASSI_H
