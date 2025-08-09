#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    int priority;
    struct Node *next;
} Node;

typedef struct {
    Node *front;  // Highest priority element
    Node *rear;   // Last element in queue
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
    pq->front = NULL;
    pq->rear = NULL;
}

// Check if the queue is empty
bool isEmpty(PriorityQueue *pq) {
    return pq->front == NULL;
}

// Insert with priority (max-priority queue)
void enqueue(PriorityQueue *pq, int data, int priority) {
    Node *newNode = createNode(data, priority);
    
    // Case 1: Empty queue
    if (isEmpty(pq)) {
        pq->front = newNode;
        pq->rear = newNode;
        return;
    }
    
    // Case 2: New node has higher priority than front
    if (priority > pq->front->priority) {
        newNode->next = pq->front;
        pq->front = newNode;
        return;
    }
    
    // Case 3: New node has lower priority than rear
    if (priority <= pq->rear->priority) {
        pq->rear->next = newNode;
        pq->rear = newNode;
        return;
    }
    
    // Case 4: Insert somewhere in middle
    Node *current = pq->front;
    while (current->next != NULL && current->next->priority >= priority) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    
    // Update rear if we inserted at the end
    if (newNode->next == NULL) {
        pq->rear = newNode;
    }
}

// Remove the highest priority element
int dequeue(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty!\n");
        return -1;
    }
    
    Node *temp = pq->front;
    int data = temp->data;
    
    pq->front = pq->front->next;
    
    // If queue becomes empty
    if (pq->front == NULL) {
        pq->rear = NULL;
    }
    
    free(temp);
    return data;
}

// Get the highest priority element
int peekFront(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty!\n");
        return -1;
    }
    return pq->front->data;
}

// Get the last element
int peekRear(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty!\n");
        return -1;
    }
    return pq->rear->data;
}

// Display the priority queue
void display(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty\n");
        return;
    }
    
    printf("Priority Queue (data:priority): ");
    Node *current = pq->front;
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
    
    printf("Front element: %d (highest priority)\n", peekFront(&pq));
    printf("Rear element: %d\n", peekRear(&pq));
    
    dequeue(&pq);
    display(&pq);
    
    enqueue(&pq, 60, 0);
    display(&pq);
    
    printf("New rear element: %d\n", peekRear(&pq));
    
    freeQueue(&pq);
    
    return 0;
}