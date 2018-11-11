#
# Makefile
# pulkomandy, 2018-11-10 16:37
#

Spacewar: engine.o main.o
	g++-x86 -o $@ $^ -lbe

engine.o: Spacewar_3_1.cpp
	g++-x86 -c -Wall -o $@ $^

main.o: main.cpp
	g++-x86 -c -Wall -o $@ $^


# vim:ft=make
#
