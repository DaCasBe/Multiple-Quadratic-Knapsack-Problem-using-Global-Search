#!/bin/bash

FICHERO_ENTRADA="'$1'"

FICHERO_SALIDA="'$2'"

cat << _end_ | gnuplot
set terminal postscript eps color
set output $FICHERO_SALIDA
set key right bottom
set xrange [0:500]
set xlabel "Iteracion"
set ylabel "Beneficio"
plot $FICHERO_ENTRADA using 3 t "TS current" w l, $FICHERO_ENTRADA using 4 t "TS best" w l
_end_
