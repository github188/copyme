
# plateform, use one of them #
# include "arm.mk"
# include x86.mk
# plateform end #

pnnet:
	$(MAKE) -C net

clean:
	$(MAKE) -C net
