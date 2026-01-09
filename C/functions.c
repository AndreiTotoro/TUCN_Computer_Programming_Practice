#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void strip_newline(char *buffer){
    int buff_len = strlen(buffer);
    if (buffer[buff_len - 1] == '\n'){
        buffer[buff_len - 1] = '\0';
    }
}

void read_input(char *const path_to_mat1, char *const path_to_mat2, float ***mat1, char ***mat2, int *nr_of_rows, int *nr_of_columns)
{
    FILE *mat1_file;
    FILE *mat2_file;

    scanf("%d %d", nr_of_rows, nr_of_columns);

    mat1_file = fopen(path_to_mat1, "r");
    if(mat1_file == NULL){
        perror("Failed to open file");
        exit(1);
    }

    *mat1 = malloc(sizeof(float *) * *nr_of_rows);
    if(*mat1 == NULL){
        perror("Failed to allocate memory");
        exit(1);
    }

    for(int i = 0; i < *nr_of_rows; i++){
        char buffer[256];
        if(fgets(buffer, sizeof(buffer), mat1_file) == NULL){
            perror("Failed to read from file");
            exit(1);
        }
        (*mat1)[i] = malloc(sizeof(float) * *nr_of_columns);
        if((*mat1)[i] == NULL){
            perror("Failed to allocate memory");
            exit(1);
        }

        strip_newline(buffer);

        char *token = strtok(buffer, " ");

        int j = 0;
        while(token != NULL){
            (*mat1)[i][j] = strtof(token, NULL);
            token = strtok(NULL, " ");
            j++;
        }

    }

    fclose(mat1_file);

    mat2_file = fopen(path_to_mat2, "r");
    if(mat2_file == NULL){
        perror("Failed to open file");
        exit(1);
    }

    *mat2 = malloc(sizeof(char *) * *nr_of_rows);
    if(*mat2 == NULL){
        perror("Failed to allocate memory");
        exit(1);
    }

    for(int i = 0; i < *nr_of_rows; i++){
        char buffer[256];
        if(fgets(buffer, sizeof(buffer), mat2_file) == NULL){
            perror("Failed to read from file");
            exit(1);
        }
        (*mat2)[i] = malloc(sizeof(char) * *nr_of_columns);
        if((*mat2)[i] == NULL){
            perror("Failed to allocate memory");
            exit(1);
        }

        strip_newline(buffer);

        char *token = strtok(buffer, " ");

        int j = 0;
        while(token != NULL){
            (*mat2)[i][j] = *token;
            token = strtok(NULL, " ");
            j++;
        }

    }

    fclose(mat2_file);
    
}

void get_price_values_from_mat1(float **mat1, PriceValue **price_values, int nr_of_rows, int nr_of_columns, int *price_value_count){
    *price_value_count = 0;
    *price_values = NULL;

    for(int i = 0; i < nr_of_rows; i++){
        for(int j = 0; j < nr_of_columns; j++){
            if(mat1[i][j] - (int)mat1[i][j] > 0){
                (*price_value_count)++;
                *price_values = realloc(*price_values, (sizeof(PriceValue) * *price_value_count));
                if(*price_values == NULL){
                    perror("Failed to reallocate memory");
                    exit(1);
                }
                (*price_values)[*price_value_count - 1].price = mat1[i][j];
                (*price_values)[*price_value_count - 1].i = i;
                (*price_values)[*price_value_count - 1].j = j;
            }
        }
    }
}

void get_store_items_from_mat2(char **mat2, StoreItem **store_items, PriceValue *price_values, int nr_of_columns, int nr_of_rows, int price_value_count, int *store_item_count){
    *store_items = malloc(price_value_count * sizeof(StoreItem));
    if(*store_items == NULL){
        perror("Failed to allocate space");
        exit(1);
    }

    for(int k = 0; k < price_value_count; k++){
        int i = price_values[k].i;
        int j = price_values[k].j;
        float price = price_values[k].price;
        (*store_items)[k].price = price;
        if(i == 0){
            (*store_items)[k].quantity = (j > 0) ? (mat2[nr_of_rows - 1][j - 1] - '0') : 0;
        } else {
            (*store_items)[k].quantity = mat2[i - 1][j] - '0';
        }
        char *name = malloc(sizeof(char) * (nr_of_rows + 1));

        int count = 0;
        for(int l = i; l < nr_of_rows; l++){
            if(isalpha(mat2[l][j])){
                name[count] = mat2[l][j];
                count++;
            } else {
                break;
            }
        }
        name[count] = '\0';

        *store_item_count = price_value_count;
        (*store_items)[k].item_name = name;
    }
}

int compare_by_quantity(const void *a, const void *b){
    StoreItem *sa = (StoreItem *)a;
    StoreItem *sb = (StoreItem *)b;
    
    if (sb->quantity > sa->quantity) return 1;
    if (sb->quantity < sa->quantity) return -1;
    
    return strcmp(sa->item_name, sb->item_name);
}

void display_store_items_by_quantity(StoreItem *store_items, int store_item_count){
    qsort(store_items, store_item_count, sizeof(StoreItem), compare_by_quantity);
    for(int i = 0; i < store_item_count; i++){
        printf("%s %d %.1f\n", store_items[i].item_name, store_items[i].quantity, store_items[i].price);
    }
}

void clean_up(float **mat1, char **mat2, PriceValue *price_values, StoreItem *store_items, int nr_of_rows, int nr_of_store_items){
    free(price_values);
    for(int i = 0; i < nr_of_store_items; i++){
        free(store_items[i].item_name);
    }
    free(store_items);
    for(int i = 0; i < nr_of_rows; i++){
        free(mat1[i]);
        free(mat2[i]);
    }
}
