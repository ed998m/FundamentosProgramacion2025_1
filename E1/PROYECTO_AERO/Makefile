# Compilador y flags
CC = gcc
CFLAGS = -Wall

CC = gcc
CFLAGS = -Wall
SRC = src
OBJ = main.o entrada_datos.o naca.o graficas.o aerodinamica.o exportar_perfil_formato_clasico.o

all: main

main: $(OBJ)
	$(CC) -o main $(OBJ) -lm

main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $(SRC)/main.c

entrada_datos.o: $(SRC)/entrada_datos.c
	$(CC) $(CFLAGS) -c $(SRC)/entrada_datos.c

naca.o: $(SRC)/naca.c
	$(CC) $(CFLAGS) -c $(SRC)/naca.c

graficas.o: $(SRC)/graficas.c
	$(CC) $(CFLAGS) -c $(SRC)/graficas.c

aerodinamica.o: $(SRC)/aerodinamica.c
	$(CC) $(CFLAGS) -c $(SRC)/aerodinamica.c

exportar_perfil_formato_clasico.o: $(SRC)/exportar_perfil_formato_clasico.c
	$(CC) $(CFLAGS) -c $(SRC)/exportar_perfil_formato_clasico.c

clean:
	del *.o main perfil.dat perfil_clasico.txt 2>nul || true
