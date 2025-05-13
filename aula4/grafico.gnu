set terminal pngcairo enhanced font 'Arial,12' size 800,600
set output 'grafico.png'

set logscale x 10  # Escala logarítmica no eixo x (iterações)
set xlabel "Número de Iterações"
set ylabel "Erro Absoluto"
set title "Erro na Aproximação de Pi pela Série de Gregory-Leibniz"
set grid

plot "resultados.dat" using 1:3 with linespoints title "Erro Absoluto" lw 2 lc rgb "blue"
