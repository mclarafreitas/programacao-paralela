#include <stdio.h>
#include <stdbool.h>
#include <omp.h>

// Função para verificar se um número é primo
bool ehPrimo(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

int main() {
    int n, contador = 0;
    double inicio, fim;

    printf("Digite o valor de n: ");
    scanf("%d", &n);

    inicio = omp_get_wtime();

    // Paralelização sem proteger a variável contador
    #pragma omp parallel for
    for (int i = 2; i <= n; i++) {
        if (ehPrimo(i)) {
            contador++; // <- condição de corrida aqui!
        }
    }

    fim = omp_get_wtime();

    printf("PARALELO SEM PROTEÇÃO:\n");
    printf("Quantidade de números primos entre 2 e %d (possivelmente incorreto): %d\n", n, contador);
    printf("Tempo de execução: %.6f segundos\n", fim - inicio);

    return 0;
}
