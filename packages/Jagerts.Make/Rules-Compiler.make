.mk-int-debug:
	@mkdir -p $(INT_DIR_DEBUG)

.mk-int-release:
	@mkdir -p $(INT_DIR_RELEASE)

.mk-out-debug:
	@mkdir -p $(OUT_DIR_DEBUG)

.mk-out-release:
	@mkdir -p $(OUT_DIR_RELEASE)

.compile-objs-debug:
	@$(foreach d, $(_OBJ_FILES_DEBUG), $(COMPILIER) -std=$(CPP_LANGUAGE) -c -o $d $(PROJECT_DIR)$(basename $(notdir $d)).cpp $(_COMPILIER_FLAGS);)

.compile-objs-release:
	@$(foreach d, $(_OBJ_FILES_RELEASE), $(COMPILIER) -std=$(CPP_LANGUAGE) -c -o $d $(PROJECT_DIR)$(basename $(notdir $d)).cpp $(_COMPILIER_FLAGS);)

.compile-debug: .mk-int-debug .mk-out-debug .compile-objs-debug
	@echo "Compiling $(PROJECT_NAME)"
	@echo "  Operating System $(OS_NAME)"
	@echo "  Configuration = Debug"
	@echo "  Platform = $(PLATFORM_NAME)"

	@$(COMPILIER) -o $(_TARGET_DEBUG) $(_OBJ_FILES_DEBUG) $(_COMPILIER_FLAGS) $(LIB_FLAGS) $(_LIB_FLAGS_DEBUG) -DDEBUG=1

.compile-release: .mk-int-release .mk-out-release .compile-objs-release
	@echo "Compiling $(PROJECT_NAME)"
	@echo "  Operating System $(OS_NAME)"
	@echo "  Configuration = Release"
	@echo "  Platform = $(PLATFORM_NAME)"

	@$(COMPILIER) -o $(_TARGET_RELEASE) $(_OBJ_FILES_RELEASE) $(_COMPILIER_FLAGS) $(LIB_FLAGS) $(_LIB_FLAGS_RELEASE) -DRELEASE=1