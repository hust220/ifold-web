set terminal postscript landscape "Helvetica" 14 
set output 'EnergyvsTemp.ps'
set noclip points
set clip one
set noclip two
set bar 1.000000
set border 31 lt -1 lw 1.000
set xdata
set ydata
set zdata
set x2data
set y2data
set boxwidth
set dummy x,y
set title "Potential Energy vs. Simulation Temperature"
set ylabel "Potential Energy" 
set xlabel "Simulation Temperature" 
set lmargin -1
set bmargin -1
set rmargin -1
set tmargin -1
set locale "C"
set style line 1 lt 3  lw 3  pt 1 ps 1
plot "EnergyvsTemp.dat" title "Plot of Energy vs Temperature" w linespoints linestyle 1
#    EOF
