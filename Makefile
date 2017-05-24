GCC=g++
FLAGS=-fsanitize=leak -fsanitize=undefined -fsanitize=address -Wall
#FLAGS=-ggdb -g

#FLAGS=-g -ggdb

chaos:standard_map.cpp
	$(GCC) $(FLAGS) standard_map.cpp
chaos_gsl:standard_mapV2.cpp
	$(GCC) $(FLAGS2) standard_mapV2.cpp
clean:
	rm -f *.dat *.txt *.out *~
