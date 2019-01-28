#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

struct node{
    int data;
    int key;
    struct node *neighbor;
};


struct node *head = NULL;
struct node *last = NULL;
struct node *current = NULL;

bool isEmpty(){
    return head == NULL;
}

//XOR operation on two point-to-struct-node pointers
struct node* XOR(struct node* a, struct node* b){
    return (struct node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

int length(){
    int length = 0;
    struct node *current = head;
    struct node *previous =  NULL;
    struct node *temp;
    while (current != NULL){
        ++length;        
        temp = current;
        current = XOR(previous, current->neighbor);
        previous = temp;
    }
    return length;
}

void insertFirst(int key, int data){
    struct node *link = (struct node*) malloc(sizeof(struct node));
    link-> key = key;
    link -> data = data;
    if(isEmpty())
        last = link;
    else{
        head->neighbor = XOR(head->neighbor,link);
    }
    link->neighbor = head;
    head = link;
}

void insertLast(int key, int data){
    struct node *link = (struct node*) malloc(sizeof(struct node));
    link-> key = key;
    link -> data = data;
    if (isEmpty())
        head = link;
    else{
        last->neighbor = XOR(last->neighbor, link);
    }
    link->neighbor = last;
    last = link;
}

bool insertAfter(int key , int newkey, int data){
    if (isEmpty())
        return false;

    struct node *current = head;
    struct node *previous = NULL;
    struct node *temp;
    int count = 1;
    
    //search the position
    while (current->key !=key){
        if (previous == current->neighbor)
            return false;
        else {
            temp = current;
            current = XOR(current->neighbor, previous);
            previous = temp;
        }
    }

    //create new node
    struct node *link = (struct node*) malloc(sizeof(struct node));
    link-> key = newkey;
    link -> data = data;

    //add the new node
    if (current == last){
        link->neighbor =current;
        last = link;
    } else{
        struct node* next =  XOR(current->neighbor,previous);
        next->neighbor = XOR(link, XOR(next->neighbor, current));
        link->neighbor = XOR(current, next);        
    }
    current->neighbor = XOR(previous, link);
    return true;

}

struct node* delete(int key){
    struct node* current = head;
    struct node* previous = NULL;

    if(isEmpty())
        return NULL;

    // search the will-be-deleted node
    while (current->key != key){
        if (current == last)
            return NULL;
        else{
            struct node* temp = current;
            current = XOR(previous,current->neighbor);
            previous = temp;
        }
    }

    //delete the node
    if (current == head){
        head->neighbor->neighbor= XOR(head->neighbor->neighbor,head);
        head = head->neighbor;
    }
    else if (current == last){
        last->neighbor->neighbor=XOR(last->neighbor->neighbor,last);
        last = last->neighbor;
    } else {
        struct node* next = XOR(current->neighbor, previous);
        next->neighbor = XOR(previous, XOR(current, next->neighbor));
        previous->neighbor = XOR(next, XOR(previous->neighbor, current));
    }

    return current;
}

void displayForward(){
    struct node *ptr = head;
    struct node *previous = NULL;
    struct node *temp;
    printf("\n[ ");

    while(ptr != NULL){
        printf("(%d, %d) ", ptr->key, ptr->data);
        temp = ptr;
        ptr = XOR(ptr->neighbor, previous);
        previous = temp;

    }
    printf(" ]\n");
}

void displayBackward(){
    struct node *ptr = last;
    struct node *previous = NULL;
    struct node *temp;
    printf("\n[ ");

    while(ptr != NULL){
        printf("(%d, %d) ", ptr->key, ptr->data);
        temp = ptr;
        ptr = XOR(ptr->neighbor, previous);
        previous = temp;

    }
    printf(" ]\n");
}


void main(){
    insertLast(1,10);
    displayForward();
    insertLast(2,20);
    insertFirst(3,20);
    insertAfter(2,5,50);
    insertAfter(5,4,40);
    delete(1);;
    displayForward();
    displayBackward();
    printf("%d", length());

}
