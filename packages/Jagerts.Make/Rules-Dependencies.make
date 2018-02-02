.clean_dependencies_debug:
	@$(foreach p, $(LIB_PROJECTS), $(foreach f, $(wildcard $(OUT_DIR_DEBUG)p.*), rm -f $f;))

.clean_dependencies_release:
	@$(foreach p, $(LIB_PROJECTS), $(foreach f, $(wildcard $(OUT_DIR_RELEASE)p.*), rm -f $f;))

.copy_dependencies_debug:
	@mkdir -p $(OUT_DIR_DEBUG)
	@$(foreach p, $(LIB_PROJECTS), $(foreach f, $(wildcard $(SOLUTION_DIR)$p/$(BIN_DIR_DEBUG)$p*.*), cp $f $(OUT_DIR_DEBUG);))

.copy_dependencies_release:
	@mkdir -p $(OUT_DIR_RELEASE)
	@$(foreach p, $(LIB_PROJECTS), $(foreach f, $(wildcard $(SOLUTION_DIR)$p/$(BIN_DIR_RELEASE)$p*.*), cp $f $(OUT_DIR_RELEASE);))