.distr-clean:
	@rm -rf $(SOLUTION_DIR)dist/$(PROJECT_NAME)/

.distr-mk:
	@mkdir -p $(SOLUTION_DIR)dist/$(PROJECT_NAME)/
	@mkdir -p $(SOLUTION_DIR)dist/$(PROJECT_NAME)/$(BIN_DIR_DEBUG)
	@mkdir -p $(SOLUTION_DIR)dist/$(PROJECT_NAME)/$(BIN_DIR_RELEASE)

.distr-copy-headers:
	@$(foreach h, $(wildcard $(PROJECT_DIR)*.hpp), cp $h $(SOLUTION_DIR)dist/$(PROJECT_NAME)/;)

.distr-copy-bins:
	@$(foreach f, $(wildcard $(PROJECT_DIR)/$(BIN_DIR_DEBUG)$(PROJECT_NAME)*.*), cp $f $(SOLUTION_DIR)dist/$(PROJECT_NAME)/$(BIN_DIR_DEBUG);)
	@$(foreach f, $(wildcard $(PROJECT_DIR)/$(BIN_DIR_RELEASE)$(PROJECT_NAME)*.*), cp $f $(SOLUTION_DIR)dist/$(PROJECT_NAME)/$(BIN_DIR_RELEASE);)

.distr-copy: .distr-mk .distr-copy-headers .distr-copy-bins