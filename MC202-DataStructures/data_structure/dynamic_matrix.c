#include <stdio.h>
#include <stdlib.h>

int** create_matrix(int l, int c){
    int **matrix = (int**)calloc(l, sizeof(int*));

    for(int i = 0 ; i < l ; i++){
        matrix[i] = (int*)calloc(c, sizeof(int));
        for(int j = 0 ; j < c ; j++){
            scanf("%d",&matrix[i][j]);
        }
    }

    return matrix;
}

void print_matrix(int **matrix,int l,int c){
    for(int i = 0; i < l; i++){
        for(int j = 0; j < c; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void destroy_matrix(int ***matrix,int l){

    if(*matrix != NULL){
        for(int i = 0 ; i < l ; i++){
            free((*matrix)[i]);
        }
        free(*matrix);
        *matrix = NULL;
    }
}

int main(){
    int l,c; // size of lines and columns
    scanf("%d %d",&l,&c);

    int **matrix = create_matrix(l,c);

    print_matrix(matrix,l,c);

    destroy_matrix(&matrix,l);

    return 0;
}