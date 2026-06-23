#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    long long total_points = 100000000;
    long long local_points;
    long long local_inside = 0;
    long long global_inside = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc > 1) {
        total_points = atoll(argv[1]);
    }

    local_points = total_points / size;

    if (rank == 0) {
        local_points += total_points % size;
    }

    srand(time(NULL) + rank * 1234);

    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    double compute_start = MPI_Wtime();

    for (long long i = 0; i < local_points; i++) {
        double x = 2.0 * rand() / (double)RAND_MAX - 1.0;
        double y = 2.0 * rand() / (double)RAND_MAX - 1.0;

        if (x * x + y * y <= 1.0) {
            local_inside++;
        }
    }

    double compute_end = MPI_Wtime();

    double reduce_start = MPI_Wtime();

    MPI_Reduce(
        &local_inside,
        &global_inside,
        1,
        MPI_LONG_LONG,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    double reduce_end = MPI_Wtime();
    double end = MPI_Wtime();

    if (rank == 0) {
        long long used_points = total_points;
        double pi = 4.0 * global_inside / (double)used_points;
        double error = fabs(M_PI - pi);

        printf("%d,%lld,%.10f,%.10f,%.10f,%.10f,%.10f\n",
               size,
               used_points,
               pi,
               error,
               end - start,
               compute_end - compute_start,
               reduce_end - reduce_start);
    }

    MPI_Finalize();
    return 0;
}