#!/bin/bash

i=1

while read line
do

	jobid[${i}]=`echo $line|awk '{print $1}'`
	submit[${i}]=`echo $line|awk '{print $2}'`
	wait[$i]=`echo $line|awk '{print $3}'`
	exec[$i]=`echo $line|awk '{print $4}'`
	cores[$i]=`echo $line|awk '{print $5}'`

	start[${i}]=`expr ${submit[i]} + ${wait[i]}`
	end[${i}]=`expr ${start[i]} + ${exec[i]}`
	echo ${start[i]} ${cores[i]} ${end[i]} >> ./impulses-util_system.log

	i=`expr $i + 1`
done < "cons_res_lay_no_overhead.swf"

#for i in `seq 1 10`; do 
#	echo ${jobid[$i]}
#	echo ${start[$i]}
#	echo ${end[$i]}
	#echo ${submit[$i]}
	#echo ${wait[$i]}
	#echo ${exec[$i]}
	#echo ${cores[$i]}
#done

#for j in `seq ${start[1]} ${end[230]}`; do
#for j in `seq 1295947914 1295947924`; do  
#	used_cpus[${j}]=0
#	for k in `seq 1 230`; do
#		if [ $j -ge ${start[${k}]} -a $j -le ${end[${k}]} ]; then
#			used_cpus[${j}]=`expr ${used_cpus[${j}]} + ${cores[${k}]}`

#		fi

#	done	

#	echo $j ${used_cpus[${j}]} >> ./util_system.log
#done


for j in `seq ${start[1]} ${end[230]}`; do
        used_cpus[${j}]=0
        for k in `seq 1 230`; do
                if [ "$j" -ge "${start[${k}]}" -a "$j" -lt "${end[${k}]}" ]; then
                        used_cpus[${j}]=`expr ${used_cpus[${j}]} + ${cores[${k}]}`
                fi

        done
        echo $j ${used_cpus[${j}]} >> ./util_system.log
done

