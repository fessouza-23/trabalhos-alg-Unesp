main: main.o sorting.o arrayAndFileManipulation.o
	gcc -o $@ $^

sorting.o: sorting.c sorting.h
	gcc sorting.c -o sorting.o -c

arrayAndFileManipulation.o: arrayAndFileManipulation.c arrayAndFileManipulation.h
	gcc arrayAndFileManipulation.c -o arrayAndFileManipulation.o -c

main.o: main.c
	gcc main.c -o main.o -c