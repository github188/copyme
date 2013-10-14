
CUR_DIR = $(shell pwd)

export AR = arm-linux-gnueabihf-ar
export CC = arm-linux-gnueabihf-gcc-4.6
export CXX = arm-linux-gnueabihf-g++-4.6
export CFLAGS = -I$(CUR_DIR)/include/
export CXXFLAGS = -I$(CUR_DIR)/include/
export ARFLAGS = -rcs
export LIBS = 

