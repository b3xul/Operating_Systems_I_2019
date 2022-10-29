#!/bin/bash
if [ $# -lt 2 ]
then
        echo "Inserire come primo argomento il path relativo della cartella da modificare tra virgolette e poi tutti i caratteri che si vogliono convertire in maiuscolo separati da spazi"
fi
echo "${@:2}"
for oldchar in "${@:2}"
do
	echo "$oldchar"
	newchar="$(echo "$oldchar" | tr '[:lower:]' '[:upper:]')"
    echo "$newchar"
	find "$1" -name "*$oldchar*" -type f | rename 'y/"{$oldchar}"/"${newchar}"/' -n
	#for f in $(find "$1" -name "*$oldchar*" -type f)
	#do
    #    newchar="$(echo "$oldchar" | tr '[:lower:]' '[:upper:]')"
    #    echo newchar
	#	rename 'y/"$oldchar"/"$newchar"/' -n
    #done
done
