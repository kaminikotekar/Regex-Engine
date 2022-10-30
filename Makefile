execute: NFA
	bin/run/NFA

NFA: main.o NFA.o hashmap.o parse.o
	gcc main.o parse.o NFA.o hashmap.o -o bin/run/NFA

main.o:
	gcc -c -I include src/main.c

NFA.o:
	gcc -c -I include src/NFA.c

hashmap.o:
	gcc -c -I include src/hashmap.c

parse.o:
	gcc -c -I include src/parse.c

clean:
	rm -f main.o NFA.o hashmap.o parse.o bin/run/NFA