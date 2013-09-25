
OBJS = pnsocktool.o sockwrap.o error.o pnsocket.o

default : $(OBJS)
	$(AR) $(ARFLAGS) libpnnet.a $(OBJS)
	@echo make network tools done.

pnsocktool.o : pnsocktool.c pnsocktool.h
	$(CC) $(CFLAGS) -c $< -o $@

sockwrap.o : sockwrap.c sockwrap.h error.h netcommon.h
	$(CC) $(CFLAGS) -c $< -o $@

error.o : error.c error.h
	$(CC) $(CFLAGS) -c $< -o $@

pnsocket.o : pnsocket.c pnsocket.h
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS)
