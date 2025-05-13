#include <stdio.h>
#include <stdbool.h>

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

    // Solicita o valor de n
    printf("Digite o valor de n: ");
    scanf("%d", &n);

    // Conta os primos entre 2 e n
    for (int i = 2; i <= n; i++) {
        if (ehPrimo(i)) {
            contador++;
        }
    }

    printf("Quantidade de números primos entre 2 e %d: %d\n", n, contador);
    return 0;
}
