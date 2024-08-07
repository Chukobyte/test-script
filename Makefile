PROJECT_NAME := test_script

# OS Specific Stuff
ifeq ($(OS),Windows_NT)
    OS_TYPE := windows
    BUILD_OBJECT := $(PROJECT_NAME).exe
    L_FLAGS := -lmingw32 -static-libgcc -static-libstdc++
    DELETE_CMD := del
else
    OS_TYPE := linux
    BUILD_OBJECT := $(PROJECT_NAME)
    L_FLAGS := -lcrypt -lpthread -ldl  -lutil -lm -static-libgcc -static-libstdc++
    DELETE_CMD := rm
endif

CC := gcc # C Compiler
CXX := g++ # C++ compiler
I_FLAGS := -I"${PYTHON_INCLUDE}"
LIBRARIES := -L"${PYTHON_LIBS}"
CPP_FLAGS := -w -std=c++14 -Wfatal-errors

SRC = $(wildcard src/*.cpp src/test_script/*.cpp)

OBJ = $(SRC:.cpp=.o)

# MAIN

.PHONY: all build clean

all: clean format build

# Compiles if .o is missing or changes to the .cpp file
%.o: %.cpp
	@echo "Compiling " $< " into " $@
	@$(CXX) -c $(CPP_FLAGS) $< -o $@ $(I_FLAGS)

build: $(OBJ)
	@echo "Linking " $@
	@$(CXX) -o $(BUILD_OBJECT) $^ $(I_FLAGS) $(L_FLAGS) $(LIBRARIES)

clean:
ifneq ("$(wildcard $(BUILD_OBJECT))","")
	$(DELETE_CMD) $(BUILD_OBJECT)
endif
ifeq ($(OS_TYPE),windows)
	$(foreach object, $(OBJ), del $(subst /,\,$(object));)
else
	$(foreach object, $(OBJ), rm $(object);)
endif

run:
	@./$(BUILD_OBJECT)

format:
	@astyle -n --style=google --recursive src/*.cpp src/*.h

# Adds debug symbols for debugger
debug-build: C_FLAGS +=  -g
debug-build: build
