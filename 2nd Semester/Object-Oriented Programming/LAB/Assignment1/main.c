


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void readVector(int** vector, int* size);
void decomposePrimeFactors(int number);
void findLongestContiguousSubsequence(int* vector, int size);
void printArray(int* array, int start, int end);

// Function to read a vector of numbers from the console
void readVector(int** vector, int* size) {
    printf("Enter the size of the vector: ");
    scanf("%d", size);

    *vector = (int*)malloc(*size * sizeof(int));

    printf("Enter the elements of the vector:\n");
    for (int i = 0; i < *size; i++) {
        scanf("%d", &(*vector)[i]);
    }
}

// Function to decompose a given natural number into its prime factors
void decomposePrimeFactors(int number) {
    printf("Prime factors of %d are: ", number);
    for (int i = 2; i <= number; i++) {
        while (number % i == 0) {
            printf("%d ", i);
            number /= i;
        }
    }
    printf("\n");
}

// Function to find the longest contiguous subsequence
void findLongestContiguousSubsequence(int* vector, int size) {
    int start = 0, end = 0;
    int longestStart = 0, longestEnd = 0;
    int longestLength = 1;

    for (int i = 1; i < size; i++) {
        // Convert numbers to strings and sort their characters
        char str1[20], str2[20];
        sprintf(str1, "%d", vector[i - 1]);
        sprintf(str2, "%d", vector[i]);
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        if (len1 != len2 || strcmp(str1, str2) != 0) {
            start = i;
            end = i;
            continue;
        }

        // If the sorted strings are equal, extend the current subsequence
        end = i;
        if (end - start + 1 > longestLength) {
            longestStart = start;
            longestEnd = end;
            longestLength = end - start + 1;
        }
    }

    printf("Longest contiguous subsequence with same digits: ");
    printArray(vector, longestStart, longestEnd);
}

// Function to print elements of an array from start to end
void printArray(int* array, int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int* vector = NULL;
    int size;
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Read a vector of numbers\n");
        printf("2. Decompose a number into prime factors\n");
        printf("3. Find the longest contiguous subsequence with same digits\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            readVector(&vector, &size);
            break;
        case 2:
        {
            int number;
            printf("Enter a number to decompose into prime factors: ");
            scanf("%d", &number);
            decomposePrimeFactors(number);
        }
        break;
        case 3:
            if (vector == NULL) {
                printf("Error: Vector not initialized. Please read a vector first.\n");
            }
            else {
                findLongestContiguousSubsequence(vector, size);
            }
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    // Free dynamically allocated memory
    free(vector);

    return 0;
}










// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

