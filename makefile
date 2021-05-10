
CC = gcc
CFLAGS = -g

project : maininput.c vec.c Stations.c dynamicheap.c
	$(CC) $(CFLAGS) maininput.c vec.c Stations.c dynamicheap.c -o project  

