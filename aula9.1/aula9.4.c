// montecarlo_v4.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    long total_pontos = 1e8;
    int nthreads;

    double inicio = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        nthreads = omp_get_num_threads();
    }

    long *acertos_por_thread = calloc(nthreads, sizeof(long));

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        unsigned int seed = time(NULL) ^ tid;
        long local_acertos = 0;

        #pragma omp for
        for (long i = 0; i < total_pontos; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) local_acertos++;
        }

        acertos_por_thread[tid] = local_acertos;
    }

    long total_acertos = 0;
    for (int i = 0; i < nthreads; i++) {
        total_acertos += acertos_por_thread[i];
    }

    double pi = 4.0 * total_acertos / total_pontos;
    double tempo = omp_get_wtime() - inicio;
    free(acertos_por_thread);

    printf("V4 (rand_r + vetor): Pi = %.6f | Tempo = %.4f s\n", pi, tempo);
    return 0;
}
