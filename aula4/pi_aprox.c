#include <stdio.h>
#include <math.h>
#include <time.h>

#define REAL_PI 3.14159265358979323846

// Função para calcular pi usando a série de Gregory-Leibniz
double calcular_pi(int iteracoes) {
    double pi_aprox = 0.0;
    for (int i = 0; i < iteracoes; i++) {
        double termo = (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
        pi_aprox += termo;
    }
    return pi_aprox * 4.0;
}

int main() {
    int iteracoes[] = {10, 100, 1000, 10000, 100000, 1000000}; 
    int tamanho = sizeof(iteracoes) / sizeof(iteracoes[0]);

    printf("Iteracoes\tPi Aproximado\tErro Absoluto\tTempo (ms)\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < tamanho; i++) {
        clock_t inicio = clock();
        double pi_aprox = calcular_pi(iteracoes[i]);
        clock_t fim = clock();

        double erro = fabs(REAL_PI - pi_aprox);
        double tempo_ms = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;

        printf("%d\t\t%.10f\t%.10f\t%.3f\n", iteracoes[i], pi_aprox, erro, tempo_ms);
    }

    return 0;
}
