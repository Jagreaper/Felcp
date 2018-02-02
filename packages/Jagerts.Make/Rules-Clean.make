.clean-debug:
	@echo "Cleaning $(PROJECT_NAME)"
	@echo "  Operating System $(OS_NAME)"
	@echo "  Configuration = Debug"
	@echo "  Platform = $(PLATFORM_NAME)"

	@rm -rf $(PROJECT_DIR)$(OBJ_DIR_DEBUG)
	@rm -rf $(PROJECT_DIR)$(BIN_DIR_DEBUG)

.clean-release:
	@echo "Cleaning $(PROJECT_NAME)"
	@echo "  Operating System $(OS_NAME)"
	@echo "  Configuration = Release"
	@echo "  Platform = $(PLATFORM_NAME)"

	@rm -rf $(PROJECT_DIR)$(OBJ_DIR_RELEASE)
	@rm -rf $(PROJECT_DIR)$(BIN_DIR_RELEASE)
