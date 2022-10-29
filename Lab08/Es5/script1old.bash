#!/bin/bash
#while read message
echo Ehilà, sono lo script1 e mio padre mi ha passato un $1

while [ 0 ]
do
	echo MyString1
	if [ message = s ]
	then
		break
	else
		sleep 5
		let arg="$1"+1
		./script2.bash "$arg" &
	fi
	echo Ora io, script1, leggo
	read message
	echo Ora io, script1, ho letto
done
echo Script 1 terminato
#done < "`./script2.bash < "o" &`"
