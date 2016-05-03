select cognome,nome,sesso, a.matricola, idmatrice, progressivo from anagrafica as a join operatore_matriceturni as o on a.matricola=o.matricola where progressivo=1 and idmatrice="OSA_NOTTURNO"



//////////////////////////////////////  GESTIONE DELLE DATE
select strftime('%w', 'now')
select strftime('%Y', 'now')

//data del lunedi della settimana corrente
DATE('now','localtime','weekday 0','-6 days') 

//data del primo lunedi del mese di marzo 2016
SELECT date('2016-01-01','start of year','+2 months','weekday 1');

//numero della settimana della data indicata ne lsecondo parametro
select strftime('%W', '2016-02-22', 'localtime', 'weekday 0', '-6 days')

//data del primo lunedi del mese esplicitato nel primo parametro, in questo esempio febbraio
SELECT date('2016-02-01','start of month','+0 months','weekday 1');

//data delle prima domenica del mese esplicitato nel primo parametro, in questo esempio marzo
SELECT date('2016-03-01','start of month','+0 months','weekday 0');

//data del lunedi della settimana della data indicata dal primo parametro
select date('2016-02-08', 'weekday 0', '-6 days');