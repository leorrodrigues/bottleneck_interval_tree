all:
	reset
	g++ main.cpp -o interval.out -O2
debug:
	reset
	g++ main.cpp -o interval.out -g
