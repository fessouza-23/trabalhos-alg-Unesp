OBJ_DIR = obj
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

clinica: $(OBJ_DIR)/main.o $(OBJ_DIR)/cliutils.o $(OBJ_DIR)/cliente.o $(OBJ_DIR)/consulta.o
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/cliutils.o $(OBJ_DIR)/cliente.o $(OBJ_DIR)/consulta.o -o $(BIN_DIR)/clinica -w

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/cliutils.h $(INCLUDE_DIR)/cliente.h $(INCLUDE_DIR)/consulta.h | $(OBJ_DIR)
	gcc -I $(INCLUDE_DIR) -c $< -o $@ -w

$(OBJ_DIR)/cliutils.o: $(SRC_DIR)/cliutils.c $(INCLUDE_DIR)/cliutils.h | $(OBJ_DIR)
	gcc -I $(INCLUDE_DIR) -c $< -o $@ -w

$(OBJ_DIR)/cliente.o: $(SRC_DIR)/cliente.c $(INCLUDE_DIR)/cliutils.h $(INCLUDE_DIR)/cliente.h | $(OBJ_DIR)
	gcc -I $(INCLUDE_DIR) -c $< -o $@ -w

$(OBJ_DIR)/consulta.o: $(SRC_DIR)/consulta.c $(INCLUDE_DIR)/cliutils.h $(INCLUDE_DIR)/consulta.h | $(OBJ_DIR)
	gcc -I $(INCLUDE_DIR) -c $< -o $@ -w

# Create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
