#!/bin/bash
#creare nuovo utente:
#adduser userDummy
#passwd userDummy
#effettuare login di userDummy:
#sudo login userDummy
#(passare a una shell di userDummy:
#su userDummy
#oppure /bin/bash essendo loggato come userDummy (solo $ nel terminal)
#N.B. 	whoami: chi è il proprietario della shell (anche se non loggato)
#	who: tutti gli utenti effettivamente loggati
#uscire da shell o effettuare logout: exit
if [[ $# -eq 0 || $# -eq 1 ]]
#oppure if [ $# -eq 0 -o $# -eq 1 ]
then
	echo 'Inserire 2 argomenti ( numero secondi e utente da controllare )'
	exit 1
fi
while [ 0 ]
do
	if [ "`who | grep -e $2`" ]
	then
		echo "$2 loggato"
		sleep $1
	else
		echo "$2 non loggato"
		break
	fi
done
