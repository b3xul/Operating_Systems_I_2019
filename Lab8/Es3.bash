#!/bin/bash
#se il pacchetto mandato viene ricevuto (stringa non nulla) allora sono connesso

#`esegue comandi`
#"``" piazza lo stdout dei comandi eseguiti in una stringa

#eseguo un solo ping  (-c 1) di google.com, e ne ridireziono lo stderr a dev/null (non mi interessa sapere il tipo di errore, mi basta che la condizione dell'if sia falsa
#lo stdout invece lo prende grep e verifica se è presente la stringa "1 received"

#if [ "`ping google.com -c 1 2> /dev/null | grep -e "1 received"`" ]	N.B. Tutto racchiuso tra "" per interpretarla come stringa

#in alternativa vedo se il conteggio delle linee ritornate da grep è = 1
if [ `ping google.com -c 1 2> /dev/null | grep -e "1 received" -c` -eq 1 ]  
then
	echo Sei connesso a internet!
else
	echo Non sei connesso a internet!
fi
