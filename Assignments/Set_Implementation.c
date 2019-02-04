/*
										CONCEPTS IN PROGRAMMING LANGUAGES
													ASSIGNMENT 1


CODE PREPARED and SUBMITTED BY:		MADHUR TRIVEDI
									BT17CSE039
									Computer Science and Engineering Department,
									VISVESVARAYA NATIONAL INSTITUTE of TECHNOLOGY,
									NAGPUR
*/

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
	for (int i = 1; i <= num; i++)
	{
		nptr = (Node_type *)malloc(sizeof(Node_type));
		nptr->data = i;
		nptr->next = list_ptr;
		list_ptr = nptr;
	}
	return list_ptr;
}

Node_type *InsertAtStart(Node_type *list_ptr, int d){

	Node_type *nptr;

	nptr = (Node_type *)malloc(sizeof(Node_type));

	if(nptr != NULL){

		nptr->data = d;
		nptr->next = list_ptr;
		list_ptr = nptr;
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

void DisplayList(Node_type *list_ptr){

	Node_type *nptr;
	int i;

	if(list_ptr == NULL) {
		printf("Set is Empty \n\n");
	}
	else {
		nptr = list_ptr;
		printf("{  ");
		while(nptr != NULL) {
			printf("%d  ",nptr->data);
			nptr = nptr->next;
		}
		printf("}\n\n");
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


void enumerate(Node_type *list_ptr){
	DisplayList(list_ptr);
}

Node_type *create(){
	Node_type *nptr;
	//nptr = (Node_type *)malloc(sizeof(Node_type));
	nptr = NULL;
	return nptr;
}

Node_type *add(Node_type *list_ptr, int x){

	if(!is_element_of(x, list_ptr)){
		list_ptr = InsertAtStart(list_ptr, x);
		//printf("%d inserted successfully\n", x);
	}
	return list_ptr;
}

Node_type *Remove(Node_type *list_ptr, int x){

	Node_type *nptr, *prev;

	if(list_ptr == NULL){
		printf("Set is Empty\n\n");
	}
	else{
		nptr = list_ptr;
		prev = NULL;

		while(nptr->data != x && nptr->next != NULL){

			prev = nptr;
			nptr = nptr->next ;
		}

		if(nptr->data == x){
			//Remove Item at first node
			if(prev!=NULL){
				prev->next = nptr->next;
			}
			//otherwise
			else {
				list_ptr = nptr->next;
			}
			free(nptr);
			printf("Removed Successfully\n\n");
		}
		else
		{
			printf("%d not found\n\n", x);
		}
	}
	return list_ptr;
}

Node_type *build(int n){
	Node_type *nptr=NULL;
	int x;
	//nptr = CreateList(n);
	for(int i=0; i<n; i++){
		printf("Element: ");
		scanf("%d", &x);
		if(!is_element_of(x, nptr)){
			nptr = add(nptr, x);
		}
	}
	printf("Set : ");
	DisplayList(nptr);
	return nptr;
}

Node_type *Union(Node_type *s, Node_type *t){
	Node_type *result, *head1, *head2;
	result = NULL;
	head1 = s; head2 = t;

	while(head1 != NULL) {
		result = add(result, head1->data);
		head1 = head1->next;
	}

	while(head2 != NULL){
		if(!is_element_of(head2->data, head1)){
			result = add(result, head2->data);
		}
		head2 = head2->next;
	}
	return result;
}

Node_type *intersection(Node_type *s, Node_type *t){
	Node_type *result, *head;
	result = NULL;
	head = s;

	while(head != NULL){
		if(is_element_of(head->data, t)){
			result = add(result, head->data);
		}
		head = head->next;
	}
	return result;
}

Node_type *difference(Node_type *s, Node_type *t){
	Node_type *result, *head1, *head2;
	result = NULL;
	head1 = s; head2 = t;

	//head1 - head2
	while(head1 != NULL){
		if(!is_element_of(head1->data, head2)){
			result = add(result, head1->data);
		}
		head1 = head1->next;
	}
	return result;
}

bool subset(Node_type *s, Node_type *t){
	Node_type *head1, *head2;
	head1 = s; head2 = t;
	bool isSub = true;

	while(head1 != NULL && isSub){
		if(is_element_of(head1->data, head2)){
			head1 = head1->next;
		}
		else{
			isSub = false;
		}
	}
	return isSub;
}

void Static(Node_type *list_ptr){

	int ch=1, x, n;
	printf("\nStatic Set ---- \n");
	printf("\n\t0. Exit\n\t1. Is_Element_Of\n\t2. Is_Empty\n\t3. Size\n\t4. Enumerate\n\t5. Build\n\n");

	while(ch){
		printf("Enter Your Choice here : ");
		scanf("%d", &ch);
		printf("\n");
		switch(ch){
			case 1: printf("Enter the element to check : ");
					scanf("%d", &x);
					is_element_of(x, list_ptr) ? printf("....YES....\n\n") : printf("....NO....\n\n");
					break;

			case 2: is_empty(list_ptr) ? printf("....YES....\n\n") : printf("....NO....\n\n");
					break;

			case 3: printf("Size of Set is : %d \n\n", size(list_ptr));
					break;

			case 4: enumerate(list_ptr);
					break;

			case 5:	printf("How many no. of elements you want to build a set : ");
					scanf("%d", &n);
					list_ptr = build(n);
					break;
		}
	}
}

Node_type *Dynamic(Node_type *l_ptr){

	Node_type *list_ptr;
	list_ptr = l_ptr;
	int ch=1, x, n;

	printf("\nDynamic Set ---- \n");
	printf("\n\t0. Exit\n\t1. Create\n\t2. Add\n\t3. Remove\n\t4. Show Set\n\n");

	while(ch){
		printf("Enter your choice here: ");
		scanf("%d", &ch);
		printf("\n");
		switch(ch){

			case 1: list_ptr=create();
					printf("Success\n\n");
					break;

			case 2: printf("Enter the element to add : ");
					scanf("%d", &x);
					list_ptr = add(list_ptr, x);
					printf("Added Successfully\n\n");
					break;

			case 3: printf("Enter the element to delete : ");
					scanf("%d", &x);
					list_ptr = Remove(list_ptr, x);
					break;

			case 4: DisplayList(list_ptr);
					break;
		}
	}

	return list_ptr;
}

Node_type *input_set(Node_type *lptr){

	int x=1;
	while(x){
		printf("Element : ");
		scanf("%d", &x);
		lptr = add(lptr, x);
	}
	return lptr;
}

void Operations(){

	Node_type *s, *t;
	s=NULL; t=NULL;
	int ch=1;

	printf("Add Elements in The First Set (S) : ");
	printf("(0 to exit) : \n\n");
	s = input_set(s);


	printf("\n\nAdd Elements in The Second Set (T) : ");
	printf("(0 to exit) : \n\n");
	t = input_set(t);

	printf("\n3. Operations on two sets : \n\n");
	printf("Set S : ");
	DisplayList(s);
	printf("\nSet T : ");
	DisplayList(t);

	printf("\nOperations on two Sets : \n");
	printf("\n\t0. Exit\n\t1. Union (S u T)\n\t2. Intersection (S n T)\n\t3. Difference (S - T)\n\t4. Subset (S c T)\n\n");

	while(ch){
		printf("Enter your choice here : ");
		scanf("%d", &ch);
		printf("\n");
		switch(ch){

			case 1: printf("Union of Sets : \n");
					DisplayList(Union(s, t));
					break;

			case 2: printf("Intersection of Sets : \n");
					DisplayList(intersection(s, t));
					break;

			case 3: printf("Difference of Sets : \n");
					DisplayList(difference(s, t));
					break;

			case 4: subset(s, t) ? printf("YES set S is Subset of T \n\n") : printf("NO set S is not Subset of T \n\n");
					break;
		}
	}
}

int main()
{
	Node_type *list_ptr;
	list_ptr = NULL;
	int n, x, ch=1;

	//list_ptr = CreateList(10);

	printf("\n\n\n==============================W E L C O M E==============================\n\n\n");

	while(ch){
		printf("********************************************\n");
		printf("\n\t1. Dynamic Set ---- \n");
		printf("\n\t2. Static Set ---- \n");
		printf("\n\t3. Operations on two sets : \n");
		printf("\n\t0. Exit\n\n");
		printf("********************************************\n\n");

		printf("Enter a choice : ");
		scanf("%d", &ch);
		printf("\n");
		switch(ch){
			case 1: list_ptr = Dynamic(list_ptr);
					break;

			case 2: Static(list_ptr);
					break;

			case 3: Operations();
					break;
		}
	}

	printf("\n\nThanks for your time\n Have a nice day.....\n\n\n");
	return 0;
}

