#include <unistd.h>
typedef struct struct_linked_list
{	
	int size;
	void* content;
	struct struct_linked_node* next;
}linked_list;
typedef struct struct_linked_node
{
	void* content;
	struct struct_linked_node* next;
}linked_node;
//Inicia el primer nodo de la lista con la estructura a la que apunte inicializada a 0.
linked_list* create(int size);
//Inicializa la lista con un elemento dado
int open_up(int size, void *element);
//Inserta un elemento en la lista en la posición que indica index.
int insert_at(int index , void* elemento, linked_list* list);
//Elimina de la lista un elemento, pero no libera la memoria que éste ocupa.
int del_at(int index, linked_list* list);
//Elimina un elemento de la lista y libera la memoria que la estrcutura ocupa.
int free_at(int index, linked_list* list);
//copia en la dirección apuntada por 'elemento' el elemento en la posición 'index' de la lista.
int get_at (int index, void* elemento,  linked_list* list);
//Devuelve el tamaño de la lista en número de elementos.
int get_size(linked_list* list);