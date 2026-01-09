#include "functions.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Products populate_products(){
    int quantity;
    float price;
    int id = 0;
    Products products;
    products.data = NULL;

    puts("Input  some pairs of price and quantity ");
    scanf("%f %d", &price, &quantity);
    while(price || quantity){
        if(price > 0 && quantity > 0){
            products.data = realloc(products.data, sizeof(Product) * (id + 1));
            if(products.data == NULL){
                perror("Failed to reallocate memory");
                exit(1);
            }
            products.data[id].id = id;
            products.data[id].price = price;
            products.data[id].quantity = quantity;
            id++;
        }
        scanf("%f %d", &price, &quantity);
    }

    printf("%d products were validated\n", id);
    products.nr_of_products = id;

    return products;
}

float initialize_users_available_money(){
    float money = 0;
    
    while(money <= 0){
        puts("Please introduce the available amount of money: ");
        scanf("%f", &money);
        if(money <= 0){
            puts("The amount must be a positive number!");
        }
    }

    return money;
}

void display_available_products(Products const *products){
    puts("The products you can buy are:");
    for(int i = 0; i < products->nr_of_products; i++){
        printf("%d - price = %.1f, quantity = %d\n", products->data[i].id, products->data[i].price, products->data[i].quantity);
    }
}

void remove_at(Product **products_data, int size, int id){
    if(size - 1 == 0){
        return;
    }
    for(int i = id; i < size - 1; i++){
        (*products_data)[i] = (*products_data)[i + 1];
    }
    *products_data = realloc(*products_data, sizeof(Product) * (size - 1));
    if(*products_data == NULL){
        perror("Failed to reallocate memory");
        exit(1);
    }
}

void buy_product(float *available_money, Products *products){

    int id;
    puts("Please select the id of the product ypu want to buy:");
    scanf("%d", &id);

    if(id < 0){
        puts("The product does not exist!");
        return ;
    }
    for(int i = 0; i < products->nr_of_products; i++){
        if(id == products->data[i].id){
            if(*available_money >= products->data[i].price){
                *available_money -= products->data[i].price;
                products->data[i].quantity--;

                printf("You have successfully bought product %d with price %.1f\n", id, products->data[i].price);
                if(*available_money > 0){
                    printf("Amount of money left is %.1f\n", *available_money);
                }
                
                if(products->data[i].quantity == 0){
                    remove_at(&products->data, products->nr_of_products, i);
                    products->nr_of_products--;
                }

            } 

            else{
                puts("Not enough money available to buy this product!");
            }

            return;
        }
    }
    puts("The product does not exist!");
    return ;
}

float get_cheapest_product_price(Products *products){
    float min = 9999999;
    for(int i = 0; i < products->nr_of_products; i++){
        if(products->data[i].price < min){
            min = products->data[i].price;
        }
    }
    return min;
}

void display_final_message_and_clean_up(Products *products){
    puts("You don't have enough money to buy something else!");
    free(products->data);
}