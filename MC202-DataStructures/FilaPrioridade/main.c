#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPrioridade.h"

int main(int argc, char **argv){
    char *path = (argc > 1) ? argv[1] : NULL;

    int n;
    FILE *f = fopen(path, "r");

    fscanf(f, "%d\n", &n);

    p_heap fila = criar_Heap(n);

    for(int i = 0 ; i < n ; i++){
        char operator;
        item cliente;

        fscanf(f, "%c", &operator);
        //printf("%c\n", operator);
        if(operator == 'P'){
            if(fila->n == 0){
                printf("[]\n");
                continue;
            }
            printf("[%s %d ... ",fila->cliente[0].sobrenome,fila->cliente[0].p);
            printf("%s %d]\n",fila->cliente[fila->minH].sobrenome,fila->cliente[fila->minH].p);
        }else if(operator == 'L'){
            if(fila->n > 0){
                printf("Mesa liberada para Sr(a) %s.\n",fila->cliente[0].sobrenome);
            }
            remover_Heap(fila,0);
        }else if(operator == 'D'){
            printf("Sr(a) %s desistiu de esperar e foi embora.\n",fila->cliente[fila->minH].sobrenome);
            remover_Heap(fila,fila->minH);
        }else if(operator == 'I'){
            fscanf(f , " %s %d",cliente.sobrenome,&cliente.p);
            inserir_Heap(fila,cliente);
        }else if(operator == 'M'){
            fscanf(f , " %s %d",cliente.sobrenome,&cliente.p);
            trocar_prioridade(fila,cliente);
        }
        fscanf(f, "\n");
        //printar_Heap(fila);
    }

    //printar_Heap(fila);

    fclose(f);
    destruir_Heap(fila);

    return 0;
}