CC = clang
CCP = mpicc

BIN = ./binaire
LIB = ./librairie
OBJ = ./objet
SRC = ./source

FCT = fonctions-generales
PRL = parallele
SQT = sequentiel

FLAGS = -g0

ifeq ($(USE_MPI),1)
    COMPILER = $(CCP)
    MPI_FLAGS = -DUSE_MPI
else
    COMPILER = $(CC)
    MPI_FLAGS =
endif

.SUFFIXES: .o .c

$(OBJ)/%.o: $(SRC)/%.c
	$(COMPILER) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

# parallele

$(BIN)/exe-parallele: $(OBJ)/$(FCT)/$(PRL)/affichage.o $(OBJ)/$(FCT)/$(PRL)/calcul-mat.o $(OBJ)/$(FCT)/$(PRL)/convert.o $(OBJ)/$(PRL)/resolution.o $(OBJ)/$(PRL)/parallele.o $(OBJ)/$(PRL)/main.o
	$(CCP) $(MPI_FLAGS) $(FLAGS) $^ -o $@

$(OBJ)/$(PRL)/main.o: $(SRC)/$(PRL)/main.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(PRL)/parallele.o: $(SRC)/$(PRL)/parallele.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(PRL)/resolution.o: $(SRC)/$(PRL)/resolution.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

# sequentiel

$(BIN)/exe-sequentiel: $(OBJ)/$(FCT)/$(SQT)/affichage.o $(OBJ)/$(FCT)/$(SQT)/calcul-mat.o $(OBJ)/$(FCT)/$(SQT)/convert.o $(OBJ)/$(SQT)/resolution.o $(OBJ)/$(SQT)/main.o
	$(CC) $(FLAGS) $^ -o $@

$(OBJ)/$(SQT)/main.o: $(SRC)/$(SQT)/main.c
	$(CC) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(SQT)/resolution.o: $(SRC)/$(SQT)/resolution.c
	$(CC) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

# fonctions-generales

$(OBJ)/$(FCT)/$(PRL)/affichage.o: $(SRC)/$(FCT)/affichage.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(FCT)/$(SQT)/affichage.o: $(SRC)/$(FCT)/affichage.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(FCT)/$(PRL)/calcul-mat.o: $(SRC)/$(FCT)/calcul-mat.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(FCT)/$(SQT)/calcul-mat.o: $(SRC)/$(FCT)/calcul-mat.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ)/$(FCT)/$(PRL)/convert.o: $(SRC)/$(FCT)/convert.c
	$(CCP) $(MPI_FLAGS) $(FLAGS) -c $< -o $@

$(OBJ)/$(FCT)/$(SQT)/convert.o: $(SRC)/$(FCT)/convert.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: lean exe kill

sequentiel: $(BIN)/exe-sequentiel
parallele: $(BIN)/exe-parallele

exe-parallele:
	make clean
	make parallele
	mpiexec -n 1 $(BIN)/exe-parallele

exe-sequentiel:
	make clean
	make sequentiel
	$(BIN)/exe-sequentiel

clean:
	rm -f ./texte/*.data ./texte/*.txt
	rm -f $(OBJ)/$(FCT)/$(PRL)/*.o $(OBJ)/$(FCT)/$(SQT)/*.o $(OBJ)/$(PRL)/*.o $(OBJ)/$(SQT)/*.o $(BIN)/*

kill:
	pkill -9 prog