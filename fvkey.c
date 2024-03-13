# #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEDICINES 5

struct MedicineStack {
    char medicines[MAX_MEDICINES][50];
    int top;
};

// Function to initialize the stack
void initializeStack(struct MedicineStack *stack) {
    stack->top = -1;
}

// Function to push a medicine into the stack
void push(struct MedicineStack *stack, const char *medicine) {
    if (stack->top == MAX_MEDICINES - 1) {
        printf("Stack overflow! Cannot add more medicines.\n");
    } else {
        strcpy(stack->medicines[++stack->top], medicine);
    }
}

// Function to display medicine prescription
void displayMedicinePrescription(struct MedicineStack *stack) {
    printf("Medicine Prescription :\n");
    for (int i = stack->top; i >= 0; i--) {
        printf("Take Medicine #%d: %s\n", stack->top - i + 1, stack->medicines[i]);
    }
}

// Function to check if the user want to continue input medicines or no
int isContinue() {
    char response[10];
    printf("Do you want to continue? (yes/no): ");
    scanf("%s", response);
    return (strcmp(response, "yes") == 0 || strcmp(response, "Yes") == 0 || strcmp(response, "YES") == 0);
}

int main() {
    printf("key Hospital\n");
    printf("==============\n");

    while (1) {
        struct MedicineStack medicineStack;
        initializeStack(&medicineStack);

        for (int i = 0; i < MAX_MEDICINES; i++) {
            char medicine[50];
            printf("Enter medicine name [minimum %d medicines] ('done' to finish): ", MAX_MEDICINES);
            scanf("%s", medicine);
            if (strcmp(medicine, "done") == 0) {
                printf("\n");
                break;
            }

            push(&medicineStack, medicine);
            printf("Medicine %s added to the prescription\n", medicine);
        }

        // Display the medicine prescription
        displayMedicinePrescription(&medicineStack);

        // Check if the user wants to continue or no
        if (!isContinue()) {
            printf("\nThank you");
            break;
        }
    }

    return 0;
}
