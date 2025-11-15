# Adapted from: https://gist.github.com/mauriciopoppe/de8908f67923091982c8c8136a063ea6

COMPILER = g++
OPTIONS = -Wall -Wextra -pedantic -std=c++11 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
COMPILE = $(COMPILER) $(OPTIONS)

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj

BIN_NAME = shell
BIN = $(BIN_DIR)/$(BIN_NAME)

SRC_EXT = cpp
SRCS := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJS = $(SRCS:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

.PHONY: release
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "Creating build directories"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

.PHONY: clean
clean:
	@echo "Deleting build directories"
	@$(RM) -r $(BUILD_DIR)


all: $(BIN) run

# Rule to link object files into the target executable
$(BIN): $(OBJS)
	$(COMPILE) -o $(BIN) $(OBJS)

# Rule to compile .cpp files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	$(COMPILE) -c $< -o $@

# Rule to run the executable
run: $(BIN)
	$(BIN)
