execute: NFA
	bin/run/NFA

NFA: main.o NFA.o 
	gcc main.o NFA.o -o bin/run/NFA

main.o:
	gcc -c -I include src/main.c

NFA.o:
	gcc -c -I include src/NFA.c

clean:
	rm -f main.o NFA.o bin/run/NFA