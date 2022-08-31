#ifndef GRAFOS_H
#define GRAFOS_H
#include<stdlib.h>
#include<stdbool.h>
typedef struct Grafo {
    int isWeighted;
    int numVertices;
    int maxGrade;
    int** edges;
    float** weights;
    int* grade;
} Grafo;

Grafo* createGrafo(int numVertices, int maxGrade, int isWeighted){
    Grafo *gf = (Grafo*)malloc(sizeof(Grafo));
    if (gf != NULL)
    {
        int i;
        gf->numVertices = numVertices;
        gf->maxGrade = maxGrade;
        gf->isWeighted = (isWeighted != 0)?1:0;
        gf->grade = (int*)calloc(numVertices, sizeof(int));
        gf->edges = (int**)malloc(numVertices*sizeof(int*));
        for(i=0; i < numVertices; i++){
            gf->edges[i] = (int*)malloc(maxGrade*sizeof(int));
            if(gf->isWeighted){
                gf->weights = (float**)malloc(numVertices*sizeof(float*));
                for(i=0; i < numVertices; i++){
                    gf->weights[i] = (float*)malloc(maxGrade*sizeof(float));  
                }
            }
        }
    }
    return gf;
}

void releaseGrafo(Grafo *gf){
    if(gf != NULL){
        int i;
        for(i=0; i < gf->numVertices; i++){
            free(gf->edges[i]);
        }
        free(gf->edges);
        if(gf->isWeighted){
            for(i=0; i<gf->numVertices; i++){
                free(gf->weights[i]);
            }
            free(gf->weights);

        }
        free(gf->grade);
        free(gf);
    }
}

int insertEdges(Grafo *gf, int origin, int destiny, int isDigraph, float weight ){
    if(gf == NULL){
        return 0;
    }
    if(origin < 0 || origin >= gf->numVertices){
        return 0;
    }
    if(destiny < 0 || destiny >= gf->numVertices){
        return 0;
    }
    gf->edges[origin][gf->grade[origin]] = destiny; // insere a aresta do vertice origin na proxima posição da lista de arestas
    if(gf->isWeighted){
        gf->weights[origin][gf->grade[origin]] = weight;
    }
    gf->grade[origin]++;
    if(isDigraph == 0){
        insertEdges(gf, destiny, origin, 1, weight);
    }
    return 1;

}
int removeEdges(Grafo *gf, int origin, int destiny, int isDigraph){
    if(gf == NULL){
        return 0;;
    }
    if(origin < 0 || origin >= gf->numVertices){
        return 0;
    }
    if(destiny < 0 || destiny >= gf->numVertices){
        return 0;
    }
    int i = 0;
    while(i < gf->grade[origin] && gf->edges[origin][i] != destiny){
        i++;
    }
    if(i == gf->grade[origin]){
        return 0;
    }
    gf->grade[origin]--;
    gf->edges[origin][i] = gf->edges[origin][gf->grade[origin]];
    if(gf->isWeighted){
        gf->weights[origin][i] = gf->weights[origin][gf->grade[origin]];
    }
    if(isDigraph == 0){
        removeEdges(gf, destiny, origin, 1);
    }
    return 1;
}

void depthSearchAux(Grafo *gf, int verticeInitial, int *vectVisited, int cont){
    int i;
    vectVisited[verticeInitial] = cont;
    for(i =0; i < gf->grade[verticeInitial]; i++){
        if(!vectVisited[gf->edges[verticeInitial][i]]){
            depthSearchAux(gf, gf->edges[verticeInitial][i], vectVisited, cont + 1);        
        }
    }

}

void depthSearch(Grafo *gf, int verticeInitial, int *vectVisited){
/*
gf -> grafo
verticeInitial -> vertice inicial para a busca
vectVisited -> vetor de resposta da busca, mesmo numero de vertice, marco a ordem de visita

*/
int i, cont = 1;
for(i=0; i<gf->numVertices; i++){
    vectVisited[i] = 0;
}
depthSearchAux(gf, verticeInitial, vectVisited, cont);
}


void searchSenaiAux(Grafo *gf, int *vectVisited, int verticeAtual, int indiceVect, bool* statusVisited){
int i, j;
statusVisited[verticeAtual] = true;
vectVisited[verticeAtual] = verticeAtual;

for(i=0; i < gf->grade[verticeAtual]; i++){
    printf("caminho antigo: %d\n", verticeAtual);
    int edge = gf->edges[verticeAtual][i];
    if(!statusVisited[edge]){  
        printf("caminho atual: %d\n", edge); 
        verticeAtual = edge;
        searchSenaiAux(gf, vectVisited, verticeAtual, indiceVect + 1, statusVisited);
    }
    
    
}
}
void searchSenai(Grafo *gf, int verticeInicial, int *vectVisited){
    int i, cont = 0;
    bool statusVisited[5];

    for(i=0; i < gf->numVertices; i++){
        vectVisited[i] = 0;
        statusVisited[i] = false;
    }
    searchSenaiAux(gf, vectVisited, verticeInicial, cont, statusVisited);
}

#endif