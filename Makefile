# compilateur
CC := g++
# options de compilation
CFLAGS := -std=c++17 -g -Wall -Wextra -pedantic -ggdb -I /home/linux/Documents/Barjokart/tomlplusplus

##############################################################################################################
# ! Veuillez absolument mettre le chemin de votre dossier contenant la bibliothèque toml++ comme ci-dessus ! #
##############################################################################################################

all : executable

executable : recupParam.o main.o
	$(CC) -o $@ $^

%.o : %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)



run : executable
	./executable

clean :
	rm -f *.o

memoire : executable
	valgrind --leak-check=full ./executable
