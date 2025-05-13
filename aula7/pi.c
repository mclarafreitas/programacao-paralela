#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    long num_pontos = 1000000;
    long dentro_do_circulo = 0;

    // Sementes independentes por thread
    unsigned int seeds[omp_get_max_threads()];
    for (int i = 0; i < omp_get_max_threads(); i++) {
        seeds[i] = time(NULL) + i * 1337;
    }

    #pragma omp parallel default(none) shared(num_pontos, seeds, dentro_do_circulo) 
    {
        int tid = omp_get_thread_num();                    // private por padrão
        unsigned int seed = seeds[tid];                    // firstprivate-like
        double x, y;                                       // private por padrão

        #pragma omp for
        for (long i = 0; i < num_pontos; i++) {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX;

            if (x * x + y * y <= 1.0) {
                #pragma omp critical
                dentro_do_circulo++;
            }
        }
    }

    double pi = 4.0 * dentro_do_circulo / num_pontos;
    printf("Estimativa de pi (com critical): %.6f\n", pi);

    return 0;
}
