#include <stdio.h>
#include <stdlib.h>

void sort_array(int values[], int total_number) {
    for (int i = 0; i < total_number - 1; i++) {
        for (int j = 0; j < total_number - i - 1; j++) {
            if (values[j] > values[j + 1]) {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }
}

double calculate_mean(const int values[], int total_number) {
    long long sum = 0;
    for (int i = 0; i < total_number; i++) {
        sum += values[i];
    }
    return (double) sum / total_number;
}

double calculate_median(const int values[], int total_number) {
    int *sorted = malloc((size_t)total_number * sizeof(int));
    if (sorted == NULL) {
        printf("Memory allocation failed.\n");
        exit(0);
    }

    for (int i = 0; i < total_number; i++) sorted[i] = values[i];
    sort_array(sorted, total_number);

    double result;
    if (total_number % 2 == 1) {
        result = sorted[total_number / 2];
    } else {
        result = ((double)sorted[total_number / 2 - 1] + sorted[total_number / 2]) / 2.0;
    }
    free(sorted);
    return result;
}

void calculate_mode(const int values[], int total_number) {
    int *sorted = malloc((size_t)total_number * sizeof(int));
    if (sorted == NULL) {
        printf("Memory allocation failed.\n");
        exit(0);
    }
    for (int i = 0; i < total_number; i++) sorted[i] = values[i];
    sort_array(sorted, total_number);

    int max_count = 1, count = 1;
    for (int i = 1; i < total_number; i++) {
        if (sorted[i] == sorted[i - 1]) count++;
        else {
            if (count > max_count) max_count = count;
            count = 1;
        }
    }
    if (count > max_count) max_count = count;

    if (max_count == 1) {
        printf("Mode: No mode (all values occur once)\n");
    } else {
        printf("Mode: ");
        int first = 1;
        count = 1;
        for (int i = 1; i <= total_number; i++) {
            if (i < total_number && sorted[i] == sorted[i - 1]) {
                count++;
            } else {
                if (count == max_count) {
                    if (!first) printf(", ");
                    printf("%d", sorted[i - 1]);
                    first = 0;
                }
                count = 1;
            }
        }
        printf("\n");
    }
    free(sorted);
}

int main(void) {
    int total_number;
    printf("Enter the number of integers: ");
    if (scanf("%d", &total_number) != 1 || total_number <= 0) {
        printf("Please enter a positive number.\n");
        return 0;
    }

    int *values = malloc((size_t)total_number * sizeof(int));
    if (values == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("Enter %d integers separated by spaces: ", total_number);
    for (int i = 0; i < total_number; i++) {
        if (scanf("%d", &values[i]) != 1) {
            printf("Invalid input: integers only.\n");
            free(values);
            return 0;
        }
    }

    printf("Mean: %.2f\n", calculate_mean(values, total_number));
    printf("Median: %.2f\n", calculate_median(values, total_number));
    calculate_mode(values, total_number);
    free(values);
    return 0;
}
