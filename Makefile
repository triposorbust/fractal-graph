randomwalk :	main.o	lattice.o
	gcc -o randomwalk main.o lattice.o

main.o : graph.h	lattice.h	main.c
	gcc -c main.c

lattice.o : graph.h	lattice.h	lattice.c
	gcc -c lattice.c

clean :
	rm randomwalk main.o lattice.o
