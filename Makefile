CXXFLAGS += -Wall -Wextra -std=c++14 -MMD

main: main.o
	g++ $^ -o $@

-include main.d
