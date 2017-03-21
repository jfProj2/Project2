all: 1730ed

1730ed: tui.o io.o main.o
	g++ -Wall -lmenu -lncurses -o 1730ed tui.o io.o main.o
tui.o: tui.cpp tui.h
        g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c -lmenu -lncurses  tui.cpp
io.o: io.cpp io.h
        g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c -lmenu -lncurses io.cpp

main.o: main.cpp tui.h io.h
        g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c -lmenu -lncurses main.cpp

clean:
	rm -f 1730ed
	rm -f tui.o
	rm -f io.o
	rm -f main.o


#all: bananas

#bananas: bananas.o
	#g++ -lncurses -lmenu -o  bananas bananas.o

#bananas.o: bananas.cpp
	#g++ -c bananas.cpp

#clean:
	#rm -f bananas
	#rm -f bananas.o