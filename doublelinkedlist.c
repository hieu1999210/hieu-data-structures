#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    int key;

    struct node *next;
    struct node *prev;
};

struct node *head = NULL;

struct node *last = NULL;

struct node *current = NULL;

bool isEmpty(){
    return head == NULL;
}

int length(){
    int length = 0;
    struct node *current;

    for (current = head; current != NULL; current = current -> next) /* a->b is equivalent to (*a).b */
        length++;
    return length;
}

void displayForward(){
    struct node *ptr = head;
    printf("\n[ ");

    while(ptr != NULL){
        printf("(%d,%d) ", ptr -> key, ptr->data);
        ptr = ptr -> next;  
    }

    printf(" ]\n");
}

void displayBackward(){
    struct node *ptr = last;
    printf("\n[ ");

    while(ptr != NULL){
        printf("(%d, %d) ", ptr->key, ptr->data);
        ptr = ptr->prev;
    }
    printf(" ]\n");
}

void insertFirst(int key, int data){
    struct node *link = (struct node*) malloc(sizeof(struct node));
    link->key = key;
    link->data = data;

    if (isEmpty())
        last = link;
    else
        head->prev = link;
    link->next = head;
    head = link;
}

void insertLast(int key, int data){
    struct node *link = (struct node*) malloc(sizeof(struct node));
    link->key = key;
    link->data = data;

    if(isEmpty())
        head = link;
    else {
        last->next = link;
        link->prev = last;
    }

    last = link;
      
}

struct node* deleteFirst(){
    struct node* tempLink = head;

    if(head->next == NULL)
        last = NULL;
    else
        head->next->prev = NULL;
    head = head->next;
    return tempLink;
}

struct node* deleteLast() {
    struct node *tempLink = last;

    if(head->next == NULL)
        head = NULL;
    else
        last->prev->next = NULL;
    last = last->prev;
    return tempLink;

}

//delete a link with a given key
struct node* delete(int key){
    struct node* current = head;
    struct node* previous = NULL;

    if (isEmpty())
        return NULL;
    while (current->key != key){
        if(current->next == NULL)
            return NULL;
        else{
            previous = current;
            current = current->next;
        }
    }

    if(current == head)
        head = head->next;
    else
        current->prev->next = current->next;

    if(current == last)
        last = current->prev;
    else
        current->next->prev = current-> prev;
    return current;
}

bool insertAfter(int key, int newKey, int data){
    struct node *current = head;
    if (isEmpty())
        return false;
    
    while(current->key != key){
        if (current-> next == NULL)
            return false;
        else
            current = current->next;
    }

    struct node* newLink = (struct node*) malloc(sizeof(struct node));
    newLink->key = newKey;
    newLink->data = data;

    if(current == last){
        newLink->next = NULL;
        current->next = newLink;
    } else{
        newLink->next = current->next;
        current->next->prev = newLink;
    }

    newLink->prev = current;
    current->next = newLink;
    return true;
            
}

void main(){
    insertLast(1,10);
   
    insertFirst(2,20);
    insertFirst(3,30);
    insertFirst(4,1);
    insertFirst(5,40);
    insertFirst(6,46);

    printf("\nList (First to last): ");
    displayForward();

    printf("\n\nList (Last to First): ");
    displayBackward();

    printf("\nList after deleting first record: ");
    deleteFirst();
    displayForward();

    printf("\nList after deleting last record: ");
    deleteLast();
    displayForward();

    printf("\nList insert after key 4: ");
    insertAfter(4,7,13);
    displayForward();

    printf("\nList after deleting key4: ");
    delete(4);
    displayForward();


}