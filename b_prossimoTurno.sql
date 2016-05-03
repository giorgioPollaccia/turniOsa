select 
    operatore_matriceturni.matricola,cognome,nome, operatore_matriceturni.progressivo, operatore_matriceturni.idmatrice, matriceturni.progressivo, lun, mar, mer, gio, ven, sab, dom
from operatore_matriceturni,anagrafica 
join matriceturni on matriceturni.idmatrice=operatore_matriceturni.idmatrice and  anagrafica.matricola=operatore_matriceturni.matricola and matriceturni.progressivo= 2
join disponibilita on operatore_matriceturni.matricola=disponibilita.matricola 
where operatore_matriceturni.progressivo=1
