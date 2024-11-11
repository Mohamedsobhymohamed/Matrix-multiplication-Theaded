#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Global variables for matrices and dimensions
int **matrix1, **matrix2, **result1, **result2;
int r1, c1, r2, c2;

// Structure to pass parameters for element-wise computation in Variation 1
typedef struct {
    int row;
    int col;
} ElementParams;

// Function to read matrices from the input file
void read_matrices(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {  
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Read dimensions and elements of the first matrix
    fscanf(file, "%d %d", &r1, &c1);
    matrix1 = malloc(r1 * sizeof(int *));
    for (int i = 0; i < r1; i++) {
        matrix1[i] = malloc(c1 * sizeof(int));
        for (int j = 0; j < c1; j++) {
            fscanf(file, "%d", &matrix1[i][j]);
        }
    }

    // Read dimensions and elements of the second matrix
    fscanf(file, "%d %d", &r2, &c2);
    matrix2 = malloc(r2 * sizeof(int *));
    for (int i = 0; i < r2; i++) {
        matrix2[i] = malloc(c2 * sizeof(int));
        for (int j = 0; j < c2; j++) {
            fscanf(file, "%d", &matrix2[i][j]);
        }
    }

    fclose(file);
}

// Function to compute a single element in result1 matrix for Variation 1
void *compute_element(void *params) {
    ElementParams *p = (ElementParams *)params;
    int row = p->row;
    int col = p->col;

    // Calculate the element at position (row, col)
    result1[row][col] = 0;
    for (int k = 0; k < c1; k++) {
        result1[row][col] += matrix1[row][k] * matrix2[k][col];
    }

    free(p);  // Free dynamically allocated parameters
    pthread_exit(0);  
}

// Function to compute an entire row in result2 matrix for Variation 2
void *compute_row(void *param) {
    int row = *(int *)param;
    
    // Calculate each element in the row
    for (int col = 0; col < c2; col++) {
        result2[row][col] = 0;
        for (int k = 0; k < c1; k++) {
            result2[row][col] += matrix1[row][k] * matrix2[k][col];
        }
    }

    free(param);  // Free dynamically allocated row index
    pthread_exit(0);  
}

// Function to free memory allocated for matrices
void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    read_matrices("matrices.txt");

    // Allocate memory for result matrices
    result1 = malloc(r1 * sizeof(int *));
    result2 = malloc(r1 * sizeof(int *));
    for (int i = 0; i < r1; i++) {
        result1[i] = malloc(c2 * sizeof(int));
        result2[i] = malloc(c2 * sizeof(int));
    }

    // VARIATION 1: Compute each element in a separate thread
    clock_t start = clock();  // Start timer for Variation 1
    pthread_t threads[r1 * c2];
    int thread_count = 0;

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            ElementParams *params = malloc(sizeof(ElementParams));
            params->row = i;
            params->col = j;
            pthread_create(&threads[thread_count++], NULL, compute_element, params);
        }
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);  // Wait for all threads to finish
    }
    clock_t end = clock();  // End timer for Variation 1
    double time1 = (double)(end - start) / CLOCKS_PER_SEC;  // Calculate elapsed time

    // Print result for Variation 1
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", result1[i][j]);
        }
        printf("\n");
    }
    printf("END1 %.6f\n", time1);

    // VARIATION 2: Compute each row in a separate thread
    start = clock();  // Start timer for Variation 2
    pthread_t row_threads[r1];

    for (int i = 0; i < r1; i++) {
        int *row = malloc(sizeof(int));
        *row = i;
        pthread_create(&row_threads[i], NULL, compute_row, row);
    }

    for (int i = 0; i < r1; i++) {
        pthread_join(row_threads[i], NULL);  // Wait for each row's thread to finish
    }
    end = clock();  // End timer for Variation 2
    double time2 = (double)(end - start) / CLOCKS_PER_SEC;  // Calculate elapsed time

    // Print result for Variation 2
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            printf("%d ", result2[i][j]);
        }
        printf("\n");
    }
    printf("END2 %.6f\n", time2);

    // Free memory for all matrices
    free_matrix(matrix1, r1);
    free_matrix(matrix2, r2);
    free_matrix(result1, r1);
    free_matrix(result2, r1);

    return 0;
}

