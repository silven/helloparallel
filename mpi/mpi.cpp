#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <mpi.h>
#include <vector>
#include <unistd.h>

int main(int argc, char** argv) {
    std::vector<uint32_t> problem_sizes = {256, 384, 512, 640, 768, 1024};

    int rank, world_size;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &world_size);

    for(uint32_t N : problem_sizes) {
        if (N % world_size != 0) {
            printf("Matrix world_size not divisible by number of processors\n");
            MPI_Finalize();
            return -1;
        }

        auto A = (uint32_t*)malloc(sizeof(uint32_t)*(N*N));
        auto B = (uint32_t*)malloc(sizeof(uint32_t)*(N*N));
        auto C = (uint32_t*)malloc(sizeof(uint32_t)*(N*N));


        if (!A || !B || !C) {
            printf("Could not allocate enough memory!\n");
            return -1;
        }

        const uint32_t CHUNK = N / world_size;
        const uint32_t PER = N * CHUNK;

		auto start = std::chrono::high_resolution_clock::now();
        for(uint32_t i(0); i < CHUNK; ++i)
            for(uint32_t j(0); j < N; ++j) {
                C[i*N + j] = 0;
                for(uint32_t k(0); k < N; ++k) {
                    C[i*N + j] += A[i*N + k] * B[k*N + j];
                }
            }

		auto end = std::chrono::high_resolution_clock::now();
		
		auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
		if (rank == 0) {
			printf("Problem size: %d, time '%ld' ms\n", N, delta.count());
		}
        free(A);
        free(B);
        free(C);
	}
	
    MPI_Finalize();
    return 0;
}

