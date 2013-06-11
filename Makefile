randomwalk :	main.o	lattice.o	options.o
	gcc -o randomwalk main.o lattice.o options.o

main.o : graph.h	lattice.h	main.c
	gcc -c main.c

lattice.o : graph.h	lattice.h	lattice.c
	gcc -c lattice.c

options.o :	options.c options.h
	gcc -c options.c

clean :
	rm randomwalk main.o lattice.o options.o
