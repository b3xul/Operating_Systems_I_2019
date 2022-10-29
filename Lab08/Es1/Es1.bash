#!/bin/bash
#case...esac=switch sul valore della variabile $# (argc) (in realtà qua va bene un if solo (if [ $# -eq 0])
case $# in
	0)	echo Inserire almeno un argomento
		exit 1;;
esac

#backquotes(backtick) ` (AltGr+') raccolgono stdout di un comando eseguito nella shell (equivale a $(echo...) )
#(tilde ~ (AltGr+ì))
#tr= translate= substitute : con ' '
#ossia PATH passerà da essere: /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
#		     a essere: /usr/local/sbin /usr/local/bin /usr/sbin /usr/bin /sbin /bin /usr/games /usr/local/games
#e quindi i assumerà man mano i valori dei vari path
for i in `echo $PATH | tr ':' ' '`
do
	if test -e $i/$1 #se l'argomento ($i: path presente in $PATH / $1: nomefile passato come argomento) esiste
		then
		if test -f $i/$1 #se l'argomento è un file regolare	
			then echo $i/$1	#stampa il percorso
		fi
	fi
done
