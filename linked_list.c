#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"
int get_size(linked_list* list){
	int ii = 0;
	linked_node* current_node;
	if(list==NULL){
		printf("\nLista no inicializada\n");
		return -1;
	}
	if(list->next!=NULL){
		ii = 1;
		current_node = list->next;
	}else{
		return 0;
	}
	while(current_node->next!=NULL){
		ii++;
		current_node = current_node->next;
	}
	return ii;
}
linked_list* create(int size){
	linked_list* lista = (linked_list*) malloc(sizeof(linked_list));
	lista->size = size;
	lista->next = NULL;
	return lista;
}
int insert_at(linked_list* list, int index , void* elemento){
	if(elemento==NULL) return -1;
	if(index < 0 || index > get_size(list)){
		printf("Índice fuera de rango\n");
		return -1;
	}
	linked_node* new_node = (linked_node*) malloc(sizeof(linked_node));
	int size = list->size;
	int ii=0;
	linked_node* current_node;
	new_node->content = malloc(size);
	if (index==0){
		//***caso especial de insertar en la posición 0
		new_node->next = list->next;
		list->next = new_node;
		memcpy(new_node->content, elemento, size);
		return 0;
	}//else //si la posición no es 0
	current_node = list->next;
	while(ii<index-1){
		current_node = current_node->next;
		ii++;
	}
	new_node->next = current_node->next;
	current_node->next = new_node;
	memcpy(new_node->content, elemento, size);
	return 0;
}
int del_at(linked_list* list, int index){
	int n_elements = get_size(list);
	if(index < 0 || index > (n_elements - 1)){
		printf("Índice fuera de rango\n");
		return -1;
	}
	int ii=0;
	linked_node* current_node;
	if (index==0){
		//***caso especial de borrar de la posición 0
		free(list->next->content);
		linked_node* trash = list->next;
		list->next = list->next->next;
		free(trash);
		return 0;
	}
	current_node = list->next;
	while(ii<index-1){
		current_node = current_node->next;
		ii++;
	}
	free(current_node->next->content);
	linked_node* trash = current_node->next;
	current_node->next = current_node->next->next;
	free(trash);
	return 0;
}
int get_at (linked_list* list, int index , void* elemento){
	if(elemento==NULL) return -1;
	int n_elements = get_size(list);
	int ii = 0;
	if(index < 0 || index > (n_elements - 1)){
		printf("Índice fuera de rango\n");
		return -1;
	}
	int size = list->size;
	linked_node* current_node;
	current_node = list->next;
	while(ii<index){
		current_node = current_node->next;
		ii++;
	}
	memcpy(elemento, current_node->content, size);
	return 0;
}
void* get_pointer_at (linked_list* list, int index){
	int n_elements = get_size(list);
	int ii = 0;
	if(index < 0 || index > (n_elements - 1)){
		printf("Índice fuera de rango\n");
		return NULL;
	}
	linked_node* current_node;
	current_node = list->next;
	while(ii<index){
		current_node = current_node->next;
		ii++;
	}
	return current_node->content;
}
int owrite_at(linked_list* list, int index, void* elemento){
	if(elemento==NULL) return -1;
	int n_elements = get_size(list);
	int ii = 0;
	if(index < 0 || index > (n_elements - 1)){
		printf("Índice fuera de rango\n");
		return -1;
	}
	int size = list->size;
	linked_node* current_node;
	current_node = list->next;
	while(ii<index){
		current_node = current_node->next;
		ii++;
	}
	memcpy(current_node->content, elemento, size);
	return 0;
}
void show(linked_list* list, void (funct_print)(void*)){
	int i;
	int tama = get_size(list);
	for(i = 0;i < tama; i++){		
		(funct_print)(get_pointer_at(list, i));
	}
}

//MÉTODOS PARA SER USADA COMO COLA


int enqueue(linked_list* list, void* elemento){
	return insert_at(list, 0, elemento);
}

int dequeue(linked_list* list, void* elemento){
	int error = 0;
	error = get_at(list, get_size(list)-1, elemento);
	if (error !=0) return error;
	del_at(list, get_size(list)-1);
	return error;
}




