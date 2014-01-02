
CUR_DIR = $(shell pwd)

#export AR = /home/kise/workspace/arm_env/arm-2007q3/bin/arm-none-linux-gnueabi-ar
#export CC = /home/kise/workspace/arm_env/arm-2007q3/bin/arm-none-linux-gnueabi-gcc
#export CXX = /home/kise/workspace/arm_env/arm-2007q3/bin/arm-none-linux-gnueabi-g++
export AR = arm-linux-gnueabihf-ar
export CC = arm-linux-gnueabihf-gcc
export CXX = arm-linux-gnueabihf-g++-4.6
export CFLAGS = -I$(CUR_DIR)/include/
export CXXFLAGS = -I$(CUR_DIR)/include/
export ARFLAGS = -rcs
export LIBS = 

