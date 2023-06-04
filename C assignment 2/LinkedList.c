#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

LinkedList* createLinkedList()
{
    LinkedList* LL = NULL;
    LL = (LinkedList*)malloc(sizeof(LinkedList));
    LL->head = NULL;
    LL->count = 0;
    return LL;
}

void insertStart(LinkedList* list, void* entry)
{
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->data = entry;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}

void* removeStart(LinkedList* list)
{
    void* data = NULL;
    LinkedListNode* firstNode = list->head;
    if(firstNode != NULL)
    {
        data = firstNode->data;
        list->head = firstNode->next;
        free(firstNode);
        list->count--;
    }
    return data;
}

void freeLinkedList(LinkedList* list, listFunc funcPtr)
{
    /*need 2 pointers, curr and nextCurr*/
    /*these 2 are pointers, so no need free */
    LinkedListNode* curr = list->head;
    LinkedListNode* nextCurr = NULL;
    
    while(curr != NULL)
    {
        nextCurr = curr->next;
        (*funcPtr)(curr->data); /*calls function that free node*/
        free(curr);
        curr = nextCurr;
    }
    free(list);

}

void freeNode(void* data)
{
    free((Position*)data);
}




