flags = -std=c++14 -Wall -Iinclude
way = sources/sort/
include = include/sort.hpp

sort_fun: main.o libsort.a
	g++ -o sort_fun main.o -L. -lsort ${flags}

main.o: sources/main.cpp 
	g++ -c sources/main.cpp ${flags}

libsort.a: feeling_in.o output_arr.o buble_sort.o merge_sort.o quick_sort.o swap_sort.o insert_sort.o
	ar cr libsort.a feeling_in.o output_arr.o buble_sort.o merge_sort.o quick_sort.o swap_sort.o insert_sort.o

feeling_in.o: ${way}feeling_in.cpp ${include}
	g++ -c ${way}feeling_in.cpp ${flags}

output_arr.o: ${way}output_arr.cpp ${include}
	g++ -c ${way}output_arr.cpp ${flags}

buble_sort.o: ${way}buble_sort.cpp ${include}
	g++ -c ${way}buble_sort.cpp ${flags}

merge_sort.o: ${way}merge_sort.cpp ${include}
	g++ -c ${way}merge_sort.cpp ${flags}

quick_sort.o: ${way}quick_sort.cpp ${include}
	g++ -c ${way}quick_sort.cpp ${flags}

swap_sort.o: ${way}swap_sort.cpp ${include}
	g++ -c ${way}swap_sort.cpp ${flags}

insert_sort.o: ${way}insert_sort.cpp ${include}
	g++ -c ${way}insert_sort.cpp ${flags}

clean:
	rm -f *.o *.a sort_fun
