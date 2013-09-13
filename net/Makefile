
OBJS = pnsocktool.o sockwrap.o

default : $(OBJS)
		@echo make network tools done.

pnsocktool.o : pnsocktool.c pnsocktool.h
	$(CC) -c $< -o $@

sockwrap.o : sockwrap.c sockwrap.h error.h netcommon.h
	$(CC) -c $< -o $@

clean : $(OBJS)
	rm -rf $(OBJS)
