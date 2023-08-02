#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPrioridade.h"

void trocar(item *a,item *b){
    item t = *a;
    *a = *b;
    *b = t;
}

int comparar_string(char *str1,char *str2){
    if(strlen(str1) != strlen(str2))return 0;

    for(int i = 0 ; i < strlen(str1) ; ++i){
        if(str1[i] != str2[i])return 0;
    }

    return 1;
}

p_heap criar_Heap(int tam){
    p_heap new = malloc(sizeof(heap));
    new->cliente = malloc((tam+1)*sizeof(item));
    new->tam = tam;
    new->n = 0;
    new->minH = 0;

    return new;
}

void destruir_Heap(p_heap heap){
    free(heap->cliente);
    free(heap);
}

void inserir_Heap(p_heap heap,item cliente){
    if(heap->n == heap->tam)return;

    heap->cliente[heap->n] = cliente;
    heap->n++;

    sobe_Heap(heap,heap->n - 1);
}

void remover_Heap(p_heap heap,int pos){
    heap->n--;
    heap->cliente[pos] = heap->cliente[heap->n];
    desce_heap(heap,0);
    if(pos != 0){
        heap->minH = procurar_min(heap);
    }
}

void sobe_Heap(p_heap heap,int k){
    if(k > 0 && heap->cliente[PAI(k)].p < heap->cliente[k].p){
        trocar(&heap->cliente[PAI(k)],&heap->cliente[k]);
        sobe_Heap(heap,PAI(k));
        if(heap->cliente[heap->minH].p >= heap->cliente[k].p)heap->minH = k;
    }
}

void desce_heap(p_heap heap,int k){
    if(F_ESQ(k) >= heap->n){
        if(heap->cliente[heap->minH].p >= heap->cliente[k].p)heap->minH = k;
        return;
    }
    int maior_filho = F_ESQ(k);
    if(F_DIR(k) < heap->n && heap->cliente[F_DIR(k)].p > heap->cliente[F_ESQ(k)].p){
        maior_filho = F_DIR(k);
    }

    if(heap->cliente[k].p < heap->cliente[maior_filho].p){
        trocar(&heap->cliente[k],&heap->cliente[maior_filho]);
        if(heap->cliente[heap->minH].p >= heap->cliente[maior_filho].p)heap->minH = maior_filho;
        desce_heap(heap,maior_filho);
    }
}

void trocar_prioridade(p_heap heap,item cliente){
    for(int i = 0 ; i < heap->n ; i++){
        if(strcmp(heap->cliente[i].sobrenome,cliente.sobrenome) == 0){

            if(heap->minH == i && cliente.p > heap->cliente[i].p){
                heap->cliente[i].p = cliente.p;
                heap->minH = procurar_min(heap);
            }else{
                heap->cliente[i].p = cliente.p;
            }
            
            if(i == 0){
                desce_heap(heap,i);
            }else{
                sobe_Heap(heap,i);
            }

            break;
        }        
    }
}

int procurar_min(p_heap heap){
    int minP = INF,pos = 0;

    for(int i = 0 ; i < heap->n ; i++){
        if(minP > heap->cliente[i].p){
            minP = heap->cliente[i].p;
            pos = i;
        }
    }

    return pos;
}

void printar_Heap(p_heap heap){
    for(int i = 0 ; i < heap->n ; i++){
        printf("%d %s |",heap->cliente[i].p,heap->cliente[i].sobrenome);
    }
    printf("\n");
}