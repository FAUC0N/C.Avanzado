#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* insertNode(Node* head, int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL || head->data >= data) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != NULL && current->next->data < data)
            current = current->next;
        
        newNode->next = current->next;
        current->next = newNode;
    }
    return head;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    srand(time(0));
    Node* head = NULL;

    for(int i = 0; i < 10; i++) {
        int num = rand() % 100;
        head = insertNode(head, num);
    }

    printList(head);

    freeList(head);

    return 0;
}