#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define SQUARE_MATRIX_SIZE 5
#define WORD_LEN 100

typedef struct Coordinate {
    int x;
    int y;
} Coordinate;

//Will read and maalidate the key matrix from the file, making sure it only contains uppercase characters
void read_and_validate_key_mat(char* const filepath, char ***mat);

//Will remove the (eventual)trailing new-line of any string
void strip_newline(char *buffer);

//Will prompt the user to input a word and check that it only contains letters
void read_and_validate_word_from_keyboard(char **word_from_keyboard);

//Will read the text that is supposed to be decrypted from the file
void read_text_to_decrypt(char* const text_to_decrypt_filepath, char** text_to_decrypt);

//Will obtain and store the coordinates of the cyper by searching for the words letters in the matrix
void obtain_and_store_coordinates(char **mat, char *const word_from_keyboard, Coordinate **coordinates);

//Will transform the coodinates as if they were being read on two rows
void get_code_in_coordinates(Coordinate *coordinates, char *const word_from_keyboard, Coordinate **code_in_coordinates);

//Will print the decrypted word by applying the code in coordinates to the matrix
void print_decrypted_word(char **mat, Coordinate *code_in_coordinates, char const *word_from_keyboard);

//Will decrypt a whole line from a file using the same tehnique
void decrypt_and_write_encrypted_text(char **key_mat, char *text_to_decrypt, char *const filepath);

//Will free up all the memory
void clean_up(char **key_mat, char *word_from_keyboard, char *text_to_decrypt, Coordinate *coordinates, Coordinate *code_in_coordinates);

#endif