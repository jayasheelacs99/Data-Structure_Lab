#include<stdio.h>
#include<stdlib.h>
struct Node {
    int data;
    struct Node *prev, *next;
} *head = NULL;

struct Node* newNode(int v) {
    struct Node *n = malloc(sizeof(struct Node));
    n->data = v; n->prev = n->next = NULL;
    return n;
}

void insertStart(int v) {
    struct Node *n = newNode(v);
    if (!head) head = n;
    else {
        n->next = head;
        head->prev = n;
        head = n;
    }
}

void insertEnd(int v) {
    struct Node *n = newNode(v), *t = head;
    if (!head) head = n;
    else {
        while (t->next) t = t->next;
        t->next = n;
        n->prev = t;
    }
}

void insertLeft(int key, int v) {
    struct Node *t = head;
    while (t && t->data != key) t = t->next;

    if (!t) { printf("Value %d not found!\n", key); return; }

    struct Node *n = newNode(v);

    if (t == head)
        insertStart(v);
    else {
        n->next = t;
        n->prev = t->prev;
        t->prev->next = n;
        t->prev = n;
    }
}

void deleteStart() {
    if (!head) { printf("List is empty!\n"); return; }

    struct Node *t = head;
    head = head->next;
    if (head) head->prev = NULL;
    free(t);
}

void deleteEnd() {
    if (!head) { printf("List is empty!\n"); return; }

    struct Node *t = head;
    if (!t->next) { free(t); head = NULL; return; }

    while (t->next) t = t->next;
    t->prev->next = NULL;
    free(t);
}

void deleteValue(int key) {
    struct Node *t = head;
    while (t && t->data != key) t = t->next;

    if (!t) { printf("Value %d not found!\n", key); return; }

    if (t == head) deleteStart();
    else if (!t->next) deleteEnd();
    else {
        t->prev->next = t->next;
        t->next->prev = t->prev;
        free(t);
    }
}

void display() {
    struct Node *t = head;
    if (!t) { printf("List is empty!\n"); return; }

    printf("Doubly Linked List: ");
    while (t) {
        printf("%d <-> ", t->data);
        t = t->next;
    }
    printf("NULL\n");
}

int main() {
    int ch, v, k;
     printf("\n--- DOUBLY LINKED LIST MENU ---\n");
        printf("1. Insert at Start\n");
        printf("2. Insert at End\n");
        printf("3. Insert to the Left of a Node\n");
        printf("4. Delete at Start\n");
        printf("5. Delete at End\n");
        printf("6. Delete a Node by Value\n");
        printf("7. Display List\n");
        printf("8. Exit\n");
    while (1) {

        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter value: "); scanf("%d", &v);
                insertStart(v); break;

            case 2:
                printf("Enter value: "); scanf("%d", &v);
                insertEnd(v); break;

            case 3:
                printf("Enter node value to the left of which you want to insert: ");
                scanf("%d", &k);
                printf("Enter new value: "); scanf("%d", &v);
                insertLeft(k, v); break;

            case 4:
                deleteStart(); break;

            case 5:
                deleteEnd(); break;

            case 6:
                printf("Enter value to delete: "); scanf("%d", &k);
                deleteValue(k); break;

            case 7:
                display(); break;

            case 8:
                exit(0);

            default:
                printf("Invalid Choice!\n");
        }
    }
}
