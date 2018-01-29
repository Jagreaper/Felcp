ifeq ($(OS),Windows_NT)
	OS_NAME = Windows
	OS_TARGET = WIN32
	EXT_RUNTIME = exe
	EXT_DLL = dll
	EXT_LIB = lib
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        PLATFORM_TARGET = AMD64
		PLATFORM_NAME = x64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        	PLATFORM_TARGET = AMD64
			PLATFORM_NAME = x64
        endif

        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        	PLATFORM_TARGET = IA32
			PLATFORM_NAME = x86
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
		OS_NAME = Linux
		OS_TARGET = LINUX
    endif

    ifeq ($(UNAME_S),Darwin)
		OS_NAME = MacOS
		OS_TARGET = OSX
		EXT_RUNTIME = out
		EXT_DLL = so
		EXT_LIB = a
    endif

	LBITS := $(shell getconf LONG_BIT)
	ifeq ($(LBITS),64)
		PLATFORM_TARGET = AMD64
		PLATFORM_NAME = x64
	else
		PLATFORM_TARGET = IA32
		PLATFORM_NAME = x86
	endif
endif

CONFIGURATION = Debug
PROJECT_DIR = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SOLUTION_DIR = $(PROJECT_DIR)../
BIN_DIR = bin/$(CONFIGURATION)/$(OS_NAME)/$(PLATFORM_NAME)/
OBJ_DIR = obj/$(CONFIGURATION)/$(OS_NAME)/$(PLATFORM_NAME)/
OUT_DIR = $(PROJECT_DIR)$(BIN_DIR)
INT_DIR = $(PROJECT_DIR)$(OBJ_DIR)

TARGET_NAME = $(shell basename $(PROJECT_DIR))
TARGET_EXT = $(EXT_RUNTIME)
TARGET_FILE = $(TARGET_NAME).$(TARGET_EXT)
TARGET = $(OUT_DIR)$(TARGET_FILE)

INCLUDE_DIRS = $(SOLUTION_DIR) $(PROJECT_DIR) $(SOLUTION_DIR)packages/
INCLUDE_PARAMS = $(foreach d, $(INCLUDE_DIRS), -I$d)
INCLUDE_FILES = $(wildcard $(INCLUDE_DIRS)*.hpp)

SRC_FILES = $(wildcard $(PROJECT_DIR)*.cpp)
OBJ_FILES = $(patsubst $(PROJECT_DIR)%.cpp,$(INT_DIR)%.o,$(SRC_FILES))

LIB_DIRS = $(OUT_DIR)
LIB_FILES = $(foreach f, $(foreach d, $(LIB_DIRS), $(wildcard $d*.$(EXT_DLL))), $(if $(filter-out $(TARGET), $f), $f))

LIB_FLAGS = $(foreach F, $(LIB_FILES), $F) 

PREPROCESSOR_MACROS :=
C_PREPROCESSOR_MACROS = $(foreach m, $(PREPROCESSOR_MACROS), -D$m)

COMPILIER = g++
COMPILIER_FLAGS = $(INCLUDE_PARAMS) $(C_PREPROCESSOR_MACROS) -D$(OS_TARGET) -D$(PLATFORM_TARGET) -D$(shell echo $(CONFIGURATION) | tr a-z A-Z)=1

CPP_LANGUAGE = c++1z

COPY_DIRS = 
COPY_CMD = $(foreach d, $(COPY_DIRS), cp $(TARGET) $d;)
COPY_MKDIR_CMD = $(foreach d, $(COPY_DIRS), mkdir -p $d;)
COPY_CLEAN_CMD = $(foreach d, $(COPY_DIRS), rm -f $d$(TARGET_FILE);)

all: build

start:
	@echo building project $(TARGET_NAME)
	@echo ""

build: start $(TARGET)
	@echo "success compiling binaries"	

rebuild: start rclean $(TARGET)
	@echo "success compiling binaries"	

sources:
	@echo "compiling sources"	

$(INT_DIR):
	@mkdir -p $(INT_DIR)

$(INT_DIR)%.o: $(PROJECT_DIR)%.cpp  $(INCLUDE_FILES) sources | $(INT_DIR)
	@$(COMPILIER) -std=$(CPP_LANGUAGE) -c -o $@ $< $(COMPILIER_FLAGS)

compile: $(OBJ_FILES)
	@echo "compiling binaries"
	@mkdir -p $(OUT_DIR)
	@$(COMPILIER) -o $(TARGET) $^ $(COMPILIER_FLAGS) $(LIB_FLAGS)
	@$(COPY_MKDIR_CMD)
	@$(COPY_CMD)

$(TARGET): compile

.PHONY: clean

rclean:
	@echo "cleaning object files"	
	@rm -f $(OBJ_FILES)	
	@echo "cleaning binary files"	
	@rm -f $(TARGET)
	@$(COPY_CLEAN_CMD)

clean:
	@echo cleaning project $(TARGET_NAME)
	@echo ""
	@echo "cleaning object files"	
	@rm -f $(OBJ_FILES)	
	@echo "cleaning binary files"	
	@rm -f $(TARGET)
	@$(COPY_CLEAN_CMD)
