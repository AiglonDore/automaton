all : automaton.out

release : release_linux release_windows

automaton.out : main.o automaton.o chararray.o dot.o loop.o stack.o
	gcc -o $@ -Wall $^

main.o : main.c loop.h dot.h automaton.h bool.h
	gcc -c -Wall main.c

automaton.o : automaton.c automaton.h chararray.h stack.h bool.h
	gcc -c -Wall automaton.c

chararray.o : chararray.c chararray.h bool.h
	gcc -c -Wall chararray.c

dot.o : dot.c dot.h chararray.h automaton.h bool.h
	gcc -c -Wall dot.c

loop.o : loop.c chararray.h automaton.h bool.h
	gcc -c -Wall loop.c

stack.o : stack.c stack.h bool.h
	gcc -c -Wall stack.c

clean :
	rm -f *.o
