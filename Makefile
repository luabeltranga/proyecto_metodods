GCC=g++
FLAGS=-fsanitize=leak -fsanitize=undefined -fsanitize=address -Wall
#FLAGS=-g -ggdb

chaos:standard_map.cpp
	$(GCC) $(FLAGS) standard_map.cpp

clean:
	rm -f *.dat *.txt *.out *~
