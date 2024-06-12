//Name:Xiangying Sun
//Email: sun.xiangyi@northeastern.edu
#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
}node_t;

typedef struct list{
    struct node* head;
}List;

/*-----creating the nodes----------*/
node_t* newNode(int num)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node) {
        printf("Memory allocation error\n");
        exit(1);
    }
    new_node -> data = num;
    new_node -> next = NULL;
    return new_node;
}
/*---creating linked list----*/
List* init_LL(){
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        printf("Memory allocation error\n");
        exit(1);
    }
    list->head = NULL;
    return list;
}

/*---Insert the nodes at the begining of the list---*/
void insertFirst(List* l, int data){
    node_t* new_node = newNode(data);
    new_node -> next = l->head;
    l->head = new_node;
}

/*----display the output--------*/
void display(List* l)
{
    node_t *temp;
    temp=l->head;
    while(temp!=NULL)
    {
        printf("%d->",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}

/*-------reversing the linked list using recursion------*/
void reverseUtil(node_t **head, node_t *curr, node_t *prev) {
    if (!curr) {
        *head = prev;
        return;
    }
    node_t *next = curr->next;
    curr->next = prev;
    reverseUtil(head, next, curr);
}

void reverse(List *l, node_t *ptr) {
    reverseUtil(&(l->head), ptr, NULL);
}

/*----Free the nodes-----*/
void freenode(List* l){
  node_t *temp;
    while(l->head)
    {
        temp=l->head->next;
        free(l->head);
        l->head=temp;
    }  
    
}
/*-----Main program--------------*/
int main()
{
    List *list=init_LL();
    

    insertFirst(list,44);
    insertFirst(list,33);
    insertFirst(list,22);
    insertFirst(list,11);
    display(list);
    reverse(list,list->head);
    display(list);
    
    freenode(list);
    free(list);
    return 0;
}
