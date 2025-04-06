CC := gcc
CFLAGS := -Wall -Wextra -Werror -Iinc
LDFLAGS := -lpthread

BIN := addnum
SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := test
CFG ?= configfile/cfg.txt

MAIN_SRC := $(SRC_DIR)/main.c
ALL_SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS := $(filter-out $(MAIN_SRC), $(ALL_SRCS))
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ALL_SRCS))

UNIT_SRC := $(TEST_DIR)/test_addnum.c
UNIT_EXE := test_addnum

GREEN := \033[1;32m
RESET := \033[0m

.PHONY: all clean run valgrind help re test test_clean

all: $(BIN)

$(BIN): $(OBJS)
	@echo "$(GREEN) Linking $(RESET)"
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN) Compiling $(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	@echo "$(GREEN) Running with config file: $(CFG)$(RESET)"
	./$(BIN) -f $(CFG)

valgrind: $(BIN)
	@echo "$(GREEN) Valgrind with config: $(CFG)$(RESET)"
	valgrind -s --leak-check=full --track-origins=yes ./$(BIN) -f $(CFG)

test: $(UNIT_SRC)
	@echo "$(GREEN) Building unit tests $(RESET)"
	$(CC) $(CFLAGS) $(UNIT_SRC) $(SRCS) -o $(UNIT_EXE) $(LDFLAGS)
	@echo "$(GREEN) 🧪 Running unit tests...$(RESET)"
	./$(UNIT_EXE)

test_clean:
	@rm -f $(UNIT_EXE)

clean:
	@echo "$(GREEN) Cleaning $(RESET)"
	@rm -rf $(OBJ_DIR) $(BIN) $(UNIT_EXE)

re: clean all

help:
	@echo "$(GREEN)Available targets:$(RESET)"
	@echo "  $(GREEN)make          $(RESET)- Build the program"
	@echo "  $(GREEN)make run      $(RESET)- Run the program with configfile (default: $(CFG))"
	@echo "  $(GREEN)make valgrind $(RESET)- Run the program under Valgrind"
	@echo "  $(GREEN)make clean    $(RESET)- Clean object files and binary"
	@echo "  $(GREEN)make re       $(RESET)- Rebuild from scratch"
	@echo "  $(GREEN)make test     $(RESET)- Compile and run unit tests"
	@echo "  $(GREEN)make help     $(RESET)- Show this help message"
