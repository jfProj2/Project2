all: 1730ed

1730ed: tui.o io.o main.o
        g++ -Wall -o 1730ed tui.o io.o main.o
tui.o: tui.cpp tui.h
        g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c tui.cpp
io.o: io.cpp io.h
        g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c io.cpp

main.o: main.cpp tui.h io.h
        g++ -Wall -std=c++14 -g -O0 -pedantic-errors -c main.cpp

clean:
        rm -f 1730ed
        rm -f tui.o
        rm -f io.o
        rm -f main.o
