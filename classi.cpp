#include "classi.h"








impiegatoOsa::impiegatoOsa( QString matricola, QString cognome, QString nome, QString sesso, bool abilitato)
{
   this->matricola= matricola;
   this->cognome= cognome;
   this->nome= nome;
   this->sesso= sesso;
   this->abilitatoTurno= abilitato;

}

QString impiegatoOsa::get_matricola()
{
    return this->matricola;
}



QString impiegatoOsa::get_cognome()
{
    return this->cognome;
}
QString impiegatoOsa::get_nome()
{
    return this->nome;
}
QString impiegatoOsa::get_sesso()
{
    return this->sesso;
}
