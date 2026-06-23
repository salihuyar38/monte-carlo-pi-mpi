#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]) {
    long long total_points = 100000000;
    long long inside_circle = 0;

    if (argc > 1) {
        total_points = atoll(argv[1]);
    }

    srand(time(NULL));

    clock_t start = clock();

    for (long long i = 0; i < total_points; i++) {
        double x = 2.0 * rand() / (double)RAND_MAX - 1.0;
        double y = 2.0 * rand() / (double)RAND_MAX - 1.0;

        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }

    clock_t end = clock();

    double runtime = (double)(end - start) / CLOCKS_PER_SEC;
    double pi = 4.0 * inside_circle / (double)total_points;
    double error = fabs(M_PI - pi);

    printf("serial,1,%lld,%.10f,%.10f,%.10f,0,0\n",
           total_points, pi, error, runtime);

    return 0;
}