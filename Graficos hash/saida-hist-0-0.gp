set term png
set output "saida-hist-0-0.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 2693466557 # 1479936 Media 1819.99) - Fase  0 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:4603] "saida-hist-0-0.gpdat" u 3:4 w boxes t ""
