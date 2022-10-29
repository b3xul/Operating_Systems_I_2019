#!/bin/bash
#while read message
echo Ehilà sono lo script2 e mio padre mi ha passato $1
while [ 0 ]
do
        echo MyString2
        if [ message = s ]
        then
                break
	else
		sleep 5
		let arg="$1"+1
		./script1.bash "$arg" &
	fi
	echo Ora io, script2, leggo
        read message
        echo Ora io, script2, ho letto	
done
echo Script2 terminato
#done < "`./script1.bash < "o" &`"
