# Demonstriert einen Plot mit gnuplot und dem Here-Dokument
# Name : aplotstyles1
# Datei zum Plotten
FILE=messdat.dat
# Verschiedene Styles zum Testen
STYLES="lines points linespoints dots impulses steps fsteps histeps boxes"
for var in $STYLES
do
gnuplot -persist <<PLOT
set xrange [0:6]
set yrange [-20:40]
set xlabel "Monat"
set ylabel "Grad/Celcius"
set style data $var
set title "Temperatur-Daten 1999–2002"
# Falls Sie eine Postscript-Datei erstellen wollen ...
# set terminal postscript
# set output "messdat.ps"
plot "$FILE" using 1:2 t "1999" ,\
"$FILE" using 1:3 t "2000" ,\
"$FILE" using 1:4 t "2001" ,\
"$FILE" using 1:5 t "2002"
quit
PLOT
done

