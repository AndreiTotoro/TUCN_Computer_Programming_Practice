#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void strip_newline(char *buffer){
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

void read_and_validate_key_mat(char* const filepath, char ***mat){
    FILE *file;

    *mat = malloc(SQUARE_MATRIX_SIZE * sizeof(char *));
    if(*mat == NULL){
        perror("Failed to allocate memory");
        exit(1);
    }

    file = fopen(filepath, "r");

    if(file == NULL){
        perror("Failed to open file.");
        exit(1);
    }

    char buffer[10];

    for(int i = 0; i < SQUARE_MATRIX_SIZE; i++){
        if(fgets(buffer, sizeof(buffer), file) == NULL){
            perror("Failed to read from file.");
            exit(1);
        }
        strip_newline(buffer);

        (*mat)[i] = malloc(SQUARE_MATRIX_SIZE * sizeof(char));
        if((*mat)[i] == NULL){
            perror("Failed to allocate memory");
            exit(1);
        }

        for(int j = 0; j < SQUARE_MATRIX_SIZE; j++){
            if(islower(buffer[j])){
                perror("The program encountered an illegal character");
                exit(1);
            }
            (*mat)[i][j] = buffer[j];
        }
    }

    fclose(file);
}

void read_and_validate_word_from_keyboard(char **word_from_keyboard){

    *word_from_keyboard = malloc(100 * sizeof(char));

    printf("Please input your word:\n");
    scanf("%s", *word_from_keyboard);

    strip_newline(*word_from_keyboard);
    
    for(int i = 0; i < strlen(*word_from_keyboard); i++){
        char const letter = (*word_from_keyboard)[i];
        if(!isalpha(letter)){
            perror("Word entered does not contain only letters");
            exit(1);
        }
        (*word_from_keyboard)[i] = toupper(letter);
    }
}

void read_text_to_decrypt(char* const text_to_decrypt_filepath, char** text_to_decrypt){
    FILE *file;

    file = fopen(text_to_decrypt_filepath, "r");

    if(file == NULL){
        perror("Failed to open file.");
        exit(1);
    }

    *text_to_decrypt = malloc(1024 * sizeof(char));
    if(*text_to_decrypt == NULL){
        perror("Failed to allocate memory");
        exit(1);
    }

    char buffer[1024];

    if(fgets(buffer, sizeof(buffer), file) == NULL){
        perror("Failed to read from file,");
        exit(1);
    }

    strip_newline(buffer);

    strcpy(*text_to_decrypt, buffer);
}

void obtain_and_store_coordinates(char **mat, char *const word_from_keyboard, Coordinate **coordinates){
    *coordinates = malloc(sizeof(Coordinate) * strlen(word_from_keyboard));

    int cnt = 0;
    while(word_from_keyboard[cnt] != '\0'){
        char letter = word_from_keyboard[cnt];
        for(int i = 0; i < SQUARE_MATRIX_SIZE; i++){
            for(int j = 0; j < SQUARE_MATRIX_SIZE; j++){
                if(letter == 'J'){
                    if(mat[i][j] == 'I'){
                        (*coordinates)[cnt].x=i;
                        (*coordinates)[cnt].y=j;
                        j = SQUARE_MATRIX_SIZE;
                    }
                } else{
                    if(mat[i][j] == letter){
                        (*coordinates)[cnt].x=i;
                        (*coordinates)[cnt].y=j;
                        j = SQUARE_MATRIX_SIZE;
                    }
                }
            }
        }
        cnt++;
    }
}
void get_code_in_coordinates(Coordinate *coordinates, char *const word_from_keyboard, Coordinate **code_in_coordinates){
    int word_len = strlen(word_from_keyboard);
    *code_in_coordinates = malloc(sizeof(Coordinate) * word_len);
    if (*code_in_coordinates == NULL){
        perror("Failed to allocate memory");
        exit(1);
    }
    int *flat = (int *)coordinates; 

    for(int k = 0; k < word_len; k++){
        (*code_in_coordinates)[k].x = flat[k]; 
        (*code_in_coordinates)[k].y = flat[k + word_len];
    }
}

void print_decrypted_word(char **mat, Coordinate *code_in_coordinates, char const *word_from_keyboard){
    for(int i = 0; i < strlen(word_from_keyboard); i++){
        printf("%c", mat[code_in_coordinates[i].x][code_in_coordinates[i].y]);
    }
    printf("\n");
}

void decrypt_and_write_encrypted_text(char **key_mat, char *text_to_decrypt, char *const filepath){

    FILE *file;

    file = fopen(filepath, "w");

    char *word = strtok(text_to_decrypt, " ");

    while(word != NULL){
         strip_newline(word);
    
        for(int i = 0; i < strlen(word); i++){
            char const letter = word[i];
            if(!isalpha(letter)){
                perror("Word entered does not contain only letters");
                exit(1);
            }
            word[i] = toupper(letter);
        }

        Coordinate *coordinates;
        Coordinate *code_in_coordinates;

        obtain_and_store_coordinates(key_mat, word, &coordinates);

        get_code_in_coordinates(coordinates, word, &code_in_coordinates);

        for(int i = 0; i < strlen(word); i++){
            fputc(key_mat[code_in_coordinates[i].x][code_in_coordinates[i].y], file);
        }
        fputc(' ', file);

        word = strtok(NULL, " ");
    }

   fclose(file);
}

void clean_up(char **key_mat, char *word_from_keyboard, char *text_to_decrypt, Coordinate *coordinates, Coordinate *code_in_coordinates){
    for(int i = 0; i < SQUARE_MATRIX_SIZE; i++){
        free(key_mat[i]);
    }
    free(key_mat);
    free(word_from_keyboard);
    free(text_to_decrypt);
    free(coordinates);
    free(code_in_coordinates);
}
