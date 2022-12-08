#---------------------------------------------------------------------------+
# Fichier de commandes gnuplot : output/Tri_rapide/Tri_rapide_aleatoire.plt |
#---------------------------------------------------------------------------+
#
set style data lines
set xlabel "Nombre d'éléments"
set ylabel "Nombre d'opérations"
set title  "TRI RAPIDE"
set grid
set terminal png
set output 'output/Tri_rapide/png/Tri_rapide_aleatoire_op.png'
plot 'output/Tri_rapide/Tri_rapide_aleatoire.dat' using 1:2 title 'aleatoire'
set ylabel "Nombre de comparaisons"
set terminal png
set output 'output/Tri_rapide/png/Tri_rapide_aleatoire_cmp.png'
plot 'output/Tri_rapide/Tri_rapide_aleatoire.dat' using 1:3 title 'aleatoire'
quit
