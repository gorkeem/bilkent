heapsort: heap.o heapsort.o
	g++ heap.o heapsort.o -o heapsort

heap.o: heap.cpp
	g++ -c heap.cpp

heapsort.o: heapsort.cpp
	g++ -c heapsort.cpp

clean: clean-custom
	rm* output