CC = clang
CCP = mpicc
BIN = ./bin
LIB = ./lib
OBJ = ./obj
SRC = ./src
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

all: $(BIN)/prog

$(BIN)/prog: $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/main.o
	$(CCP) $(FLAGS) $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/main.o -o $@

$(BIN)/prog-seq: $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution_seq.o $(OBJ)/main_seq.o
	$(CC) $(FLAGS) $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution_seq.o $(OBJ)/main_seq.o -o $@

$(BIN)/tests-calcul_mat: $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/tests-calcul_mat.o
	$(COMPILER) $(FLAGS) $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/tests-calcul_mat.o -o $@

$(BIN)/tests-resolution: $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/tests-resolution.o
	$(COMPILER) $(FLAGS) $(OBJ)/gen.o $(OBJ)/convert.o $(OBJ)/calcul_mat.o $(OBJ)/resolution.o $(OBJ)/tests-resolution.o -o $@

.PHONY: clean exe kill

exe_prog:
	make clean
	make all
	mpiexec -n 1 $(BIN)/prog

exe_prog-seq:
	make clean
	make $(BIN)/prog-seq
	$(BIN)/prog-seq

exe_tests-calcul_mat:
	make clean
	make all
	$(BIN)/tests-calcul_mat

exe_tests-resolution:
	make clean
	make all
	$(BIN)/tests-resolution

clean:
	rm -f $(OBJ)/* $(BIN)/*

kill:
	pkill -9 prog