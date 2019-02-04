#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//typedef int Item_type;
typedef enum {FAILURE, SUCCESS} statuscode;

typedef struct Node_tag {
	int data;
	struct Node_tag * next;
} Node_type;

Node_type *CreateList(int num){

	Node_type *list_ptr, *nptr;
	statuscode sc;
	list_ptr = NULL;
	for (int i = 0; i < num; i++)
	{
		nptr = (Node_type *)malloc(sizeof(Node_type));
		nptr->data = i;
		nptr->next = list_ptr;
		list_ptr = nptr;
	}
	return list_ptr;
}

statuscode InsertAtStart(Node_type **list_ptr, int d){

	Node_type *nptr;
	statuscode sc = SUCCESS;

	nptr = (Node_type *)malloc(sizeof(Node_type));

	if(nptr != NULL){

		nptr->data = d;
		nptr->next = *list_ptr;
		*list_ptr = nptr;
	}
	else{
		sc = FAILURE;
	}
	return sc;
}

Node_type *InsertAtEnd(Node_type *list_ptr, int d){

	Node_type *nptr, *ptr;

	nptr = (Node_type *)malloc(sizeof(Node_type));
	nptr->data = d;
	nptr->next = NULL;
	if(list_ptr == NULL){
		list_ptr = nptr;
	}
	else {
		ptr = list_ptr;
		while(ptr->next !=NULL){
			ptr = ptr->next;
		}
		ptr->next = nptr;
	}
	return list_ptr;
}

Node_type *DeleteList(Node_type *list_ptr){

	Node_type *nptr;

	if(list_ptr == NULL) {
		printf("List is already empty\n");
	}
	else {
		while(list_ptr != NULL){
			nptr = list_ptr;
			list_ptr = list_ptr->next;
			printf("Data Deleted = %d\n", nptr->data);
			free(nptr);
		}
	}
	return list_ptr;
}

Node_type *DeleteAtStart(Node_type *list_ptr, int *dptr){

	Node_type *nptr ;
	nptr = list_ptr;
	if (list_ptr != NULL)
	{
		list_ptr = list_ptr->next;
		*dptr = nptr->data;
		free(nptr);
	}
	return list_ptr;
}

Node_type *DeleteAtEnd(Node_type *list_ptr, int *dptr){

	Node_type *prev, *ptr;
	if(list_ptr != NULL){
		if(list_ptr->next == NULL){
			*dptr = list_ptr->data;
			free(list_ptr);
			list_ptr = NULL;
		}
		else{
			ptr = list_ptr;
			while(ptr->next != NULL){
				prev = ptr;
				ptr = ptr->next;
			}
			prev->next = NULL;
			*dptr = ptr->data;
			free(ptr);
		}
	}
	return list_ptr;
}

void TraverseList(Node_type *list_ptr){

	Node_type *nptr;
	int i;

	if(list_ptr == NULL) {
		printf("List is Empty \n");
	}
	else {
		nptr = list_ptr;
		i=0;
		while(nptr != NULL) {
			printf("Data in Node = %d\n",nptr->data);
			i++;
			nptr = nptr->next;
		}
	}
}

bool is_element_of(int x, Node_type *list_ptr){
	Node_type *nptr;
	bool retval=false;
	if(list_ptr != NULL){
		int flag=0;
		nptr = list_ptr;
		while(nptr!=NULL && flag==0){
			if(nptr->data == x){
				flag=1;
				retval=true;
			}
			else {
				nptr = nptr->next;
			}
		}
	}
	return retval;
}

bool is_empty(Node_type *list_ptr){
	Node_type *nptr;
	bool retval=false;
	if(list_ptr == NULL){
		retval = true;
	}
	return retval;
}

int size(Node_type *list_ptr){
	Node_type *nptr;
	int len = 0;
	if(list_ptr == NULL){
		len = 0;
	}
	else {
		nptr = list_ptr;
		while(nptr != NULL){
			len++;
			nptr = nptr->next;
		}
	}
	return len;
}

int main()
{
	Node_type *list_ptr;
	statuscode sc;
	list_ptr = NULL;
	int ch, dt, x, len, node;
	bool bl;
	ch=1;

	//CREATE NEW NODES OF LIST
	printf("Enter number of Nodes: ");
	scanf("%d", &node);
	list_ptr = CreateList(node);

	printf("1. Insert At Start \n2. Insert At End \n3. Delete At Start \n4. Delete At End\n5. Delete List\n6. Traverse List\n7. Is_ELEMENT_OF\n8. Is_Empty\n0. Exit\n");

	while(ch){
		scanf("%d", &ch);
		switch(ch){
			case 1: sc = InsertAtStart(&list_ptr, 5);
					if(sc == SUCCESS) {
						printf("Insert Success\n");
					}
					else {
						printf("Insert Fail\n");
					}
					break;

			case 2: list_ptr = InsertAtEnd(list_ptr, -1);
					printf("Insert Success\n");
					break;

			case 3: list_ptr = DeleteAtStart(list_ptr, &dt);
					printf("%d Deleted Successfully !\n", &dt);
					break;

			case 4: list_ptr = DeleteAtEnd(list_ptr, &dt);
					printf("%d Deleted From End\n");
					break;

			case 5: list_ptr = DeleteList(list_ptr);
					break;

			case 6: TraverseList(list_ptr);
					break;

            case 7: printf("Enter the element to search : ");
                    scanf("%d", &x);
                    is_element_of(x, list_ptr) ? printf("FOUND\n") : printf("NOT FOUND\n");
                    break;

			case 8: is_empty(list_ptr) ? printf("Empty") : printf("Not Empty");
					break;

			case 9: len = size(list_ptr);
					printf("Size of Set : %d", len);
					break;

			case 10:

			//case 10:

        }

	}
	return 0;
}
