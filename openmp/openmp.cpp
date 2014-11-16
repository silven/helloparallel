#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <unistd.h>

int main(void) {
    std::vector<uint32_t> problem_sizes = {256, 384, 512, 640, 768, 1024};

    for(uint32_t N : problem_sizes) {

        auto A = (uint32_t*)malloc(sizeof(uint32_t)*(N*N));
        auto B = (uint32_t*)malloc(sizeof(uint32_t)*(N*N));
        auto C = (uint32_t*)malloc(sizeof(uint32_t)*(N*N));


        if (!A || !B || !C) {
            printf("Could not allocate enough memory!\n");
            return -1;
        }

		auto start = std::chrono::high_resolution_clock::now();
		#pragma omp parallel for
        for(uint32_t i = 0; i < N; ++i)
            for(uint32_t j(0); j < N; ++j) {
                C[i*N + j] = 0;
                for(uint32_t k(0); k < N; ++k) {
                    C[i*N + j] += A[i*N + k] * B[k*N + j];
                }
            }

		auto end = std::chrono::high_resolution_clock::now();
		auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);	
		printf("Problem size: %d, time '%ld' ms\n", N, delta.count());
        free(A);
        free(B);
        free(C);
	}
    return 0;
}

