all: main

main-valgrind: main.o lib.o BST.o
	$(CC) main.o lib.o BST.o -o main
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./main
	rm -rf *.o
	
main: main.o lib.o BST.o
	$(CC) main.o lib.o BST.o -lm -o main
	rm -rf *.o
	
lib.o: ./libs/lib.c
	$(CC) ./libs/lib.c -c ./libs/lib.c
	
BST.o: ./libs/BST.c
	$(CC) ./libs/BST.c -c ./libs/BST.c
	
insertion_main.o: main.c
	$(CC) main.c -c main.c
	
clean:
	rm -rf *.o main
