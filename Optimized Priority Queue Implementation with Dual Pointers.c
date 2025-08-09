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
} PriorityQueue;

// Create a new node
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

// Initialize the priority queue
void initializeQueue(PriorityQueue *pq) {
    pq->head = NULL;
}

// Check if the queue is empty
bool isEmpty(PriorityQueue *pq) {
    return pq->head == NULL;
}

// Insert with priority using dual-pointer approach
void enqueue(PriorityQueue *pq, int data, int priority) {
    Node *newNode = createNode(data, priority);
    
    // Case 1: Empty queue or new node has highest priority
    if (isEmpty(pq) || priority > pq->head->priority) {
        newNode->next = pq->head;
        pq->head = newNode;
        printf("Enqueued %d with priority %d (at head)\n", data, priority);
        return;
    }
    
    // Case 2: Use dual pointers for insertion
    Node *prev = NULL;
    Node *current = pq->head;
    
    while (current != NULL && current->priority >= priority) {
        prev = current;
        current = current->next;
    }
    
    // Insert between prev and current
    prev->next = newNode;
    newNode->next = current;
    
    printf("Enqueued %d with priority %d (after priority %d)\n", 
           data, priority, prev->priority);
}

// Remove the highest priority element
int dequeue(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty!\n");
        return -1;
    }
    
    Node *temp = pq->head;
    int data = temp->data;
    pq->head = pq->head->next;
    free(temp);
    
    printf("Dequeued %d\n", data);
    return data;
}

// Peek at the highest priority element
int peek(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty!\n");
        return -1;
    }
    return pq->head->data;
}

// Display the priority queue
void display(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty\n");
        return;
    }
    
    printf("Priority Queue (data:priority): ");
    Node *current = pq->head;
    while (current != NULL) {
        printf("%d:%d ", current->data, current->priority);
        current = current->next;
    }
    printf("\n");
}

// Free all memory
void freeQueue(PriorityQueue *pq) {
    while (!isEmpty(pq)) {
        dequeue(pq);
    }
}

int main() {
    PriorityQueue pq;
    initializeQueue(&pq);
    
    enqueue(&pq, 10, 2);
    enqueue(&pq, 20, 3);
    enqueue(&pq, 30, 1);
    enqueue(&pq, 40, 4);
    enqueue(&pq, 50, 2);
    
    display(&pq);
    
    printf("Highest priority element: %d\n", peek(&pq));
    
    dequeue(&pq);
    dequeue(&pq);
    
    display(&pq);
    
    enqueue(&pq, 60, 5);
    enqueue(&pq, 70, 0);
    
    display(&pq);
    
    freeQueue(&pq);
    
    return 0;
}