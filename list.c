#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
     return list;
}

void * firstList(List * list) {
    list->current = list->head;
    if (list->current){
        return list->current->data;
      }
    return NULL;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
      if(list->current->next){
      list->current=list->current->next;
      return list->current->data;
      }
    return NULL;
  }

void * lastList(List * list) {
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current == list->head){
      return NULL;
    }
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* node = createNode(data);
    node->next = list->head;
    if (list->head) list->head->prev = node;
    list->head= node;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* node = createNode(data);
    node->next = list->current->next;
    node->prev = list->current;
    if(list->current){
      if (list->current->next) list->current->next->prev = node;
      list->current->next = node;
      }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list->current->next){
        list->current->next->prev = list->current->prev;
      }
    else{list->tail = list->current->prev;}
    if(list->current->prev){
        list->current->prev->next = list->current->next;
      }
    else{list->head = list->current->next;}
    Node* node = list->current;
    if (node->next){
        list->current=node->next;
      }
    void* data = node->data;
      free(node);
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}