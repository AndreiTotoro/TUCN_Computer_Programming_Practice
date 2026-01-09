#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct PriceValue{
    float price;
    int i;
    int j;
}PriceValue;

typedef struct StoreItem{
    float price;
    char *item_name;
    int quantity;
}StoreItem;

//Will read both the input from the user (the size of matrix) and the two matrixes from thefile
void read_input(char *const path_to_mat1, char *const path_to_mat2, float ***mat1, char ***mat2, int *nr_of_rows, int *nr_of_columns);

//Will strip the newline character of any string
void strip_newline(char *buffer);

//Will get all the floating point values from mat1 and storethem along with their coordinates in price_values
void get_price_values_from_mat1(float **mat1, PriceValue **price_values, int nr_of_rows, int nr_of_columns, int *price_value_count);

//Will create all store items and store them inside store_items based on the data from price_values and mat2
void get_store_items_from_mat2(char **mat2, StoreItem **store_items, PriceValue *price_values, int nr_of_column, int nr_of_rows, int price_value_count, int *store_item_count);

//Will display the store item data in the requested format
void display_store_items_by_quantity(StoreItem *store_items, int store_item_count);

//Will free up all the memory that was used to execute the program
void clean_up(float **mat1, char **mat2, PriceValue *price_values, StoreItem *store_items, int nr_of_rows, int nr_of_store_items);

#endif