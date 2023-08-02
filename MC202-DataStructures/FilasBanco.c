#include <stdio.h>
#include <stdlib.h>

typedef struct _vector{
    int *val;
    int size;
}vector;

vector read_filas(){
    vector array;
    array.size = 0;

    int n;
    scanf("%d",&n);

    int *sz_filas = (int*)calloc(n,sizeof(int));
    int **filas = (int**)calloc(n,sizeof(int*));

    for(int i = 0 ; i < n ; i++){
        scanf("%d",&sz_filas[i]);

        array.size += sz_filas[i];

        if(sz_filas[i] == 0)continue;
        
        filas[i] = (int*)calloc(sz_filas[i], sizeof(int));

        for(int j = 0 ; j < sz_filas[i] ; j++){
            scanf("%d",&filas[i][j]);
        }
    }
    
    array.val = (int*)calloc(array.size, sizeof(int));

    int count = 0;

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < sz_filas[i] ; j++){
            array.val[count] = filas[i][j];
            count++;
        }
    }


    for(int i = 0 ; i < n ; i++){
        free(filas[i]);
    }
    free(filas);
    free(sz_filas);
    filas = NULL;
    sz_filas = NULL;


    return array;
}

void print_vector(vector array){
    for(int i = 0 ; i < array.size-1 ; i++){
        printf("%d ", array.val[i]);
    }
    printf("%d",array.val[array.size-1]);
    //printf("\n");
}

void destroy_vector(vector *array){
    free(array->val);
    array->val = NULL;
    array->size = 0;
}

void merge(vector *array, int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int*)calloc(n1, sizeof(int));
    int *R = (int*)calloc(n2, sizeof(int));

    for(int i = 0 ; i < n1 ; i++){
        L[i] = array->val[l + i];
    }

    for(int i = 0 ; i < n2 ; i++){
        R[i] = array->val[m + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while(i < n1 && j < n2){
        if(L[i] < R[j]){
            array->val[k] = L[i];
            i++;
        }
        else{
            array->val[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        array->val[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        array->val[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
    L = NULL;
    R = NULL;
}

void merge_sort(vector *array,int l, int r){
    if(l < r){
        int m = (l+r)/2;
        merge_sort(array,l,m);
        merge_sort(array,m+1,r);
        merge(array,l,m,r);
    }
}

int main(){
    vector fila;

    fila = read_filas();

    if(fila.size == 0) return 0;

    merge_sort(&fila,0,fila.size - 1);

    print_vector(fila);

    destroy_vector(&fila);

    return 0;
}