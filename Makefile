all: monkeys

monkeys: monkeys.o
	g++ -lncurses -lmenu -o  monkeys monkeys.o

monkeys.o: monkeys.cpp
	g++ -c monkeys.cpp

clean:
	rm -f monkeys
	rm -f monkeys.o
