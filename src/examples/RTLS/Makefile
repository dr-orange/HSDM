############################################################################
#  Makefile
#  by NAKAJIMA Koji, Tokyo Inst. of Tech.
#  File Name: Makefile
#  last modified => Time-stamp: "99/02/04 20:31:31 ko-ji"
############################################################################
#LAPACKPP_DIR = /usr/local
#LAPACKPP_LIB_DIR = /usr/local/lib
#include makefile.ini

CIRC = _LAB_
#CIRC = _HOME_
CPP = g++
AR = ar
OPTN = -O3 -I../../include -ffast-math -fomit-frame-pointer
OUTPUT = RTLSExample
OBJS := $(patsubst %.cc,%.o,$(wildcard *.cc)) $(patsubst ../../tool/%.cc,../../tool/%.o,$(wildcard ../../tool/*.cc)) $(patsubst ../../restrictedTotalLeastSquares/%.cc,../../restrictedTotalLeastSquares/%.o,$(wildcard ../../restrictedTotalLeastSquares/*.cc))

all : $(OBJS)
	$(CPP) $(OPTN) $(CPPFLAGS) -o $(OUTPUT) $(OBJS) $(ALL_LAPACKPP_LIB) -lm
#	/bin/mv $(OUTPUT) ..

%.o : %.cc
	$(CPP) $(OPTN) $(CPPFLAGS) -c $< -o $@

clean : 
	/bin/rm -f *.o
	/bin/rm -f $(OUTPUT)
	/bin/rm -f $(OUTPUT).exe

allclean : 
	/bin/rm -f ../../tool/*.o
	/bin/rm -f ../../restrictedTotalLeastSquares/*.o
	/bin/rm -f *.o
	/bin/rm -f $(OUTPUT)
	/bin/rm -f $(OUTPUT).exe
