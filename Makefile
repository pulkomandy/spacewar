#
# Makefile
# pulkomandy, 2018-11-10 16:37
#

CXXFLAGS=-O3

Spacewar: engine.o main.o Planetarium.o Collidible.o
	g++-x86 $(CXXFLAGS) -o $@ $^ -lbe -ldevice

%.o: %.cpp
	g++-x86 $(CXXFLAGS) -c -Wall -o $@ $^

engine.o: Spacewar_3_1.cpp
	g++-x86 $(CXXFLAGS) -c -Wall -o $@ $^

main.o: main.cpp
	g++-x86 $(CXXFLAGS) -c -Wall -o $@ $^


# vim:ft=make
#
