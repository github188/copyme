
# plateform, use one of them #
# include "arm.mk"
include x86.mk
# plateform end #

default: 
	@echo use make [target] to build target.
	@echo [target] can be one of bellow.
	@echo [pnnet], network libs.

pnnet:
	@$(MAKE) -C net

pnnet_clean:
	cd net && make clean

clean: pnnet_clean
