#====================================================
#ESTRUTURAS DE DADOS - 2022/01
#SISTEMAS DE INFORMAÇÃO
#ALAN AUGUSTO MARTINS CAMPOS
#TRABALHO PRÁTICO 02- ORDEM LEXICOGRÁFICA
#====================================================

CC = g++
CXXFLAGS = -std=c++11 -g -Wall -pg

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLFER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/
OUTPUT_FOLDER = ./output/

# all sourcers, obs, and header files
MAIN = main
TARGET = main
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))
LOGDATE = $(shell date +"%b/%d at %kh:%Mm")
EXE = $(BIN_FOLFER)main

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all: comp run

comp: $(OBJ) 
	$(CC) $(CXXFLAGS) -o $(BIN_FOLFER)$(TARGET) $(OBJ)
	
run:
	$(EXE) -i ./input/1.tst.i -o ./output/output1.txt -m 4 -s 5
	$(EXE) -i ./input/2.tst.i -o ./output/output2.txt -m 4 -s 5
	$(EXE) -i ./input/3.tst.i -o ./output/output3.txt -m 4 -s 5
	$(EXE) -i ./input/4.tst.i -o ./output/output4.txt -m 4 -s 5
	$(EXE) -i ./input/5.tst.i -o ./output/output5.txt -m 4 -s 5
	$(EXE) -i ./input/6.tst.i -o ./output/output6.txt -m 4 -s 5
	$(EXE) -i ./input/7.tst.i -o ./output/output7.txt -m 4 -s 5
	$(EXE) -i ./input/8.tst.i -o ./output/output8.txt -m 4 -s 5
	$(EXE) -i ./input/9.tst.i -o ./output/output9.txt -m 4 -s 5
	$(EXE) -i ./input/10.tst.i -o ./output/output10.txt -m 4 -s 5

clean: 
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLFER)* $(TARGET)
	@rm -rf $(OUTPUT_FOLDER)* 
	rm -rf gmon.out
	rm -rf gprof.txt
	clear