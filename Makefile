all: bananas

bananas: bananas.o
	g++ -lncurses -lmenu -o  bananas bananas.o

bananas.o: bananas.cpp
	g++ -c bananas.cpp

clean:
	rm -f bananas
	rm -f bananas.o
