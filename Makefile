# === Configuration ===
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iinc
LDFLAGS := -lpthread
BIN := addnum
SRC_DIR := src
OBJ_DIR := obj
CFG ?= configfile/cfg.txt

# === Colors ===
GREEN := \033[1;32m
RESET := \033[0m

# === Sources & Objects ===
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# === Targets ===
.PHONY: all clean run valgrind help re

all: $(BIN)

$(BIN): $(OBJS)
	@echo "$(GREEN) Linking $@...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN) Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	@echo "$(GREEN) Running with config file: $(CFG)$(RESET)"
	./$(BIN) -f $(CFG)

valgrind: $(BIN)
	@echo "$(GREEN) Valgrind with config: $(CFG)$(RESET)"
	valgrind -s --leak-check=full --track-origins=yes ./$(BIN) -f $(CFG)

clean:
	@echo "$(GREEN) Cleaning $(RESET)"
	@rm -rf $(OBJ_DIR) $(BIN)

re: clean all

help:
	@echo "$(GREEN)  Available targets:$(RESET)"
	@echo "$(GREEN)  make          $(RESET)- Build the program"
	@echo "$(GREEN)  make run      $(RESET)- Run the program with configfile (default: $(CFG))"
	@echo "$(GREEN)  make valgrind $(RESET)- Run the program under Valgrind"
	@echo "$(GREEN)  make clean    $(RESET)- Clean object files and binary"
	@echo "$(GREEN)  make re       $(RESET)- Rebuild from scratch"
	@echo "$(GREEN)  make help     $(RESET)- Show this help message"
