#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 3940
#define MAX_COLS 8
#define MAX_STRING_LENGTH 50

struct Data {
    char values[MAX_ROWS][MAX_COLS][MAX_STRING_LENGTH];
    int numRows;
    int numCols;
};aaaaaa

void readCSV(const char *filename, struct Data *data) {
    FILE *file = fopen("file.csv", "r");
    if (file == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    char line[MAX_COLS * MAX_STRING_LENGTH];
    char *token;

    while (fgets(line, sizeof(line), file) != NULL) {
        int col = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            if (col >= MAX_COLS || data->numRows >= MAX_ROWS) {
                printf("Exceeded maximum number of columns or rows.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(data->values[data->numRows][col], token);
            col++;
            token = strtok(NULL, ",");
        }
        data->numCols = col > data->numCols ? col : data->numCols;
        data->numRows++;
    }

    fclose(file);
}

void displayRows(struct Data *data, int n) {
    for (int i = 0; i < n && i < data->numRows; i++) {
        for (int j = 0; j < data->numCols; j++) {
            printf("%s\t", data->values[i][j]);
        }
        printf("\n");
    }
}

void selectRow(struct Data *data, int column, const char *query) {
    int found = 0;
    for (int i = 0; i < data->numRows; i++) {
        if (strcmp(data->values[i][column], query) == 0) {
            for (int j = 0; j < data->numCols; j++) {
                printf("%s\t", data->values[i][j]);
            }
            printf("\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Not Found\n");
    }
}

void sortBy(struct Data *data, int column, int ascending) {
    for (int i = 0; i < data->numRows - 1; i++) {
        for (int j = 0; j < data->numRows - i - 1; j++) {
            if ((ascending && strcmp(data->values[j][column], data->values[j + 1][column]) > 0) ||
                (!ascending && strcmp(data->values[j][column], data->values[j + 1][column]) < 0)) {
                for (int k = 0; k < data->numCols; k++) {
                    char temp[MAX_STRING_LENGTH];
                    strcpy(temp, data->values[j][k]);
                    strcpy(data->values[j][k], data->values[j + 1][k]);
                    strcpy(data->values[j + 1][k], temp);
                }
            }
        }
    }

    displayRows(data, 10);
}

void exportCSV(struct Data *data, const char *filename) {
    FILE *file = fopen("file.csv", "w");
    if (file == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < data->numRows; i++) {
        for (int j = 0; j < data->numCols; j++) {
            fprintf(file, "%s", data->values[i][j]);
            if (j < data->numCols - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    struct Data data;
    data.numRows = 0;
    data.numCols = 0;

    readCSV("file.csv", &data);

    int k, numRows;
    do {
        printf("\nWhat do you want to do?\n");
        printf("1. Display data\n");
        printf("2. Search data\n");
        printf("3. Sort data\n");
        printf("4. Export data\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &k);

        switch (k) {
            case 1:
                printf("Number of rows: ");
                scanf("%d", &numRows);
                if (numRows > 0) {
                    displayRows(numRows +1);
                } else {
                    printf("Please enter a positive integer number of rows.\n");
                }
                break;
            case 2: {
                int column;
                char query[MAX_STRING_LENGTH];
                printf("Enter column for search: ");
                scanf("%d", &column);
                printf("Enter query value: ");
                scanf("%s", query);
                selectRow(&data, column, query);
                break;
            }
            case 3: {
                int column, ascending;
                printf("Enter column for sort: ");
                scanf("%d", &column);
                printf("Enter sorting order (1 for ascending, 0 for descending): ");
                scanf("%d", &ascending);
                sortBy(&data, column, ascending);
                break;
            }
            case 4: {
                char filename[MAX_STRING_LENGTH];
                printf("Enter filename for export: ");
                scanf("%s", filename);
                exportCSV(&data, filename);
                break;
            }
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (k != 5);

    return 0;
}
