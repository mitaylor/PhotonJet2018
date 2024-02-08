#!/usr/bin/env bash

rm -f missing.txt
rm -f existing.txt

tags=`ls */*.list | sed 's/\/.*$//'`

for tag in ${tags}; do
    indices=`cat ${tag}/${tag}.list | awk '{print $1}' | sed 's/\,.*$//'`
    rm existing.txt
    rm ${tag}/${tag}.txt

    for index in ${indices}; do
        if [ -f /data/submit/mitay/photons/condor/${tag}_${index}.root ]; then
            echo ${tag} ${index} >> existing.txt
        else
            echo ${index} >> ${tag}/${tag}.txt
        fi
    done
done