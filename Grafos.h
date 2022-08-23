#ifndef GRAFOS_H
#define GRAFOS_H
#include<stdlib.h>
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
#endif