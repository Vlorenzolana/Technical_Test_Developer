CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinc
LDFLAGS = -lpthread
SRC_DIR = src
OBJ_DIR = obj
BIN = addnum
CONFIG = configfile/cfg.txt

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean valgrind

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(BIN)
	valgrind -s --leak-check=full --track-origins=yes ./$(BIN) -f $(CONFIG)

clean:
	rm -rf $(OBJ_DIR) $(BIN)
