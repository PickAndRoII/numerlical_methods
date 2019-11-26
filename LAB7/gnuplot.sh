#!/usr/bin/env bash
set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
set output "cos.eps" # nazwa pliku wynikowego
#set title "węzły równoodległe" # tytul wykresu
set xlabel "x" # etykieta osi OX
set ylabel "f(x)" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej
set xrange [-5:5]
plot 'dane.dat' using 1:2 with lines title "f(x)=1/(1+x^2)", 'dane.dat' using 1:3 with lines title "W_6(x)"
#replot "dane2.dat" using 1:3 with points


# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"
