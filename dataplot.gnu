#set terminal postfile       
#set output  "d1_plot.eps"    
set title "Latencies for different implementations"
set xlabel "Implementation"
set ylabel "Latency"
set style fill solid 0.25 border -1
set style boxplot outliers pointtype 7
set style data boxplot
set style boxplot nooutliers
set style boxplot separation 0.2
unset key
set output "plot.eps"
set output "plot.png"
plot "time.txt" using (1):1:(0.1):2
