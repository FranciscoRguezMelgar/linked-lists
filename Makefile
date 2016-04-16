all:
	gcc -Wall -c linked_list.c
	ar -rv liblinked_list.a linked_list.o
	gcc -Wall -o prueba prueba.c liblinked_list.a
clean:
	rm *.o
	rm *.a
	rm prueba