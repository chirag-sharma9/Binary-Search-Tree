
TreeDr: TreeDr.o TreeType.o
	g++ -o driver TreeDr.o TreeType.o

TreeDr.o: TreeDr.cpp
	g++ -c TreeDr.cpp

TreeType.o: TreeType.cpp TreeType.h
	g++ -c TreeType.cpp

run: TreeDr
	./driver

clean:
	rm -f *.o
	rm -f *~
	rm -f driver
	rm output.txt
