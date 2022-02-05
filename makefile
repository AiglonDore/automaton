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

zip :
	tar zcvf thomas_roiseux.tgz "Manuel.pdf" "Rapport.pdf" automaton.c automaton.h chararray.c chararray.h dot.c dot.h loop.c loop.h main.c makefile stack.c stack.h bool.h

list :
	tar tvf thomas_roiseux.tgz

extract :
	tar xvf thomas_roiseux.tgz

release_linux :
	gcc -O2 -s -o "Released/automaton.out" main.c automaton.c chararray.c dot.c loop.c stack.c

release_windows :
	x86_64-w64-mingw32-gcc -O2 -s -static -m64 main.c automaton.c chararray.c dot.c loop.c stack.c -o "Released/automaton.exe"