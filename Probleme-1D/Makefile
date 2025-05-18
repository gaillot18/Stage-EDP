CC = clang
CCP = mpicc

BIN = ./Binaires
LIB = ./Librairies
OBJ = ./Objets
SRC = ./Sources

FCC = Fonctions-communes
PRL1 = parallele-1
SQT1 = sequentiel-1
SQT2 = sequentiel-2
FCN = Fonctions-numeriques
TXT = Textes

FLAGS = -g0

ifeq ($(USE_MPI),1)
    COMPILER = $(CCP)
    MPI_FLAGS = -DUSE_MPI
else
    COMPILER = $(CC)
    MPI_FLAGS =
endif

.SUFFIXES: .o .c



# ======================================================
# Création de l'exécutable sequentiel-1
# ======================================================
$(BIN)/$(SQT1): $(OBJ)/$(SQT1)/affichage.o $(OBJ)/$(SQT1)/calcul-mat.o $(OBJ)/$(SQT1)/convert.o $(OBJ)/$(SQT1)/resolution.o $(OBJ)/$(SQT1)/main.o
	$(CC) $(FLAGS) $^ -o $@

$(OBJ)/$(SQT1)/main.o: $(SRC)/$(SQT1)/main.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT1)/resolution.o: $(SRC)/$(SQT1)/resolution.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT1)/affichage.o: ../$(FCC)/affichage.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT1)/calcul-mat.o: ../$(FCC)/calcul-mat.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT1)/convert.o: ../$(FCC)/convert.c
	$(CC) $(FLAGS) -c $< -o $@



# ======================================================
# Création de l'exécutable parallele-1
# ======================================================
$(BIN)/$(PRL1): $(OBJ)/$(PRL1)/affichage.o $(OBJ)/$(PRL1)/calcul-mat.o $(OBJ)/$(PRL1)/convert.o $(OBJ)/$(PRL1)/resolution.o $(OBJ)/$(PRL1)/parallele.o $(OBJ)/$(PRL1)/main.o
	$(CCP) $(MPI_FLAGS) $(FLAGS) $^ -o $@

$(OBJ)/$(PRL1)/main.o: $(SRC)/$(PRL1)/main.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(PRL1)/parallele.o: $(SRC)/$(PRL1)/parallele.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(PRL1)/resolution.o: $(SRC)/$(PRL1)/resolution.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(PRL1)/affichage.o: ../$(FCC)/affichage.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(PRL1)/calcul-mat.o: ../$(FCC)/calcul-mat.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(PRL1)/convert.o: ../$(FCC)/convert.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@



# ======================================================
# Création de l'exécutable sequentiel-2
# ======================================================
$(BIN)/$(SQT2): $(OBJ)/$(SQT2)/affichage.o $(OBJ)/$(SQT2)/calcul-mat.o $(OBJ)/$(SQT2)/convert.o $(OBJ)/$(SQT2)/resolution.o $(OBJ)/$(SQT2)/affichage-struct.o $(OBJ)/$(SQT2)/main.o
	$(CC) $(FLAGS) $^ -o $@

$(OBJ)/$(SQT2)/main.o: $(SRC)/$(SQT2)/main.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT2)/resolution.o: $(SRC)/$(SQT2)/resolution.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT2)/affichage-struct.o: $(SRC)/$(SQT2)/affichage-struct.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT2)/affichage.o: ../$(FCC)/affichage.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT2)/calcul-mat.o: ../$(FCC)/calcul-mat.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT2)/convert.o: ../$(FCC)/convert.c
	$(CC) $(FLAGS) -c $< -o $@



.PHONY: clean exe kill

all: clean sequentiel-1 parallele-1 sequentiel-2

sequentiel-1: $(BIN)/$(SQT1)

parallele-1: $(BIN)/$(PRL1)

sequentiel-2: $(BIN)/$(SQT2)

exe-sequentiel-1:
	make $(SQT1)
	$(BIN)/$(SQT1)

exe-parallele-1:
	make $(PRL1)
	mpiexec -n 4 $(BIN)/$(PRL1)

exe-sequentiel-2:
	make $(SQT2)
	$(BIN)/$(SQT2) 2

clean:
	rm -f ./texte/*.data ./texte/*.txt
	rm -f $(OBJ)/$(SQT1)/*.o $(OBJ)/$(PRL1)/*.o $(OBJ)/$(SQT2)/*.o $(BIN)/* $(TXT)/resultats.txt

kill:
	pkill -9 prog