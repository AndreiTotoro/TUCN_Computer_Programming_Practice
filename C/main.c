#include "functions.h"

int main(){
    char *const path_to_mat1 = "mat1_input.txt";
    char *const path_to_mat2 = "mat2_input.txt";
    float **mat1;
    char **mat2;
    int nr_of_rows;
    int nr_of_columns;
    int price_value_count;
    int store_item_count;
    PriceValue *price_values;
    StoreItem *store_items;

    read_input(path_to_mat1, path_to_mat2, &mat1, &mat2, &nr_of_rows, &nr_of_columns);
    get_price_values_from_mat1(mat1, &price_values, nr_of_rows, nr_of_columns, &price_value_count);
    get_store_items_from_mat2(mat2, &store_items, price_values, nr_of_columns, nr_of_rows, price_value_count, &store_item_count);
    display_store_items_by_quantity(store_items, store_item_count);
    clean_up(mat1, mat2, price_values, store_items, nr_of_rows, store_item_count);

}