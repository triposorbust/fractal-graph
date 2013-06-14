randomwalk :	main.o	lattice.o	options.o	densities.o
	gcc -o randomwalk main.o lattice.o options.o densities.o

main.o : graph.h	lattice.h	main.c
	gcc -c main.c

lattice.o : graph.h	lattice.h	lattice.c
	gcc -c lattice.c

densities.o :	graph.h	densities.h	densities.c
	gcc -c densities.c

options.o :	options.c options.h
	gcc -c options.c

clean :
	rm *.o randomwalk
