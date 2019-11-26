#!/usr/bin/env bash
set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
set xlabel "i" # etykieta osi OX
set ylabel "y(i)" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej


set output "1.eps" # nazwa pliku wynikowego
set title "k=8" # tytul wykresu
plot 'dane.dat' using 1:2 with lines title "Re(FFT[y(i)]", 'dane.dat' using 1:3 with lines title "Im(FFT[y(i)]"


