#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
linked_list* create(int size){
	linked_list* list = (linked_list*) malloc(sizeof(linked_list));
	list->next = NULL;
	list->content = malloc(size);
	bzero(list->content, size);
	list->size = size;
	return list;
}
int open_up(int size, void* element){
	linked_list* list = (linked_list*) malloc(sizeof(linked_list));
	list->next = NULL;
	list->content = element;
	bzero(list->content, size);
	list->size = size;
	return 0;
}
int insert_at(int index , void* element, linked_list* list){
	int ii=0;
	int size=0;
	linked_node* current_node = (linked_node*)malloc(sizeof(linked_node));
	linked_node* new_node = (linked_node*)malloc(sizeof(linked_node));
	linked_list* newList = (linked_list*)malloc(sizeof(linked_list));;
	if(index > 1){
		if(get_size(list)!=0){
			size = list->size;
		}
		else{
			printf("Lista no inicializada\n");
			return -1;
		}
		for (ii = 0; ii < index-1; ++ii){ /*NÓTESE QUE LA CONDICIÓN HA CAMBIADO (ii < index-1)*/
			if(ii==0&&list->next!=NULL) current_node = list->next;
			else if(current_node->next!=NULL){			
				current_node=current_node->next;
			}	
			else{
				printf("El índice está fuera de rango.\n");		
				return -1 ;/*Código de índice incorrecto, demasiado bajo o demasiado alto.*/
			}
		}
		new_node->next = current_node->next;
		new_node->content = element;
		current_node->next=new_node;
		return 0;
	}else if(index==0){
		if(get_size(list)!=0){
			new_node->content = list->content;
			new_node->next = list->next;
			list->content = element;
			list->next = new_node;			
		}else{
			printf("Lista no inicializada.\n");
			return -1;
		}
		return 0;
	}else if(index==1){
		new_node->next = list->next;
		new_node->content = element;
		list->next = new_node;
	}	
}
int del_at(int index, linked_list* list){
	int ii=0;
	int size=0;
	linked_node* current_node = (linked_node*)malloc(sizeof(linked_node));
	if(index > 1){
		if(get_size(list)!=0){
			size = list->size;
		}
		else{
			printf("Lista no inicializada\n");
			return -1;
		}
		for (ii = 0; ii < index-1; ++ii){ /*NÓTESE QUE LA CONDICIÓN HA CAMBIADO (ii < index-1)*/
			if(ii==0&&list->next!=NULL) current_node = list->next;
			else if(current_node->next!=NULL){			
				current_node=current_node->next;
			}	
			else{
				printf("El índice está fuera de rango.\n");		
				return -1 ;/*Código de índice incorrecto, demasiado bajo o demasiado alto.*/
			}
		}
		linked_node* trash;
		trash = current_node->next;
		current_node->next=current_node->next->next;
		free(trash);
		return 0;
	}else if(index==0){
		if(get_size(list)>1){
			linked_node* trash;
			list->content = list->next->content;
			trash = list->next;
			list->next = list->next->next;
			free(trash);
			return 0;
		}else if(get_size(list)==1){
			free(list);
			printf("\tSe ha eliminado el último elemento de la lista, \n\tes necesario igualar list a NULL fuera del método\n");
			return 1; //código de lista vacía, necesario igualar list a NULL fuera del método.
		}else if(get_size(list)==0){
			printf("Lista no inicializada.\n");
			return -1;
		}
		return 0;
	}else if(index==1){
		if(get_size(list)<2){
			printf("El índice está fuera de rango.\n");		
			return -1;
		}
		linked_node* trash;
		trash = list->next;
		list->next = list->next->next;
		free(trash);
	}
}

int get_at (int index, 	void* element,  linked_list* list){
	int ii=0;
	int size=0;	
	linked_node* current_node;
	if(get_size(list)!=0){
		size = list->size;
	}
	else{
		printf("Lista no inicializada\n");
		return -1;
	}
	if(index > 0){
		for (ii = 0; ii < index; ++ii){
			if(ii==0&&list->next!=NULL) current_node = list->next;
			else if(current_node->next!=NULL){			
				current_node=current_node->next;
			}	
			else{
				printf("El índice está fuera de rango.\n");		
				return -1 ;/*Código de índice incorrecto, demasiado bajo o demasiado alto.*/
			}
		}
		memcpy(element, current_node->content, size);	
		return 0;
	}
	memcpy(element, list->content, size);
	return 0;
}
int get_size(linked_list* list){
	if(list==NULL){
		return 0;
	}else if(list->next==NULL){
		return 1;
	}else{
		linked_node* current_node;
		int ii;
		current_node = list->next;
		for(ii=2;current_node->next!=NULL;ii++){		
				current_node = current_node->next;
		}
		return ii;
	}
}

int main(){
	int i, res, tama;
	char * pepe = (char*) malloc(sizeof(char)*50);

	linked_list* list= create(sizeof(int));

	for(i = 0; i< 4;i++){
			insert_at(get_size(list), &i, list);
	}
	tama =get_size(list);
	printf("El tamaño de la lista es: %d\n", tama);
	for(i = 0; i< get_size(list); i++){
		get_at(i, &res, list);
		printf("en la posición %d hay un %d\n",i, res );
	}
	for(i=0;i < tama; i++){
		if(del_at(0, list)==1){
			list=NULL;
		}
		printf("El tamaño de la lista es: %d\n", get_size(list));	
	}
	printf("hoiuadhfkh\n");
	list= create(sizeof(int));

	for(i = 0; i< 4;i++){
			insert_at(get_size(list), &i, list);
	}

}