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

DIST_PROJECTS = Jagerts.Felcp.Helpers Jagerts.Felcp.Imaging Jagerts.Felcp.Xml Jagerts.Felcp.IO Jagerts.Felcp.IO.Imaging Jagerts.Felcp.IO.Xml
BUILD_PROJECTS = Jagerts.Felcp.Helpers Jagerts.Felcp.Imaging Jagerts.Felcp.Xml Jagerts.Felcp.IO Jagerts.Felcp.IO.Imaging Jagerts.Felcp.IO.Xml Jagerts.Felcp.Test

BUILD_CMD = echo ""; $(foreach p, $(BUILD_PROJECTS), make build CONFIGURATION='$(CONFIGURATION)' -f $p/Makefile; echo "";)
REBUILD_CMD = echo ""; $(foreach p, $(BUILD_PROJECTS), make rebuild CONFIGURATION='$(CONFIGURATION)' -f $p/Makefile; echo "";)
CLEAN_CMD = echo ""; $(foreach p, $(BUILD_PROJECTS), make clean CONFIGURATION='$(CONFIGURATION)' -f $p/Makefile; echo "";)

BUILD_DEBUG_CMD = echo ""; $(foreach p, $(BUILD_PROJECTS), make build CONFIGURATION='Debug' -f $p/Makefile; echo "";)
REBUILD_DEBUG_CMD = echo ""; $(foreach p, $(BUILD_PROJECTS), make rebuild CONFIGURATION='Debug' -f $p/Makefile; echo "";)
CLEAN_DEBUG_CMD = echo ""; $(foreach p, $(BUILD_PROJECTS), make clean CONFIGURATION='Debug' -f $p/Makefile; echo "";)

BUILD_RELEASE_CMD = echo ""; $(foreach p, $(BUILD_PROJECTS), make build CONFIGURATION='Release' -f $p/Makefile; echo "";)
REBUILD_RELEASE_CMD = echo ""; $(foreach p, $(BUILD_PROJECTS), make rebuild CONFIGURATION='Release' -f $p/Makefile; echo "";)
CLEAN_RELEASE_CMD = echo ""; $(foreach p, $(BUILD_PROJECTS), make clean CONFIGURATION='Release' -f $p/Makefile; echo "";)

DIST_BINS = bin/Debug/$(OS_NAME)/$(PLATFORM_NAME)/ bin/Release/$(OS_NAME)/$(PLATFORM_NAME)/
DIST_CLEAN_CMD = rm -rf $(SOLUTION_DIR)dist/;
DIST_MK_CMD = $(foreach p, $(DIST_PROJECTS), $(foreach d, $(DIST_BINS), mkdir -p $(SOLUTION_DIR)dist/$p/$d;)) mkdir -p $(SOLUTION_DIR)dist/Jagerts.Felcp.Shared/;
DIST_COPY_HEADERS_CMD = $(foreach p, $(DIST_PROJECTS), $(foreach h, $(wildcard $(SOLUTION_DIR)$p/*.hpp), cp $h $(SOLUTION_DIR)dist/$p/;)) $(foreach h, $(wildcard $(SOLUTION_DIR)Jagerts.Felcp.Shared/*.hpp), cp $h $(SOLUTION_DIR)dist/Jagerts.Felcp.Shared/;)
DIST_COPY_BINS_CMD = $(foreach p, $(DIST_PROJECTS), $(foreach d, $(DIST_BINS), $(foreach f, $(wildcard $(SOLUTION_DIR)$p/$d$p*.*), cp $f $(SOLUTION_DIR)dist/$p/$d;)))	
DIST_CMD = $(DIST_CLEAN_CMD) $(DIST_MK_CMD) $(DIST_COPY_HEADERS_CMD) $(DIST_COPY_BINS_CMD)

all: build

build:
	@$(BUILD_CMD)

rebuild:
	@$(REBUILD_CMD)

clean:
	@$(CLEAN_CMD)

build-debug:
	@$(BUILD_DEBUG_CMD)

rebuild-debug:
	@$(REBUILD_DEBUG_CMD)

clean-debug:
	@$(CLEAN_DEBUG_CMD)

build-release:
	@$(BUILD_RELEASE_CMD)

rebuild-release:
	@$(REBUILD_RELEASE_CMD)

clean-release:
	@$(CLEAN_RELEASE_CMD)

build-all: build-debug build-release

rebuild-all: rebuild-debug rebuild-release

clean-all: clean-debug clean-release

dist: rebuild-all
	@$(DIST_CMD)

dist-clean:
	@$(DIST_CLEAN_CMD)

.PHONY: clean