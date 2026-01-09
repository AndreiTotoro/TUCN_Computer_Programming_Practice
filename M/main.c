#include "functions.h"

int main(){
    Products products = populate_products();
    float available_money = initialize_users_available_money();

    while(get_cheapest_product_price(&products) <= available_money){
        display_available_products(&products);
        buy_product(&available_money, &products);
    }

    display_final_message_and_clean_up(&products);
    
    return 0;
}