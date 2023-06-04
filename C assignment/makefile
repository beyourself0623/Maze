
MAIN = main.c
FILE = main.o

ifdef DARK

override MAIN = maindark.c
override FILE = maindark.o
DARK: clean maze $(FILE) map.o terminal.o


endif

maze : map.o terminal.o $(FILE)
	gcc map.o terminal.o $(FILE) -o maze
	

$(FILE) : $(MAIN) main.h 
	gcc -c $(MAIN) 
		
map.o: map.c map.h
	gcc -c map.c 
	
terminal.o: terminal.c terminal.h
	gcc -c terminal.c 
 
clean: 
	rm -f maze map.o terminal.o main.o maindark.o
