#include "functions.h"

int main(){
    char **key_mat;
    char *word_from_keyboard;
    char *text_to_decrypt;
    char *const key_matrix_filepath = "key_matrix_b.txt";
    char *const text_to_decrypt_filepath = "text_to_decrypt_b.txt";
    char *const decrypted_text_filepath = "decrypted_text_b.txt";
    Coordinate *coordinates;
    Coordinate *code_in_coordinates;


    read_and_validate_key_mat(key_matrix_filepath, &key_mat);
    read_and_validate_word_from_keyboard(&word_from_keyboard);
    read_text_to_decrypt(text_to_decrypt_filepath, &text_to_decrypt);
    obtain_and_store_coordinates(key_mat, word_from_keyboard, &coordinates);
    get_code_in_coordinates(coordinates, word_from_keyboard, &code_in_coordinates);
    print_decrypted_word(key_mat, code_in_coordinates, word_from_keyboard);
    decrypt_and_write_encrypted_text(key_mat, text_to_decrypt, decrypted_text_filepath);
    clean_up(key_mat, word_from_keyboard, text_to_decrypt, coordinates, code_in_coordinates);

    return 0;
}

