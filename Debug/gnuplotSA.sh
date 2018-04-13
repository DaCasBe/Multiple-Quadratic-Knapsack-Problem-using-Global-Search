#!/bin/bash

FICHERO_ENTRADA="'$1'"

FICHERO_SALIDA="'$2'"

cat << _end_ | gnuplot
set terminal postscript eps color
set output $FICHERO_SALIDA
set key right bottom
set xlabel "Iteracion"
set ylabel "Beneficio"
plot $FICHERO_ENTRADA using 1 t "SA current" w l, $FICHERO_ENTRADA using 2 t "SA best" w l
_end_
