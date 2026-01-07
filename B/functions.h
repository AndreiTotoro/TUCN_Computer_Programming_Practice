#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define SQUARE_MATRIX_SIZE 5

typedef struct Coordinate {
    int x;
    int y;
} Coordinate;

void read_and_validate_key_mat(char* const filepath, char ***mat);

void strip_newline(char *buffer);

void read_and_validate_word_from_keyboard(char **word_from_keyboard);

void read_text_to_decrypt(char* const text_to_decrypt_filepath, char** text_to_decrypt);

void obtain_and_store_coordinates(char **mat, char *const word_from_keyboard, Coordinate **coordinates);

void get_code_in_coordinates(Coordinate *coordinates, char *const word_from_keyboard, Coordinate **code_in_coordinates);

void print_decrypted_word(char **mat, Coordinate *code_in_coordinates, char const *word_from_keyboard);

void decrypt_and_write_encrypted_text(char **key_mat, char *text_to_decrypt, char *const filepath);

void clean_up(char **key_mat, char *word_from_keyboard, char *text_to_decrypt, Coordinate *coordinates, Coordinate *code_in_coordinates);

#endif