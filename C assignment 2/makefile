
maze : terminal.o main.o LinkedList.o
	gcc terminal.o main.o LinkedList.o -o maze
	

main.o : main.c main.h 
	gcc -c main.c 
	
terminal.o: terminal.c terminal.h
	gcc -c terminal.c 
 
LinkedList.o : LinkedList.c LinkedList.h
	gcc -c LinkedList.c 
clean: 
	rm -f maze terminal.o main.o LinkedList.o
