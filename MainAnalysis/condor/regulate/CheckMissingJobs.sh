#!/usr/bin/env bash

rm -f missing.txt
rm -f existing.txt

tags=`ls */*.list | sed 's/\/.*$//'`

for tag in ${tags}; do
    indices=`cat ${tag}/${tag}.list | awk '{print $1}' | sed 's/\,.*$//'`

    for index in ${indices}; do
        if [ -f /data/submit/mitay/photons/condor/${tag}_${index}.root ]; then
            echo ${tag} ${index} >> existing.txt
        else
            echo ${index} >> ${tag}/${tag}.txt
        fi
    done
done

# confs=$(ls */*.conf | awk -F / '{print $2}' | sed 's/conf/root/g' | sed 's/^/\/data\/submit\/mitay\/photons\/condor\//')
# ls */*.conf | awk -F / '{print $2}' | sed 's/conf/root/g' | sed 's/^/\/data\/submit\/mitay\/photons\/condor\//' > temp.txt
# xargs -I % bash -c '[[ ! -e $1 ]] && echo "$1"' _ % < temp.txt > missing.txt
# rm temp.txt

# cat */*.list | awk -F / '{print $1}

# numbers=($(cat missing.txt | awk -F / '{print $7}' | awk -F . '{print $1}' | awk -F _ '{print $NF}'))
# folders=($(cat missing.txt | awk -F / '{print $7}' | awk -F . '{print $1}' | sed -r 's/(.*)\_.*/\1/'))

# cp /tmp/x509up_u168456 x509up_u168456

# old_folder="x"

# for i in ${!folders[@]}; do
#     if [ ${old_folder} != ${folders[i]} ]
#     then
#         if [ ${old_folder} != "x" ]
#         then
#             cd ${old_folder}
#             condor_submit SubmitCondor_${old_folder}.condor
#             cd ..
#         fi

#         echo "${numbers[i]}, ${folders[i]}_${numbers[i]}.conf" > "${folders[i]}/${folders[i]}.list"
#     else
#         echo "${numbers[i]}, ${folders[i]}_${numbers[i]}.conf" >> "${folders[i]}/${folders[i]}.list"
#     fi

#     old_folder=${folders[i]}
# done

# cd ${old_folder}
# condor_submit SubmitCondor_${old_folder}.condor
# cd ..