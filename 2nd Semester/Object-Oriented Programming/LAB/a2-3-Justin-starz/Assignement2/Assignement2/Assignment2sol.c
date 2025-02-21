#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a medicine
typedef struct {
    char name[50];
    float concentration;
    int quantity;
    float price;
} Medicine;

// Dynamic array to store medicines
Medicine* medicines = NULL;
int number_of_medicines = 0;

// for adding a new medicine to the list of 
// medicines or updating the quantity of an existing 
// medicine if it already exists.

void addOrUpdateMedicine() {
    char name[50];
    float concentration, price;
    int quantity;

    printf("Enter the medicine name: ");
    scanf("%s", name);
    printf("Enter the concentration: ");
    scanf("%f", &concentration);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    printf("Enter the price: ");
    scanf("%f", &price);

    // For Checking if the medicine already exists
    int i;
    for (i = 0; i < number_of_medicines; ++i) {
        if (strcmp(medicines[i].name, name) == 0 && medicines[i].concentration == concentration) {
            // Medicine found, update its quantity
            medicines[i].price += price;
            medicines[i].quantity += quantity;
            return;
        }
    }

    //Medicine not found
    // allocates memory for a new medicine by using realloc to 
    //increase the size of the medicines array by one element.

    medicines = realloc(medicines, (number_of_medicines + 1) * sizeof(Medicine));

    if (medicines == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    //For Adding the new medicine
    strcpy(medicines[number_of_medicines].name, name);
    medicines[number_of_medicines].concentration = concentration;
    medicines[number_of_medicines].quantity = quantity;
    medicines[number_of_medicines].price = price;
    number_of_medicines++;
}

// for deleting a medicine from the list of medicines 
// based on the provided name and concentration.
void deleteMedicine() {
    char name[50];
    float concentration;

    printf("Enter the medicine name to delete: ");
    scanf("%s", name);
    printf("Enter the concentration: ");
    scanf("%f", &concentration);

    int i, found = 0;
    for (i = 0; i < number_of_medicines; ++i) {
        if (strcmp(medicines[i].name, name) == 0 && medicines[i].concentration == concentration) {
            // Medicine found, delete it by 
            // shifting remaining medicines
            found = 1;
            for (int j = i; j < number_of_medicines - 1; ++j) {
                medicines[j] = medicines[j + 1];
            }
            number_of_medicines--;
            medicines = realloc(medicines, number_of_medicines * sizeof(Medicine));
            break;
        }
    }
    if (!found) {
        printf("Medicine not found!\n");
    }
}

// Function to search for medicines containing a given string
void searchMedicine() {
    char keyword[50];
    printf("Enter the keyword the to search : ");
    scanf("%s", &keyword);

    printf("Matching Medicines:\n");
    for (int i = 0; i < number_of_medicines; ++i) {
        if (strlen(keyword) == 0 || strstr(medicines[i].name, keyword) != NULL) {
            printf("Name: %s, Concentration: %.2f, Quantity: %d, Price: %.2f\n",
                medicines[i].name, medicines[i].concentration, medicines[i].quantity, medicines[i].price);
        }
    }
}

void displayMedicines() {
    printf("All Medicines:\n");
    for (int i = 0; i < number_of_medicines; ++i) {
        printf("Name: %s, Concentration: %.2f, Quantity: %d, Price: %.2f\n",
            medicines[i].name, medicines[i].concentration, medicines[i].quantity, medicines[i].price);
    }
}

int main() {
    int choice;

    do {
        printf("\n1. Add or update a medicine\n");
        printf("2. Delete a medicine\n");
        printf("3. Search medicines\n");
        printf("4. Display all medicines\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addOrUpdateMedicine();
            break;
        case 2:
            deleteMedicine();
            break;
        case 3:
            searchMedicine();
            break;

        case 4:
            displayMedicines();
            break;
        case 5:
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 5);

    // Free allocated memory
    free(medicines);
    return 0;
}