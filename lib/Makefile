
CC = gcc

CPPFLAGS = $(CPP_DIRS)
CFLAGS = $(WARN_OPTS)

WARN_OPTS = -Wall -Wextra

# ----------------------------------------------------------------------------------------------------

LIB_NAME = libmy.a
LIB_DIR = .

LIB = $(LIB_DIR)/$(LIB_NAME)

# ----------------------------------------------------------------------------------------------------

# LIB_DIR = ./my # and makefile there with AR_DIR = ..

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)

SRC_DIR = .
INC_DIR = .

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

# compiling the library
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(_INC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# linking the library
$(LIB): $(OBJECTS)
	$(AR) -r -c -s $@ $^

# ----------------------------------------------------------------------------------------------------

.PHONY: build
build: dir lib

.PHONY: dir
dir:
	@mkdir -p -v $(BUILD_DIR)

.PHONY: lib
lib: $(LIB)

.PHONY: clean
clean:
	@$(RM) -v $(_OBJ)
	@$(RM) -d -v $(BUILD_DIR)
	@$(RM) -v $(LIB)
