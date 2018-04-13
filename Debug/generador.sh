#!/bin/bash
k=0
for i in $@
do
	for j in 3 5
	do
	
	echo "Fichero: "$i " j: "$j" aux:" $k
	./P3Metaheuristics $i $j > fich$k"_"$j.txt
	./gnuplotSA.sh fich$k"_"$j.txt SA$k"_"$j.eps
	./gnuplotTS.sh fich$k"_"$j.txt TS$k"_"$j.eps
	./gnuplotGrasp.sh fich$k"_"$j.txt Grasp$k"_"$j.eps
	./gnuplotIG.sh fich$k"_"$j.txt IG$k"_"$j.eps

	
	done
	((k++))
done




