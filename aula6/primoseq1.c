#include <stdio.h>
#include <stdbool.h>
#include <time.h>

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
    clock_t inicio, fim;

    printf("Digite o valor de n: ");
    scanf("%d", &n);

    inicio = clock();
    for (int i = 2; i <= n; i++) {
        if (ehPrimo(i)) {
            contador++;
        }
    }
    fim = clock();

    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("SEQUENCIAL:\n");
    printf("Quantidade de números primos entre 2 e %d: %d\n", n, contador);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);

    return 0;
}
