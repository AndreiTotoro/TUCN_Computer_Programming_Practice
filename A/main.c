#include "functions.h"
#include <stdlib.h>

int main(){
    char secret_code[MAX_SIZE_OF_CODE];
    char text[MAX_SIZE_OF_TEXT];
    char **mat;
    int row_num;
    int col_num;
    Header *headers;

    read_secret_code("input_text_a.txt", secret_code);
    read_text("input_text_a.txt", text);
    mat = construct_code_matrix(secret_code, text, &row_num, &col_num);
    headers = get_and_sort_mat_headers(mat, col_num);
    write_code_matrix("output_text_a.txt", mat, row_num, col_num);
    write_encrypted_text("output_text_a.txt", mat, row_num, col_num, headers);

    free(headers);
    for(int i = 0; i < row_num; i++){
        free(mat[i]);
    }
    free(mat);
}