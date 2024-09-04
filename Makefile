
CC = gcc

CPPFLAGS = $(CPP_DIRS)
CFLAGS = $(WARN_OPTS)

WARN_OPTS = -Wall -Wextra

LDFLAGS = $(LD_DIRS)
LDLIBS = -lmy

CPP_DIRS = -I$(INC_DIR) -I$(LIB_DIR)
LD_DIRS = -L$(LIB_DIR)

# ----------------------------------------------------------------------------------------------------

BIN_NAME = vm
BIN_DIR = .

BIN = $(BIN_DIR)/$(BIN_NAME)

# ----------------------------------------------------------------------------------------------------

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)

LIB_DIR = ./lib

SRC_DIR = ./src
INC_DIR = ./inc

# ----------------------------------------------------------------------------------------------------

_SRC = $(wildcard $(SRC_DIR)/*.c)
_INC = $(wildcard $(INC_DIR)/*.h)
_OBJ = $(wildcard $(OBJ_DIR)/*.o)

# ----------------------------------------------------------------------------------------------------

# first rule
.PHONY: all
all: build

# ----------------------------------------------------------------------------------------------------

OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(_SRC))

# compiling the program
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(_INC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# will not automatically link, if a library is updated !!!
# linking the program
$(BIN): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# ----------------------------------------------------------------------------------------------------

.PHONY: build
build: dir lib bin

.PHONY: dir
dir:
	@mkdir -p -v $(BUILD_DIR)

.PHONY: lib
lib:
	@$(MAKE) -C $(LIB_DIR) all

.PHONY: bin
bin: $(BIN)

.PHONY: run
run: build
# load from file
#	@$(BIN) hello.vm
# load from stdin
	@$(BIN) < hello.vm
#	@$(BIN)

.PHONY: clean
clean:
	@$(RM) -v $(_OBJ)
	@$(RM) -d -v $(BUILD_DIR)
	@$(RM) -v $(BIN)
	@$(MAKE) -C $(LIB_DIR) clean
