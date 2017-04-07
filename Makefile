.PHONY: all load debug clean test

CC=gcc
C_FILES=load.c
C_INV_FILES=load-inverse.c
DBG_FLAGS=-O0 -g
FLAGS=-O3
OUT=load
DBG=dbg
BIN_DIR=./bin
TXT_O=out.txt


all: load

load: $(BIN_DIR)/LVX.UNALIGNED.$(OUT) $(BIN_DIR)/LXVD2X.UNALIGNED.$(OUT) $(BIN_DIR)/LVX.ALIGNED.$(OUT) $(BIN_DIR)/LXVD2X.ALIGNED.$(OUT) 

$(BIN_DIR)/LVX.UNALIGNED.$(OUT): $(C_FILES)
		mkdir -p $(BIN_DIR)
		$(CC) $(C_FILES) -o $(BIN_DIR)/LVX.UNALIGNED.$(OUT) $(FLAGS) -DLVX -DUNALIGNED

$(BIN_DIR)/LXVD2X.UNALIGNED.$(OUT): $(C_FILES)
		mkdir -p $(BIN_DIR)
		$(CC) $(C_FILES) -o $(BIN_DIR)/LXVD2X.UNALIGNED.$(OUT) $(FLAGS) -DLXVD2X -DUNALIGNED

$(BIN_DIR)/LVX.ALIGNED.$(OUT): $(C_FILES)
		mkdir -p $(BIN_DIR)
		$(CC) $(C_FILES) -o $(BIN_DIR)/LVX.ALIGNED.$(OUT) $(FLAGS) -DLVX -DALIGNED

$(BIN_DIR)/LXVD2X.ALIGNED.$(OUT): $(C_FILES)
		mkdir -p $(BIN_DIR)
		$(CC) $(C_FILES) -o $(BIN_DIR)/LXVD2X.ALIGNED.$(OUT) $(FLAGS) -DLXVD2X -DALIGNED

perf: load
		sh plot_results.sh "Load vector compare" LXVD2X.UNALIGNED.$(OUT) LVX.UNALIGNED.$(OUT) LXVD2X.ALIGNED.$(OUT) LVX.ALIGNED.$(OUT) $(BIN_DIR)

clean:
		rm -rf $(BIN_DIR)
		rm -rf *.dat
		rm -rf *.png
