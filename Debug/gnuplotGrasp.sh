#!/bin/bash

FICHERO_ENTRADA="'$1'"

FICHERO_SALIDA="'$2'"

cat << _end_ | gnuplot
set terminal postscript eps color
set output $FICHERO_SALIDA
set key right bottom
set xrange [0:1000]
set xlabel "Iteracion"
set ylabel "Beneficio"
plot $FICHERO_ENTRADA using 5 t "Grasp current" w l, $FICHERO_ENTRADA using 6 t "Grasp best" w l
_end_
