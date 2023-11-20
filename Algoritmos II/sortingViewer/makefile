main: main.o sorting.o arrayAndFileManipulation.o
	gcc -Wall -o $@ $^

sorting.o: sorting.c sorting.h
	gcc -Wall sorting.c -o sorting.o -c

arrayAndFileManipulation.o: arrayAndFileManipulation.c arrayAndFileManipulation.h
	gcc -Wall arrayAndFileManipulation.c -o arrayAndFileManipulation.o -c

main.o: main.c
	gcc -Wall main.c -o main.o -c