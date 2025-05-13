#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_INSERCOES 1000

typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;

typedef struct {
    Node* cabeca;
    pthread_mutex_t mutex;
} ListaEncadeada;

ListaEncadeada lista1 = {NULL, PTHREAD_MUTEX_INITIALIZER};
ListaEncadeada lista2 = {NULL, PTHREAD_MUTEX_INITIALIZER};

void inserir_na_lista(ListaEncadeada* lista, int valor) {
    Node* novo = malloc(sizeof(Node));
    novo->valor = valor;
    novo->proximo = NULL;

    pthread_mutex_lock(&lista->mutex);  // início da região crítica nomeada
    novo->proximo = lista->cabeca;
    lista->cabeca = novo;
    pthread_mutex_unlock(&lista->mutex);  // fim da região crítica nomeada
}

void* tarefa_insercao(void* arg) {
    for (int i = 0; i < NUM_INSERCOES; i++) {
        int valor = rand() % 1000;
        int escolha = rand() % 2;
        if (escolha == 0)
            inserir_na_lista(&lista1, valor);
        else
            inserir_na_lista(&lista2, valor);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    int num_threads = 4;
    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; i++)
        pthread_create(&threads[i], NULL, tarefa_insercao, NULL);

    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    printf("Inserções concluídas.\n");
    return 0;
}
