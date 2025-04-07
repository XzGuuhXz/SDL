all:clear compile

compile:
	g++ -o window -g -Wall window.cpp `sdl2-config --cflags --libs`

clear:
	clear

debug:
	ddd window