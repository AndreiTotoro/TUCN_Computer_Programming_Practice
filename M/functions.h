#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Product{
    int id;
    int quantity;
    float price;
} Product;

typedef struct Products{
    int nr_of_products;
    Product *data;
} Products;

//Will populate the products by accepting price-quant input from the user until a 0 0 is met
Products populate_products();

//Will prompt the user to input their available money and returnit
float initialize_users_available_money();

//Will display avilable products from the store
void display_available_products(Products const *products);

//Will prompt the user to choose a product to buy and will check if the product exists and if the user can buy that product
void buy_product(float *available_money, Products *products);

//Will remove an element from the product data
void remove_at(Product **products_data, int size, int id);

//Will get the price of the cheapest product in the product data
float get_cheapest_product_price(Products *products);

//Will display the fact that the user can no longer buy products and will free up used memory
void display_final_message_and_clean_up(Products *products);


#endif