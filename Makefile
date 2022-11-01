execute: NFA
	bin/run/NFA

NFA: main.o NFA.o hashmap.o parse.o postfix.o
	gcc main.o parse.o NFA.o hashmap.o postfix.o -o bin/run/NFA

main.o:
	gcc -c -I include src/main.c

NFA.o:
	gcc -c -I include src/NFA.c

hashmap.o:
	gcc -c -I include src/hashmap.c

parse.o:
	gcc -c -I include src/parse.c

postfix.o:
	gcc -c -I include src/postfix.c

clean:
	rm -f main.o NFA.o hashmap.o parse.o postfix.o bin/run/NFA