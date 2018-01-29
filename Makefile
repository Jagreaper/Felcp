
build:
	@echo ""
	@make build CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Helpers/Makefile
	@echo ""
	@make build CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Imaging/Makefile
	@echo ""
	@make build CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Xml/Makefile
	@echo ""
	@make build CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.IO/Makefile
	@echo ""
	@make build CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.IO.Imaging/Makefile
	@echo ""
	@make build CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.IO.Xml/Makefile
	@echo ""
	@make build CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Test/Makefile
	@echo ""

CONFIGURATION = Debug

DIST_PROJECTS = Jagerts.Felcp.Helpers Jagerts.Felcp.Imaging Jagerts.Felcp.Xml Jagerts.Felcp.IO Jagerts.Felcp.IO.Imaging Jagerts.Felcp.IO.Xml
DIST_CMD = rm -rf $(SOLUTION_DIR)dist/; $(foreach d, $(DIST_PROJECTS), mkdir -p $(SOLUTION_DIR)dist/$d/; cp -a $(SOLUTION_DIR)$d/. $(SOLUTION_DIR)dist/$d/; rm -f $(SOLUTION_DIR)dist/$d/Makefile; rm -rf $(SOLUTION_DIR)dist/$d/obj/; )

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

.PHONY: clean