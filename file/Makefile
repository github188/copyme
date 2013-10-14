
OBJS = ConfFile.o dirReader.o

default : $(OBJS)
	$(AR) $(ARFLAGS) libpnfile.a $(OBJS)
	@echo make file tools done.

ConfFile.o : ConfFile.cpp ConfFile.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

dirReader.o : dirReader.cpp dirReader.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJS)
