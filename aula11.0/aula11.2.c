// montecarlo_atomic.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    long total_pontos = 1e8;
    long acertos = 0;

    double inicio = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        long local_acertos = 0;

        #pragma omp for
        for (long i = 0; i < total_pontos; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) local_acertos++;
        }

        #pragma omp atomic
        acertos += local_acertos;
    }

    double pi = 4.0 * acertos / total_pontos;
    double tempo = omp_get_wtime() - inicio;

    printf("V2 (atomic): Pi = %.6f | Tempo = %.4f s\n", pi, tempo);
    return 0;
}
