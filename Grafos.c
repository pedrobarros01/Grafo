#include<stdio.h>
#include<stdlib.h>
#include "Grafos.h"
int main(){
    Grafo *gf;
    gf = createGrafo(10, 7, 0);
    printf("Chegou aqui");
    insertEdges(gf, 0, 1, 0, 0);
    insertEdges(gf, 1, 3, 0, 0);
    printf("Chegou aqui2");
    removeEdges(gf, 0, 1, 0);
    printf("Chegou aqui3");    
    releaseGrafo(gf);
    printf("Chegou aqui4");

    printf("Hello World");
    return 0;
}