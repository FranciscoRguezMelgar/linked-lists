#include <stdio.h>
#include "linked_list.h"

#define ELEMENTOS 10

void imprimir(void* puntero){
	int coso = *((int*) puntero);

	printf("%i\n", coso);
}

int main(){
	int ii = 0;
	linked_list* list = create(sizeof(int));

	for( ii = 0; ii < ELEMENTOS; ii++){
		insert_at(list, get_size(list), &ii);
	}
	show(list, imprimir);
	
	return 0;

}