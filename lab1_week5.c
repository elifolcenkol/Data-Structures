
#include <stdio.h>
#include <stdlib.h>

// Yığın veri yapısı tanımı
struct Stack {
    char data;
    struct Stack* next;
};

// Yığın işlemleri
void push(struct Stack** stack, char data) {
    struct Stack* newNode = (struct Stack*)malloc(sizeof(struct Stack));
    newNode->data = data;
    newNode->next = *stack;
    *stack = newNode;
}

char pop(struct Stack** stack) {
    if (*stack == NULL) {
        return 0; // Yığın boşsa 0 döndür
    }
    char data = (*stack)->data;
    struct Stack* temp = *stack;
    *stack = (*stack)->next;
    free(temp);
    return data;
}

int main() {
    struct Stack* stack = NULL;
    FILE* file = fopen("labtxt.txt", "r");

    if (file == NULL) {
        printf("Dosya acilamadi.\n");
        return 1;
    }

    char c;
    int line = 1;
    while ((c = fgetc(file)) != EOF) {
        if (c == '(') {
            push(&stack, c);
        } else if (c == ')') {
            if (pop(&stack) != '(') {
                printf("Parantez hatasi: Satir %d\n", line);
                exit(1);
            }
        } else if (c == '\n') {
            line++;
        }
    }

    // Dosya sonunda yığın boş olmalı
    while (stack != NULL) {
        if (pop(&stack) != 0) {
            printf("Parantez hatasi: kapali parantez eksik\n");
            exit(1);
        }
    }

    printf("Parantez hatasi bulunmadi.\n");
    fclose(file);
    return 0;
}
