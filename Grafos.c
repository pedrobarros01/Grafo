#include<stdio.h>
#include<stdlib.h>
#include "Grafos.h"
int main(){
    int isDigraph = 1;
    Grafo *gf;
    gf = createGrafo(5, 5, 0);
    insertEdges(gf, 0, 1, isDigraph, 0);
    insertEdges(gf, 1, 3, isDigraph, 0);
    insertEdges(gf, 1, 2, isDigraph, 0);
    insertEdges(gf, 2, 4, isDigraph, 0);
    insertEdges(gf, 3, 0, isDigraph, 0);
    insertEdges(gf, 3, 4, isDigraph, 0);
    insertEdges(gf, 4, 1, isDigraph, 0);
    int vectVisited[5];
    depthSearch(gf, 0, vectVisited);

    releaseGrafo(gf);
    

    return 0;
}