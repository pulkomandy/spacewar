#
# Makefile
# pulkomandy, 2018-11-10 16:37
#

CXXFLAGS=-O3
ARCH=$(shell uname -p)

ifeq ($(ARCH),x86)
  CXX=g++-x86
endif

Spacewar: engine.o main.o Planetarium.o Collidible.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lbe -ldevice

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -Wall -o $@ $^

engine.o: Spacewar_3_1.cpp
	$(CXX) $(CXXFLAGS) -c -Wall -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -Wall -o $@ $^


# vim:ft=make
#
