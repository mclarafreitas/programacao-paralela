#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Função para testar se um número é primo
int is_prime(int n) {
    if(n < 2) return 0;        // Números menores que 2 não são primos
    if(n == 2) return 1;       // 2 é primo
    if(n % 2 == 0) return 0;   // Números pares maiores que 2 não são primos

    // Só precisamos testar até a raiz quadrada de n
    int limit = sqrt(n);
    for(int i = 3; i <= limit; i += 2) {
        if(n % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int max = 1000000; // valor máximo padrão
    if (argc > 1) {
        max = atoi(argv[1]); // permite definir o valor máximo via linha de comando
    }

    int count_seq = 0;
    double start_time = omp_get_wtime();

    // Versão sequencial
    for (int i = 2; i <= max; i++) {
        if (is_prime(i)) {
            count_seq++;
        }
    }
    double seq_time = omp_get_wtime() - start_time;

    int count_par = 0;
    start_time = omp_get_wtime();

    // Versão paralela utilizando OpenMP
    #pragma omp parallel for reduction(+:count_par)
    for (int i = 2; i <= max; i++) {
        if (is_prime(i)) {
            count_par++;
        }
    }
    double par_time = omp_get_wtime() - start_time;

    // Impressão dos resultados
    printf("Valor maximo: %d\n", max);
    printf("Quantidade de primos (sequencial): %d\n", count_seq);
    printf("Tempo de execucao (sequencial): %f segundos\n", seq_time);
    printf("Quantidade de primos (paralelo): %d\n", count_par);
    printf("Tempo de execucao (paralelo): %f segundos\n", par_time);

    return 0;
}
