# compilateur
CC := g++
# options de compilation
CFLAGS := -std=c++17 -g -Wall -Wextra -pedantic -ggdb -I $(PWD)/tomlplusplus -I $(PWD)/ # ! dernier include à modifier !

##############################################################################################################
# ! Veuillez absolument mettre le chemin de votre dossier contenant la bibliothèque toml++ comme ci-dessus ! #
##############################################################################################################

all : executable

executable : recupParam.o main.o circuit.o
	$(CC) -o $@ $^ `libpng-config --ldflags --libs`

%.o : %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) `libpng-config --cflags`



run : executable
	./executable

clean :
	rm -f *.o

memoire : executable
	valgrind --leak-check=full ./executable
