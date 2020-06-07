void addToLast(Node * head, int val) {
    Node * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(Node));
    current->next->val = val;
    current->next->next = NULL;
}




int addToIndex(Node ** head, int val, int n) {
    int i = 0;
    Node * current = *head;
    Node * temp_node = NULL;

    if (n == 0) {
        *head = malloc(sizeof(Node));
        (*head)->val = val;
        (*head)->next = current;
        return 0;
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    temp_node = current->next;
    current->next = malloc(sizeof(Node));
    current->next->val = val;
    current->next->next = temp_node;

    return 0;
}

void removeLast(Node * head) {
    Node * current;
    if (head->next == NULL) {
        free(head);
        return;
    }

    current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
}


int removeByIndex(Node ** head, int n) {
    int i = 0;
    Node * current = *head;
    Node * temp_node = NULL;

    if (n == 0) {
        temp_node = (*head)->next;
        free(*head);
        *head = temp_node;
        return 0;
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    temp_node = current->next;
    current->next = temp_node->next;
    free(temp_node);

    return 0;
}



Node * arrayToLinkedList(int arr[], int size){
    Node * n = NULL;
    Node * head = NULL;
    int i = 0;

    if(size>0){
        n = malloc(sizeof(Node));
        n->val = arr[0];
        n->next = NULL; 
    }

    head = n;

    for (i = 1; i < size; ++i){
        n->next = malloc(sizeof(Node));
        n->next->val = arr[i];
        n->next->next = NULL;
        n = n->next;
    }

    return head;
}

