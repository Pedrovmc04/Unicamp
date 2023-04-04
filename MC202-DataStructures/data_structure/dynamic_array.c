#include <stdio.h>
#include <stdlib.h>

int main(){
    int n; // size of the array
    scanf("%d",&n);

    ////////////////////////////////////////////////////////////////

    int *vector = (int*)calloc(n, sizeof(int)); // allocate memory for vector

    for(int i = 0 ; i < n ; i++){
        scanf("%d",&vector[i]); // read vector
    }

    for(int i = 0 ; i < n ; i++){
        printf("%d ",vector[i]); // write vector
    }
    printf("\n");

    free(vector);
    vector = NULL;


    return 0;
}