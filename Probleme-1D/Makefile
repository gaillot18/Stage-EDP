CC = clang
CCP = mpicc

BIN = ./Binaire
LIB = ./Librairie
OBJ = ./Objet
SRC = ./Source

FCC = Fonctions-communes
PRL1 = parallele-1
SQT1 = sequentiel-1
FCN = Fonctions-numeriques

FLAGS = -g0

ifeq ($(USE_MPI),1)
    COMPILER = $(CCP)
    MPI_FLAGS = -DUSE_MPI
else
    COMPILER = $(CC)
    MPI_FLAGS =
endif

.SUFFIXES: .o .c

# parallele-1

$(BIN)/parallele-1: $(OBJ)/$(PRL1)/affichage.o $(OBJ)/$(PRL1)/calcul-mat.o $(OBJ)/$(PRL1)/convert.o $(OBJ)/$(PRL1)/resolution.o $(OBJ)/$(PRL1)/parallele.o $(OBJ)/$(PRL1)/main.o
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

# sequentiel-1

$(BIN)/sequentiel-1: $(OBJ)/$(SQT1)/affichage.o $(OBJ)/$(SQT1)/calcul-mat.o $(OBJ)/$(SQT1)/convert.o $(OBJ)/$(SQT1)/resolution.o $(OBJ)/$(SQT1)/main.o
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

.PHONY: clean exe kill

sequentiel-1: $(BIN)/sequentiel-1
parallele-1: $(BIN)/parallele-1

exe-parallele-1:
	make clean
	make parallele-1
	mpiexec -n 1 $(BIN)/arallele-1

exe-sequentiel-1:
	make clean
	make sequentiel-1
	$(BIN)/exe-sequentiel-1

clean:
	rm -f ./texte/*.data ./texte/*.txt
	rm -f $(OBJ)/$(FCC)/$(PRL1)/*.o $(OBJ)/$(FCC)/$(SQT1)/*.o $(OBJ)/$(PRL1)/*.o $(OBJ)/$(SQT1)/*.o $(BIN)/*

kill:
	pkill -9 prog