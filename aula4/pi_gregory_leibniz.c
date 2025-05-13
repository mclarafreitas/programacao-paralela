#include <stdio.h>
#include <math.h>
#include <time.h>

#define REAL_PI 3.14159265358979323846

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

    FILE *arquivo = fopen("resultados.dat", "w"); // Abre um arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "# Iteracoes Pi_Aproximado Erro_Absoluto Tempo_ms\n"); // Cabeçalho

    for (int i = 0; i < tamanho; i++) {
        clock_t inicio = clock();
        double pi_aprox = calcular_pi(iteracoes[i]);
        clock_t fim = clock();

        double erro = fabs(REAL_PI - pi_aprox);
        double tempo_ms = 1000.0 * (fim - inicio) / CLOCKS_PER_SEC;

        fprintf(arquivo, "%d %.10f %.10f %.3f\n", iteracoes[i], pi_aprox, erro, tempo_ms);
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Resultados salvos em 'resultados.dat'\n");
    return 0;
}
