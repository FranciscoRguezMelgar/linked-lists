#include <unistd.h>
typedef struct struct_linked_list
{	
	int size;
	struct struct_linked_node* next;
}linked_list;
typedef struct struct_linked_node
{
	void* content;
	struct struct_linked_node* next;
}linked_node;
//Inicia el primer nodo de la lista con la estructura a la que apunte inicializada a 0.
linked_list* create(int size);
//Inserta un elemento en la lista en la posición que indica index.
int insert_at(linked_list* list, int index , void* elemento);
//Elimina de la lista un elemento, pero no libera la memoria que éste ocupa.
int del_at(linked_list* list, int index);
//copia en la dirección apuntada por 'elemento' el elemento en la posición 'index' de la lista.
int get_at (linked_list* list, int index , void* elemento);
//Cambia el contenido del nodo en posición index por el que se le dé en element
int owrite_at(linked_list* list, int index, void* elemento);
//Devuelve el tamaño de la lista en número de elementos.
int get_size(linked_list* list);