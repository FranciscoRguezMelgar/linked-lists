#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

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
//Inicia el primer nodo de la lista , el header, y devuelve un puntero al mismo.
linked_list* create(int size);
/*Inserta un elemento en la lista en la posición que indica index, el elemento se copia, es decir, 
 *se reserva nueva memoria y se copia
 *el elemento apuntado por el tercer argumento en dicha memoria reservada.*/
int insert_at(linked_list* list, int index , void* elemento);
//Elimina de la lista un elemento, y liberar la memoria que ocupaba éste en la lista
int del_at(linked_list* list, int index);
//copia en la dirección apuntada por 'elemento' el elemento en la posición 'index' de la lista.
int get_at (linked_list* list, int index , void* elemento);
//Cambia el contenido del nodo en posición index por el que se le dé en 'element'
int owrite_at(linked_list* list, int index, void* elemento);
//Devuelve el tamaño de la lista en número de elementos.
int get_size(linked_list* list);
/*Imprime los elementos de la lista si se le provee de una función que los imprima.
 * la función debe tener el prototipo func_print(void* elemento); es decir, debe recibir
 * un puntero de void que será en realidad del tipo del elemento a imprimir.
 */
void show(linked_list* list, void (funct_print)(void*));
/////////////MÉTODOS DE COLAS

int enqueue(linked_list* list, void* elemento);

int dequeue(linked_list* list, void* elemento);







#endif
