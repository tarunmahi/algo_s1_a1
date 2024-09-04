set title "Sorting Algorithms Performance"  
set xlabel "Input Size"  
set ylabel "Time (seconds)"  
  
plot "test.txt" using 1:2 with lines title "Cycle Sort", 
    "test.txt" using 1:3 with lines title "Selection Sort", 
    "test.txt" using 1:4 with lines title "Quick Sort",  
    "test.txt" using 1:5 with lines title "Shell Sort", 
    "test.txt" using 1:6 with lines title "Odd-Even Sort"