stack: main.o MemManager.o MemNode.o Stack.o
	g++ -o stack main.o MemManager.o MemNode.o Stack.o

main.o: main.cpp
	g++ -c -g -o $@ $<

%.o: %.cpp %.h
	g++ -c -g -o $@ $<

clean:
	rm -f *.o
	rm -f stack


