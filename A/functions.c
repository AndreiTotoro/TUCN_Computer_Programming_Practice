#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void clean_newline(char *buffer){
    int buff_len = strlen(buffer);
    if(buffer[buff_len - 1] == '\n'){
        buffer[buff_len  - 1] = '\0';
    }
}

int validate_code(const char *code){
    char letters[128] = {0};

    int code_len = strlen(code);

    for(int i = 0; i < code_len; i++){
        char letter = tolower(code[i]);
        letters[(int)letter]++;
    }

    char curr_letter = 'a';
    for(int i = 0; i < 26; i++){
        if(letters[curr_letter] > 1){
            return 0;
        }
        curr_letter++;
    }

    return 1;


}

void read_secret_code(const char *filepath, char *place_to_read){
    FILE *file;

    file = fopen(filepath, "r");
    
    if(file == NULL){
        perror("Could not open file");
        exit(1);
    }

    char code[MAX_SIZE_OF_CODE];

    if(fgets(code, sizeof(code), file) == NULL){
        perror("No code found");
        exit(0);
    }

    clean_newline(code);

    if(!validate_code(code)){
        perror("Invalid Code Provided");
        exit(1);
    }

    strcpy(place_to_read, code);

    fclose(file);

}

void read_text(const char *filepath, char *place_to_read){
    FILE *file;
    char text[MAX_SIZE_OF_TEXT];

    file = fopen(filepath, "r");

    if(file == NULL){
        perror("Could not open file");
        exit(1);
    }

    
    char buffer[256];
    

    if(fgets(buffer, sizeof(buffer), file) == NULL){
        perror("Could not find first line");
        exit(1);
    }

    if(fgets(text, sizeof(text), file) == NULL){
        perror("No text found");
        exit(1);
    }

    clean_newline(text);

    validate_and_refactor_text(text);

    strcpy(place_to_read, text);
    
}

void validate_and_refactor_text(char *text){
    int text_len = strlen(text);
    int j = 0;

    for(int i = 0; i < text_len; i++){
        if(isdigit(text[i])){
            perror("Text can't contain numbers!");
            exit(1);
        }

        if(isalpha(text[i])){
            text[j++] = toupper(text[i]);
        } 

    }

    text[j] = '\0';


}

char **construct_code_matrix(char *secret_code, char *text, int *row_num, int *col_num){
    int secret_code_len = strlen(secret_code);
    int text_len = strlen(text);
    int nr_of_rows = 1 + (text_len + secret_code_len - 1) / secret_code_len;

    char **mat = malloc(nr_of_rows * sizeof(char *));

    if(mat == NULL){
        perror("Could not allocate memory!");
        exit(1);
    }

    for(int i = 0; i < nr_of_rows; i++){
        mat[i] = malloc(sizeof(char) * secret_code_len);
        if(mat[i] == NULL){
            perror("Could not allocate memory!");
            exit(1);
    }
    }


    int text_cursor = 0;
    for(int i = 0; i < nr_of_rows; i++){
        for(int j = 0; j < secret_code_len; j++){
            if(i == 0){
                mat[i][j] = secret_code[j];
            }
            else if (text_cursor < text_len){
                mat[i][j] = text[text_cursor++];
            }
            else{
                mat[i][j] = '*';
            }
        }
    }

    *row_num = nr_of_rows;
    *col_num = secret_code_len;
    
    return mat;

}

void write_code_matrix(const char *filepath, char **mat, int row_num, int col_num){
    FILE *file;

    file = fopen(filepath, "w");

    if(file == NULL){
        perror("Failed to open file!");
        exit(1);
    }

    fputs("The matrix is:\n", file);

    for(int i = 1; i < row_num; i++){
        for(int j = 0; j < col_num; j++){
            fputc(mat[i][j], file);
        }
        fputc('\n', file);
    }

    fclose(file);

}

int compare_by_letter(const void *a, const void *b) {
    const Header *ha = (const Header *)a;
    const Header *hb = (const Header *)b;
    return ha->letter - hb->letter;
}

Header *get_and_sort_mat_headers(char **mat, int col_num){
    Header *headers = malloc(sizeof(Header) * col_num);
    if(headers == NULL){
        perror("Could not allocate memory!");
        exit(1);
    }

    for(int i = 0; i < col_num; i++){
        headers[i].letter = mat[0][i];
        headers[i].original_index = i;
    }

    qsort(headers, col_num, sizeof(Header), compare_by_letter);

    return headers;
}

void write_encrypted_text(const char *filepath, char **mat, int row_num, int col_num, Header *headers){
    FILE *file;
    file = fopen(filepath, "a");

    if(file == NULL){
        perror("Failed to open file.");
        exit(1);
    }

    fputc('\n', file);
    fputs("The encrypted text is:\n", file);

    int counter = 0;
    
    for(int i = 0; i < col_num; i++){
        int current_col = headers[i].original_index;
        for(int j = 1; j < row_num; j++){
            char char_at_pos = mat[j][current_col];

            if(char_at_pos == '*'){
                continue;
            }

            if(counter % 5 == 0 && counter != 0){
                fputc(' ', file);
            }

            fputc(char_at_pos, file);
            counter++;


        }
    }

    fclose(file);
}
