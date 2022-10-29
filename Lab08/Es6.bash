#!/bin/bash
RamFree="`grep MemFree /proc/meminfo`"
RamFree=${RamFree//[!0-9]/}	#Parameter substitution: toglie tutte le occorrenze di caratteri diversi da cifre
#RamFree=${RamFree#"MemFree: "}
#RamFree=${RamFree#"kB"}
#echo $RamFree

RamSize="`grep MemTotal /proc/meminfo`"
RamSize=${RamSize//[!0-9]/}
#echo $RamSize

let RamUsed=$RamSize-$RamFree
#echo $RamUsed
let percentUsed=$RamUsed*100/$RamSize
#echo $percentUsed
let RamUsedMB=$RamUsed/1024
let RamSizeMB=$RamSize/1024

echo "Stai usando $RamUsed kB ($RamUsedMB MB) su un totale di $RamSize kB ($RamSizeMB MB) di RAM ($percentUsed%)"
