CC = clang
BIN = ./bin
LIB = ./lib
OBJ = ./obj
SRC = ./src
FLAGS = -fopenmp

.SUFFIXES: .o .c

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(BIN)/prog $(BIN)/tests-calcul_mat $(BIN)/tests-resolution

$(BIN)/prog: $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/main.o
	$(CC) $(FLAGS) $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/main.o -o $@

$(BIN)/tests-calcul_mat: $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/tests-calcul_mat.o
	$(CC) $(FLAGS) $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/tests-calcul_mat.o -o $@

$(BIN)/tests-resolution: $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/tests-resolution.o
	$(CC) $(FLAGS) $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/tests-resolution.o -o $@

.PHONY: clean exe kill

exe_prog:
	make clean
	make all
	OMP_NUM_THREADS=6 $(BIN)/prog

exe_tests-calcul_mat:
	make clean
	make all
	OMP_NUM_THREADS=1 $(BIN)/tests-calcul_mat

exe_tests-resolution:
	make clean
	make all
	OMP_NUM_THREADS=1 $(BIN)/tests-resolution

clean:
	rm -f $(OBJ)/* $(BIN)/*

kill:
	pkill -9 prog