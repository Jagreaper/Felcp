_INCLUDE_PARAMS = $(foreach d, $(INCLUDE_DIRS), -I$d)
_INCLUDE_FILES = $(wildcard $(INCLUDE_DIRS)*.hpp)

_PREPROCESSOR_FLAGS = $(foreach m, $(PREPROCESSOR_MACROS), -D$m) -D$(OS_TARGET) -D$(PLATFORM_NAME)
_COMPILIER_FLAGS = $(_INCLUDE_PARAMS) $(_PREPROCESSOR_FLAGS)

_LIB_PDIRS_RELEASE = $(foreach d, $(LIB_PROJECTS), $(SOLUTION_DIR)$d/bin/Release/$(OS_NAME)/$(PLATFORM_NAME)/)
_LIB_FILES_RELEASE += $(foreach f, $(foreach d, $(_LIB_PDIRS_RELEASE), $(wildcard $d*.$(EXT_LIB))), $(if $(filter-out $(TARGET), $f), $f))
_LIB_FILES_RELEASE += $(foreach f, $(foreach d, $(_LIB_PDIRS_RELEASE), $(wildcard $d*.$(EXT_SHARED))), $(if $(filter-out $(TARGET), $f), $f))
_LIB_FLAGS_RELEASE = $(foreach F, $(_LIB_FILES_RELEASE), $F) 

_LIB_PDIRS_DEBUG = $(foreach d, $(LIB_PROJECTS), $(SOLUTION_DIR)$d/bin/Debug/$(OS_NAME)/$(PLATFORM_NAME)/)
_LIB_FILES_DEBUG += $(foreach f, $(foreach d, $(_LIB_PDIRS_DEBUG), $(wildcard $d*.$(EXT_LIB))), $(if $(filter-out $(TARGET), $f), $f))
_LIB_FILES_DEBUG += $(foreach f, $(foreach d, $(_LIB_PDIRS_DEBUG), $(wildcard $d*.$(EXT_SHARED))), $(if $(filter-out $(TARGET), $f), $f))
_LIB_FLAGS_DEBUG = $(foreach F, $(_LIB_FILES_DEBUG), $F) 

_LIB_FILES += $(foreach f, $(foreach d, $(LIB_DIRS), $(wildcard $d*.$(EXT_LIB))), $(if $(filter-out $(TARGET), $f), $f))
_LIB_FILES += $(foreach f, $(foreach d, $(LIB_DIRS), $(wildcard $d*.$(EXT_SHARED))), $(if $(filter-out $(TARGET), $f), $f))
LIB_FLAGS += $(foreach F, $(LIB_FILES), $F) 

SRC_FILES += $(wildcard $(PROJECT_DIR)*.cpp)
_OBJ_FILES_DEBUG = $(patsubst $(PROJECT_DIR)%.cpp,$(INT_DIR_DEBUG)%.o,$(SRC_FILES))
_OBJ_FILES_RELEASE = $(patsubst $(PROJECT_DIR)%.cpp,$(INT_DIR_RELEASE)%.o,$(SRC_FILES))