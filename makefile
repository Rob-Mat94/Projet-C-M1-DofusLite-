CPP=g++
CFLAGS= -I$(HEADDIR) -g -Wall
# option pour l'interface graphique sfml
GFLAGS= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Les différents dossiers
SRCDIR= src
HEADDIR= includes
LIBDIR= obj
BINDIR= bin

# L'exécutable
BIN= game

# Où trouver les différents sources *.cpp qu'il faudra compiler pour créer les objets correspondants
SRC= $(wildcard $(SRCDIR)/*.cpp)
OBJ= $(SRC:$(SRCDIR)/%.cpp=$(LIBDIR)/%.o) $(LIBDIR)/main.o

# Création de l'exécutable
$(BINDIR)/$(BIN): $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS) $(GFLAGS)

# Création des différents *.o à partir des *.cpp
$(LIBDIR)/main.o: main.cpp
	$(CPP) -o $@ -c $< $(CFLAGS)

$(LIBDIR)/%.o: $(SRCDIR)/%.cpp $(HEADDIR)/%.h
	$(CPP) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(LIBDIR)/*.o
	rm -f *.o

Clean: clean
	rm -f $(BINDIR)/*
