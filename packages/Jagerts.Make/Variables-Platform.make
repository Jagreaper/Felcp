ifeq ($(OS),Windows_NT)
	OS_NAME = Windows
	OS_TARGET = WIN32
	EXT_APP = exe
	EXT_SHARED = dll
	EXT_LIB = lib
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
			PLATFORM_NAME = x64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
					PLATFORM_NAME = x64
        endif

        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
					PLATFORM_NAME = x86
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
			OS_NAME = Linux
			OS_TARGET = LINUX
			EXT_APP = out
			EXT_SHARED = so
			EXT_LIB = a
    endif

    ifeq ($(UNAME_S),Darwin)
			OS_NAME = MacOS
			OS_TARGET = OSX
			EXT_APP = out
			EXT_SHARED = so
			EXT_LIB = a
    endif

	LBITS := $(shell getconf LONG_BIT)
	ifeq ($(LBITS),64)
		PLATFORM_NAME = x64
	else
		PLATFORM_NAME = x86
	endif
endif