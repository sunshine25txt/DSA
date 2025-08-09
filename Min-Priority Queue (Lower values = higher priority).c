typedef struct {
    Node *head;
} MinPriorityQueue;

void initializeMinQueue(MinPriorityQueue *pq) {
    pq->head = NULL;
}

bool isMinQueueEmpty(MinPriorityQueue *pq) {
    return pq->head == NULL;
}

void minEnqueue(MinPriorityQueue *pq, int data, int priority) {
    Node *newNode = createNode(data, priority);
    
    // Insert at head if empty or lower priority than head
    if (isMinQueueEmpty(pq) || priority < pq->head->priority) {
        newNode->next = pq->head;
        pq->head = newNode;
        return;
    }
    
    // Find insertion point (maintains ascending priority order)
    Node *current = pq->head;
    while (current->next != NULL && current->next->priority <= priority) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
}

int minDequeue(MinPriorityQueue *pq) {
    if (isMinQueueEmpty(pq)) {
        printf("Queue is empty!\n");
        return -1;
    }
    
    Node *temp = pq->head;
    int data = temp->data;
    pq->head = pq->head->next;
    free(temp);
    return data;
}

int peekMin(MinPriorityQueue *pq) {
    if (isMinQueueEmpty(pq)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return pq->head->data;
}