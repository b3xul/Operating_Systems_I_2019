#!/bin/bash
#tr '[:lower:]' '[:upper:]'
#${string#substring} Deletes shortest match of $substring from front of $string.
#${string/substring/replacement} Replace first match of $substring with $replacement.
if [ $# -lt 2 ]
then
	echo Inserire come primo argomento il path relativo della cartella da modificare tra virgolette e poi tutti i caratteri che si vogliono convertire in maiuscolo separati da spazi
fi

#echo path=$1

str=$*	#N.B. str con gli argomenti separati da spazi
#echo str=$str

str=${str#"$1 "}	#toglie il nome della cartella da analizzare dalla stringa contente gli argomenti (rimangono solo i caratteri)
#echo strmod=$str

args=($str)	#passa dalla stringa al vettore dei singoli caratteri corrispondente
#echo ${args[*]}

i=1
#N.B. using * runs all of the arguments together as a single argument with spaces, while @ preserves the breaks between them (even if some of the arguments themselves contain spaces). The difference isn't noticeable with echo!!! KILL ME

for newchar in ${args[*]}	#scorre i caratteri da trasformare in maiuscolo 
do
	echo sostituisco carattere numero $i:$newchar
	let i=i+1
	
	currentchar=$newchar

	#echo "hello world" | read first second ; echo $second $first N.B. NON FUNZIONA perchè se eseguo la read dopo la pipe essa viene eseguita in una subshell per cui dopo aver letto effettua la exit e scompare
	#per ovviare a questo problema si può usare: read first second <<< "hello world" ;echo $second $first
	oldIFS=$IFS
	#echo "$oldIFS"	
	IFS=$'\n'
	find "$1" -name "*$newchar*" -type f
	read -r -a matching_array <<< "`find "$1" -name "*$newchar*" -type f`"	#array contenente i file da modificare (-printf "%f" stamperebbe solo i nomi ma strada diversa)
	printf '%s\n' "${my_array[@]}"
	#echo "$IFS"
	#echo ${matching_array[0]}
	#echo ${matching_array[1]}

	newchar="$(echo "$newchar" | tr '[:lower:]' '[:upper:]')"	#trasforma in maiuscolo il carattere contenuto in char (N.B. per assegnazione non si mette il $)
	#echo "$newchar"

	for filepath in ${matching_array[*]}	#TO-DO fare sì che filename iteri su tutti gli elementi di matching array ma separandoli con il \n invece che con lo spazio
	do
		echo filepath=$filepath
		filename="${filepath##*/}"	#rimuove da filepath la più lunga (##, # invece rimuove la più corta) occorrenza del pattern "*/" ossia tutto il path tranne il filename
		#echo filepath=$filepath
		#echo filename=$filename
		newfilename="$(echo "$filename" | tr $currentchar $newchar)"
		#echo "newfilename=$newfilename"
		#echo filepath=$filepath
		newfilepath="${filepath/%$filename/$newfilename}"
		#echo newfilepath=$newfilepath
		#echo filepath=$filepath
		mv $filepath $newfilepath -v
		echo
	done
	IFS=$oldIFS
done

