# Technical_Test_Developer
## COMPILING AND EXEC INSTRUCTIONS
## SPANISH BELOW
--------------------------------

Compile the normal program (without tests):

gcc -o addnum addnum.c -lpthread


Execute the program:

./addnum -f configfile/cfg.txt


Or to see the help:

./addnum -h


Check for leaks:

gcc -g3 -o addnum addnum.c -lpthread
valgrind --leak-check=full --show-leak-kinds=all ./addnum -f configfile/cfg.txt
--------------------------------
## INSTRUCCIONES DE COMPILACION Y EJECUCION
## ENGLISH ABOVE
--------------------------------

Compilar el programa normal (sin pruebas):

gcc -o addnum addnum.c -lpthread


Ejecutar el programa:

./addnum -f cfg.txt


O para ver la ayuda

./addnum -h


Comprobar leaks:

gcc -g3 -o addnum addnum.c -lpthread
valgrind --leak-check=full --show-leak-kinds=all ./addnum -f configfile/cfg.txt

