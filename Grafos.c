#include<stdio.h>
#include<stdlib.h>
#include "Grafos.h"
int main(){
    int isDigraph = 0;
    Grafo *gf;
    gf = createGrafo(5, 5, 0);
    insertEdges(gf, 0, 1, isDigraph, 0);
    insertEdges(gf, 0, 4, isDigraph, 0);
    insertEdges(gf, 1, 2, isDigraph, 0);
    insertEdges(gf, 1, 3, isDigraph, 0);
    insertEdges(gf, 1, 4, isDigraph, 0);
    insertEdges(gf, 2, 3, isDigraph, 0);
    int vectVisited[5];
    searchSenai(gf, 0, vectVisited);
    int i;
    for(i=0; i < gf->numVertices; i++){
        printf("%d\n", vectVisited[i]);
    }
    releaseGrafo(gf);
    

    return 0;
}