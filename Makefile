all:
	g++ main.cpp -o interval.out -std=c++17 -Wall -D_GLIBCXX_ASSERTIONS -D_FORTIFY_SOURCE=2 -fasynchronous-unwind-tables -fstack-protector-strong  -pipe -Werror=format-security  -Wduplicated-branches  -Wlogical-op  -Wnull-dereference  -Wdouble-promotion  -Wshadow  -Wformat=2 -Wduplicated-cond -fconcepts -O2
debug:
	g++ main.cpp -o interval.out -g
