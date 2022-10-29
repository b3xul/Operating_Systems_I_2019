#!/bin/bash
while [ 0 ]
do
	read -s -n 1 -t 2 message  #-s non stampa input, -n 1 ritorna dopo un solo carattere senza attendere la newline, -t 2 attende solo 2 secondi sulla read
	if [ "$message" = "s" ]
	then
		echo Script terminati
		break
	else
		echo faccio partire 1
		./script1.bash
		echo faccio partire 2
		./script2.bash
	fi
done
