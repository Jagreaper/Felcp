BUILD_DEBUG_CMD = $(foreach p, $(BUILD_PROJECTS), make build-debug PROJECT_DIR='$(CURDIR)/$p/' _MAKE_INCLUDE_PATH='$(_MAKE_INCLUDE_PATH)' -f $p/Makefile; echo "";)
REBUILD_DEBUG_CMD = $(foreach p, $(BUILD_PROJECTS), make rebuild-debug PROJECT_DIR='$(CURDIR)/$p/' _MAKE_INCLUDE_PATH='$(_MAKE_INCLUDE_PATH)' -f $p/Makefile; echo "";)
CLEAN_DEBUG_CMD = $(foreach p, $(BUILD_PROJECTS), make clean-debug PROJECT_DIR='$(CURDIR)/$p/' _MAKE_INCLUDE_PATH='$(_MAKE_INCLUDE_PATH)' -f $p/Makefile; echo "";)

BUILD_RELEASE_CMD = $(foreach p, $(BUILD_PROJECTS), make build-release PROJECT_DIR='$(CURDIR)/$p/' _MAKE_INCLUDE_PATH='$(_MAKE_INCLUDE_PATH)' -f $p/Makefile; echo "";)
REBUILD_RELEASE_CMD = $(foreach p, $(BUILD_PROJECTS), make rebuild-release PROJECT_DIR='$(CURDIR)/$p/' _MAKE_INCLUDE_PATH='$(_MAKE_INCLUDE_PATH)' -f $p/Makefile; echo "";)
CLEAN_RELEASE_CMD = $(foreach p, $(BUILD_PROJECTS), make clean-release PROJECT_DIR='$(CURDIR)/$p/' _MAKE_INCLUDE_PATH='$(_MAKE_INCLUDE_PATH)' -f $p/Makefile; echo "";)

DIST_CMD = $(foreach p, $(DIST_PROJECTS), make distr PROJECT_DIR='$(CURDIR)/$p/' _MAKE_INCLUDE_PATH='$(_MAKE_INCLUDE_PATH)' -f $p/Makefile;)

distr:
	@$(DIST_CMD)

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

build: build-debug build-release

rebuild: rebuild-debug rebuild-release

clean: clean-debug clean-release