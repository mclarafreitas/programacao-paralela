#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct Node {
    int valor;
    struct Node* proximo;
} Node;

typedef struct {
    Node* cabeca;
    pthread_mutex_t mutex;
} ListaEncadeada;

ListaEncadeada* listas;
int num_listas;
int num_threads = 4;
int num_insercoes = 1000;

void inserir_na_lista(ListaEncadeada* lista, int valor) {
    Node* novo = malloc(sizeof(Node));
    novo->valor = valor;
    novo->proximo = NULL;

    pthread_mutex_lock(&lista->mutex);
    novo->proximo = lista->cabeca;
    lista->cabeca = novo;
    pthread_mutex_unlock(&lista->mutex);
}

void* tarefa_insercao(void* arg) {
    for (int i = 0; i < num_insercoes; i++) {
        int valor = rand() % 1000;
        int indice = rand() % num_listas;
        inserir_na_lista(&listas[indice], valor);
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    printf("Digite o número de listas: ");
    scanf("%d", &num_listas);

    listas = malloc(num_listas * sizeof(ListaEncadeada));
    for (int i = 0; i < num_listas; i++) {
        listas[i].cabeca = NULL;
        pthread_mutex_init(&listas[i].mutex, NULL);
    }

    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; i++)
        pthread_create(&threads[i], NULL, tarefa_insercao, NULL);

    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    printf("Inserções concluídas nas %d listas.\n", num_listas);

    for (int i = 0; i < num_listas; i++)
        pthread_mutex_destroy(&listas[i].mutex);
    free(listas);
    return 0;
}
