CONFIGURATION = Debug

all: build

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

rebuild:
	@echo ""
	@make rebuild CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Helpers/Makefile
	@echo ""
	@make rebuild CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Imaging/Makefile
	@echo ""
	@make rebuild CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Xml/Makefile
	@echo ""
	@make rebuild CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.IO/Makefile
	@echo ""
	@make rebuild CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.IO.Imaging/Makefile
	@echo ""
	@make rebuild CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.IO.Xml/Makefile
	@echo ""
	@make rebuild CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Test/Makefile
	@echo ""

.PHONY: clean

clean:
	@echo ""
	@make clean CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Helpers/Makefile
	@echo ""
	@make clean CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Imaging/Makefile
	@echo ""
	@make clean CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Xml/Makefile
	@echo ""
	@make clean CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.IO/Makefile
	@echo ""
	@make clean CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.IO.Imaging/Makefile
	@echo ""
	@make clean CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.IO.Xml/Makefile
	@echo ""
	@make clean CONFIGURATION='$(CONFIGURATION)' -f Jagerts.Felcp.Test/Makefile
	@echo ""