OBJ_DIR = obj
SRC_DIR = src
INCLUDE_DIR = include

clinica: $(OBJ_DIR)/main.o $(OBJ_DIR)/cliutils.o $(OBJ_DIR)/cliente.o $(OBJ_DIR)/consulta.o
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/cliutils.o $(OBJ_DIR)/cliente.o $(OBJ_DIR)/consulta.o $(SRC_DIR)/my.res -o clinica -w

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/cliutils.h $(INCLUDE_DIR)/cliente.h $(INCLUDE_DIR)/consulta.h | $(OBJ_DIR)
	gcc -I $(INCLUDE_DIR) -c $< -o $@ -w

$(OBJ_DIR)/cliutils.o: $(SRC_DIR)/cliutils.c $(INCLUDE_DIR)/cliutils.h | $(OBJ_DIR)
	gcc -I $(INCLUDE_DIR) -c $< -o $@ -w

$(OBJ_DIR)/cliente.o: $(SRC_DIR)/cliente.c $(INCLUDE_DIR)/cliutils.h $(INCLUDE_DIR)/cliente.h | $(OBJ_DIR)
	gcc -I $(INCLUDE_DIR) -c $< -o $@ -w

$(OBJ_DIR)/consulta.o: $(SRC_DIR)/consulta.c $(INCLUDE_DIR)/cliutils.h $(INCLUDE_DIR)/consulta.h | $(OBJ_DIR)
	gcc -I $(INCLUDE_DIR) -c $< -o $@ -w
