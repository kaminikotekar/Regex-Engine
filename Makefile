execute: NFA
	bin/run/NFA

NFA: main.o NFA.o  hashmap.o
	gcc main.o NFA.o hashmap.o -o bin/run/NFA

main.o:
	gcc -c -I include src/main.c

NFA.o:
	gcc -c -I include src/NFA.c

hashmap.o:
	gcc -c -I include src/hashmap.c

clean:
	rm -f main.o NFA.o hashmap.o bin/run/NFA