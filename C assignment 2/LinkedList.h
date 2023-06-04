#ifndef LL_H
#define LL_H

typedef struct LinkedListNode
{
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

typedef struct
{
    LinkedListNode* head;
    int count;
} LinkedList;

typedef struct
{
    int pRow;
    int pCol;
    int sRow;
    int sCol;
    char pSign;
} Position;

typedef void (*listFunc) (void* data);
LinkedList* createLinkedList();
void insertStart(LinkedList* list, void* entry);
void* removeStart(LinkedList* list);
void freeLinkedList(LinkedList* list, listFunc funcPtr);
void freeNode(void* data);
#endif
