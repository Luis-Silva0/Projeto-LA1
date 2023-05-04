#======================================================================
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2 -I $(INC_DIR)
#----------------------------------------------------------------------
BLD_DIR = build
SRC_DIR = src
INC_DIR = include
#----------------------------------------------------------------------
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(SRC))
#----------------------------------------------------------------------
PROGRAM = game
#======================================================================

.DEFAULT_GOAL = build

build: setup $(PROGRAM) run clean

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) -c $(CFLAGS) -o $@ $^

.PHONY: setup
setup: 
	@mkdir -p $(BLD_DIR)

.PHONY:clean
run:
	@./game
clean:
	@-rm -r $(BLD_DIR)
	@-rm game
