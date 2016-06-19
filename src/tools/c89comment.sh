#!/bin/bash

 

cd $1

if [ -d orig ]; then
	echo "ERROR - PLEASE FIX IT!"
	exit 1
fi

mkdir -p orig

for filename in `ls *.c *.h 2>/dev/null` ;do
	cp $filename ./orig/$filename

	FILE=$(<$filename)
	rm $filename -f
	echo "${FILE}" | ./c89comments > $filename
done


