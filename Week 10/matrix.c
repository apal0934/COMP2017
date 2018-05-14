#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define WIDTH 512
#define IDX(x, y) ((y) * WIDTH + (x))

struct args { 
	const float * a;
	const float * b;
	size_t y;
};

 

/**
* Returns the matrix multiplication of a and b.
*/
float * multiply(const float * a, const float * b) {

	float * result = calloc(WIDTH * WIDTH, sizeof(float));

	for (size_t y = 0; y < WIDTH; y++) {
		for (size_t k = 0; k < WIDTH; k++) {
		
	
	}

	return result;
}

void worker (*args) {
	for (size_t k = 0; k < WIDTH; k++) {
		for (size_t x = 0; x < WIDTH; x++) {
			result[IDX(x, y)] += a[IDX(k, y)] * b[IDX(x, k)];
		}
	}
}

/**
* Returns a Hadamard matrix, if H is Hadamard matrix, then
* HH^T = nI, where I is the identity matrix and n is the width.
* Easy to verify that the matrix multiplication was done correctly.
*
* Sylvester’s construction implemented here only works
* for matrices that have width that is a power of 2.
*
* Note that this construction produces matrices that are symmetric.
*/
float * hadamard(void) {

	// Ensure the width is a power of 2
	assert(((WIDTH - 1) & WIDTH) == 0);

	size_t w = WIDTH;
	size_t quad_size = 1;

	float * result = malloc(WIDTH * WIDTH * sizeof(float));

	result[0] = 1;
	while ((w >>= 1) != 0) {
		// Duplicate the upper left quadrant into the other three quadrants
		for (size_t y = 0; y < quad_size; ++y) {
			for (size_t x = 0; x < quad_size; ++x) {
				const float v = result[IDX(x, y)];
				result[IDX(x + quad_size, y)] = v;
				result[IDX(x, y + quad_size)] = v;
				result[IDX(x + quad_size, y + quad_size)] = -v;
			}
		}
		quad_size *= 2;
	}
	return result;
}

// Displays a matrix.
void display(const float * matrix) {
	for (size_t y = 0; y < WIDTH; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			printf("%6.2f ", matrix[IDX(x, y)]);
		}
		printf("\n");
	}
}

int main(void) {

	// Construct the matrices
	float * a = hadamard();
	float * b = hadamard();	

	// Compute the result
	float * r = multiply(a, b);

	// Verify the result
	for (size_t y = 0; y < WIDTH; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			assert(x == y ? r[IDX(x, y)] == WIDTH : r[IDX(x, y)] == 0);
		}
	}

	puts("done");
	free(a);
	free(b);
	free(r);

	return 0;
}


