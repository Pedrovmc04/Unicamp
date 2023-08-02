#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _bombas{
    int *x;
    int *y;
    int *r;

    int size;
}bombas;

bombas input_bombas(int size){
    bombas bomb;

    bomb.x = calloc(size, sizeof(int));
    bomb.y = calloc(size, sizeof(int));
    bomb.r = calloc(size, sizeof(int));

    bomb.size = size;

    for(int i = 0 ; i < size ; i++){
        scanf("%d %d %d",&bomb.x[i],&bomb.y[i],&bomb.r[i]);
    }

    return bomb;
}

void free_bombas(bombas *bomb){
    if(bomb != NULL){
        free(bomb->x);
        free(bomb->y);
        free(bomb->r);
        
        bomb->x = NULL;
        bomb->y = NULL;
        bomb->r = NULL;
        bomb->size = 0;
    }
}

int** new_matrix(int l, int c){
    int **matrix = (int**)calloc(l, sizeof(int*));

    for(int i = 0 ; i < l ; i++){
        matrix[i] = (int*)calloc(c, sizeof(int));
    }

    return matrix;
}

bool verify_coords(int Ln,int Cn,bombas *bomb,int x , int y){

    if(!(x >= 0 && x < Ln && y >= 0 && y < Cn))return false;

    for(int i = 0 ; i < bomb->size ; i++){
        if(!(bomb->x[i] >= 0 && bomb->x[i] < Ln && bomb->y[i] >= 0 && bomb->y[i] < Cn))return false;
    }

    return true;
}

int main(){
    int Ln,Cn,n;
    int x,y,def; // Coords Tank and Defense
    bool flag = true;

    scanf("%dx%d",&Ln,&Cn);
    scanf("%d",&n);
    
    if(n < 0){
        printf("-1\n");
        return 0;
    }

    bombas bombs = input_bombas(n);

    scanf("%d %d %d",&x,&y,&def);

    if(!verify_coords(Ln,Cn,&bombs,x,y)){
        printf("-1\n");
        return 0;
    }

    for(int i = 0 ; i < bombs.size ; i++){
        int xx = bombs.x[i] - x;
        int yy = bombs.y[i] - y;

        if(xx < 0)xx = -xx;
        if(yy < 0)yy = -yy;

        if(xx <= bombs.r[i] && yy <= bombs.r[i]){
            def--;
            if(def == 0){
                flag = false;
                break;
            }
        }      
    }

    if(flag){
        printf("Ufa\n");
    }else{
        printf("Boom\n");
    }

    free_bombas(&bombs);

    return 0;
}