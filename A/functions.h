#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define MAX_SIZE_OF_CODE 256
#define MAX_SIZE_OF_TEXT 512

typedef struct Header{
    int original_index;
    char letter;
} Header;

//Will clean the newline character if it exists from the string read from the file
void clean_newline(char *buffer);

//Will read the first line of the file and validate it against the code constraints
void read_secret_code(const char *filepath, char *place_to_read);

//Will read the second line of the file and validate & refactor it against the text constraints.
void read_text(const char *filepath, char *place_to_read);

//Used to validate the secret code
int validate_code(const char *code);

//Used to validate and refactor the read text
void validate_and_refactor_text(char *text);

//Will construct the code matrix, overlapping the secret code and the text in a matrix with the width of secret code
char **construct_code_matrix(char *secret_code, char *text, int *row_num, int *col_num);

//Will write the code matrix to the file
void write_code_matrix(const char *filepath, char **mat, int row_num, int col_num);

//Will retrieve the headers of the matrix and sort them alphabetically
Header *get_and_sort_mat_headers(char **mat, int col_num);

//Used as the sorting function for ordering the headers.
int compare_by_letter(const void *a, const void *b);

//Will append the encrypted text after the encryption algorithm is applied to the file
void write_encrypted_text(const char *filepath, char **mat, int row_num, int col_num, Header *headers);
#endif