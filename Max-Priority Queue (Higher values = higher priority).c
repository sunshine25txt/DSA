#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    int priority;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} MaxPriorityQueue;

Node* createNode(int data, int priority) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;
    return newNode;
}

void initializeMaxQueue(MaxPriorityQueue *pq) {
    pq->head = NULL;
}

bool isMaxQueueEmpty(MaxPriorityQueue *pq) {
    return pq->head == NULL;
}

void maxEnqueue(MaxPriorityQueue *pq, int data, int priority) {
    Node *newNode = createNode(data, priority);
    
    // Insert at head if empty or higher priority than head
    if (isMaxQueueEmpty(pq) || priority > pq->head->priority) {
        newNode->next = pq->head;
        pq->head = newNode;
        return;
    }
    
    // Find insertion point (maintains descending priority order)
    Node *current = pq->head;
    while (current->next != NULL && current->next->priority >= priority) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
}

int maxDequeue(MaxPriorityQueue *pq) {
    if (isMaxQueueEmpty(pq)) {
        printf("Queue is empty!\n");
        return -1;
    }
    
    Node *temp = pq->head;
    int data = temp->data;
    pq->head = pq->head->next;
    free(temp);
    return data;
}

int peekMax(MaxPriorityQueue *pq) {
    if (isMaxQueueEmpty(pq)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return pq->head->data;
}