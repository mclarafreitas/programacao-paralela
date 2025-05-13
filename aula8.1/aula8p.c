#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

typedef struct Node {
    char filename[100];
    struct Node* next;
} Node;

Node* create_node(const char* filename) {
    Node* node = malloc(sizeof(Node));
    strcpy(node->filename, filename);
    node->next = NULL;
    return node;
}

void append(Node** head, const char* filename) {
    Node* new_node = create_node(filename);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
}

int main() {
    Node* fileList = NULL;
    append(&fileList, "documento1.txt");
    append(&fileList, "relatorio_final.pdf");
    append(&fileList, "imagem.png");
    append(&fileList, "notas.csv");

    printf("Iniciando região paralela...\n");

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            printf("Total de threads: %d\n", omp_get_num_threads());

            Node* current = fileList;
            while (current != NULL) {
                Node* nodeCopy = current;
                #pragma omp task firstprivate(nodeCopy)
                {
                    int tid = omp_get_thread_num();
                    printf("Thread %d processando: %s\n", tid, nodeCopy->filename);
                }
                current = current->next;
            }

            #pragma omp taskwait
            printf("Todas as tarefas foram concluídas.\n");
        }
    }

    return 0;
}
