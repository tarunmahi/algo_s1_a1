set terminal png size 1280,941 crop
set output "test.png"

set xlabel "time"
set ylabel "v"
set title "values"

plot "test.txt"