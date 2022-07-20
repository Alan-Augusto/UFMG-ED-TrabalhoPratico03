
# ##### ###         ###   ###         ##  #     ##  #  # #
#   #   #  #       #   # #   #        ##  #     ##  ## # #
#   #   #  #       #   #     #       #  # #    #  # ## # #
#   #   ###  ##### #   #   ##  ##### #  # #    #  # # ## #
#   #   #          #   #     #       #### #    #### # ## #
#   #   #          #   # #   #       #  # #    #  # #  # #
#   #   #           ###   ###        #  # #### #  # #  # #


CC = g++
CXXFLAGS = -std=c++11 -g -Wall -pg

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLFER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/
OUTPUT_FOLDER = ./output/
GPROF_FOLDER = ./gprof/

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
	$(EXE) -i ./input/entrada_1.txt -o ./output/output_1.txt
	$(EXE) -i ./input/entrada_2.txt -o ./output/output_2.txt
	$(EXE) -i ./input/entrada_3.txt -o ./output/output_3.txt
	$(EXE) -i ./input/entrada_4.txt -o ./output/output_4.txt

clean: 
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLFER)* $(TARGET)
	@rm -rf $(OUTPUT_FOLDER)* 
	@rm -rf $(GPROF_FOLDER)*
	rm -rf gmon.out0
	clear

git:
	git add .
	@echo "your commit text: "; \
    read AGE ;\
	git commit -m "Update $(LOGDATE) - $$AGE"
	git push