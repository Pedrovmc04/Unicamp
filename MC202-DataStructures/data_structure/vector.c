#include <stdio.h>
#include <stdlib.h>

typedef struct _vector{
    int *val;
    int size;
}vector;

vector new_vector(int size){
    vector v;

    v.val = (int*)calloc(size, sizeof(int));
    v.size = size;
}

void destroy_vector(vector *v){
    if(v->val != NULL){
        free(v->val);
        v->val = NULL;
        v->size = 0;
    }
}

int main(){

    


    return 0;
}