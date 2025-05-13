#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_INSERCOES 1000
#define NUM_THREADS 4

typedef struct Node {
    int valor;
    struct Node* prox;
} Node;

typedef struct ListaEncadeada {
    Node* inicio;
    pthread_mutex_t mutex;
} ListaEncadeada;

ListaEncadeada* listas;
int NUM_LISTAS;

void inserir(ListaEncadeada* lista, int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->valor = valor;
    novo->prox = NULL;

    pthread_mutex_lock(&lista->mutex);
    novo->prox = lista->inicio;
    lista->inicio = novo;
    pthread_mutex_unlock(&lista->mutex);
}

void* tarefa(void* arg) {
    long id = (long)arg;
    for (int i = 0; i < NUM_INSERCOES; i++) {
        int valor = rand() % 100 + 1;
        int index = rand() % NUM_LISTAS;
        inserir(&listas[index], valor);
    }
    printf("Thread %ld finalizou inserções.\n", id);
    return NULL;
}

int contar_elementos(Node* no) {
    int count = 0;
    while (no != NULL) {
        count++;
        no = no->prox;
    }
    return count;
}

int main() {
    srand(time(NULL));

    printf("Digite o número de listas: ");
    scanf("%d", &NUM_LISTAS);

    listas = (ListaEncadeada*)malloc(NUM_LISTAS * sizeof(ListaEncadeada));
    for (int i = 0; i < NUM_LISTAS; i++) {
        listas[i].inicio = NULL;
        pthread_mutex_init(&listas[i].mutex, NULL);
    }

    pthread_t threads[NUM_THREADS];
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, tarefa, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_LISTAS; i++) {
        int qtd = contar_elementos(listas[i].inicio);
        printf("Lista %d tem %d elementos.\n", i, qtd);
    }

    // Libera memória e destrói mutexes
    for (int i = 0; i < NUM_LISTAS; i++) {
        Node* atual = listas[i].inicio;
        while (atual != NULL) {
            Node* tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
        pthread_mutex_destroy(&listas[i].mutex);
    }
    free(listas);

    return 0;
}
