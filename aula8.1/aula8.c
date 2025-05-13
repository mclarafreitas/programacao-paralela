#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó
typedef struct Node {
    char filename[100];
    struct Node* next;
} Node;

// Função para criar um novo nó
Node* createNode(const char* filename) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    strncpy(newNode->filename, filename, sizeof(newNode->filename));
    newNode->filename[sizeof(newNode->filename) - 1] = '\0'; // Garante terminação
    newNode->next = NULL;
    return newNode;
}

// Função para adicionar um nó ao final da lista
void append(Node** head, const char* filename) {
    Node* newNode = createNode(filename);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

// Função para imprimir os nomes dos arquivos
void printList(Node* head) {
    Node* current = head;
    printf("Lista de arquivos:\n");
    while (current != NULL) {
        printf("- %s\n", current->filename);
        current = current->next;
    }
}

// Função para liberar a memória alocada
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* fileList = NULL;

    // Adicionando arquivos fictícios
    append(&fileList, "documento1.txt");
    append(&fileList, "relatorio_final.pdf");
    append(&fileList, "imagem.png");
    append(&fileList, "notas.csv");

    // Imprimir a lista
    printList(fileList);

    // Liberar memória
    freeList(fileList);

    return 0;
}
