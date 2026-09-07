#include <stdio.h>
#include <stdlib.h>



typedef struct Vizinho { 
    int id_vizinho;
     struct Vizinho* prox; }
 Tvizinho; 
 
 
 
 typedef struct Grafo 
 { int id_vertice; 
    struct Grafo* prox; 
    Tvizinho* prim_vizinho; } 
 Tgrafo;


 Tgrafo* busca(Tgrafo* g, int x) {
     while((g != NULL) && (g->id_vertice != x)){ 
        g = g->prox; 
    } return g; 
 }


void libera (Tgrafo *a, int v) {
    if (!a) {
        while (a != NULL) {
            if (a->id_vertice == v) {
                libera_vizinhos(a->prim_vizinho);
                Tgrafo *temp = a;
                a = a->prox;
                free(temp);
            }
            a = a->prox;
        }
    }
}

 void libera_vizinhos (Tvizinho *v) {
    while(v != NULL) {
        Tvizinho *temp = v;
        v = v->prox;
        free(temp);
    }
 }



Tvizinho* busca_aresta(Tgrafo *g, int v1, int v2){ //busca ligação que o v1 tem com o v2.
   
    Tvizinho *resp = NULL; 
    
    if(busca(g,v1)&& busca(g,v2)) { //checa se ambos os vértices existem 
        Tgrafo *pv1 = busca(g,v1);
        resp = pv1->prim_vizinho; 
        while ((resp != NULL) && (resp->id_vizinho != v2)) //percorre a lista de vizinhos de v1 procurando por v2 
        { 
            resp = resp->prox; }
        
    return resp;
    } 
}


void insere_um_sentido(Tgrafo *g, int v1, int v2)
{ Tgrafo *p = busca(g, v1); 
    Tvizinho *nova = (Tvizinho *) malloc(sizeof(Tvizinho)); 
    nova->id_vizinho = v2; nova->prox = p->prim_vizinho; 
    p->prim_vizinho = nova; } 
    

void insere_aresta(Tgrafo *g, int v1, int v2){ 
   
    if(!busca_aresta(g, v1, v2)) { insere_um_sentido(g, v1, v2); insere_um_sentido(g, v2, v1); } 
}


void retira_um_sentido(Tgrafo *g, int v1, int v2) { // retira do v2 v1
    
    if(busca(g, v1)) { 
        Tgrafo *p = busca(g, v1);
        Tvizinho *ant = NULL; 
        Tvizinho *atual = p->prim_vizinho; 
        while ((atual) && (atual->id_vizinho != v2)) { 
            ant = atual; atual = atual->prox; } 
            if (ant == NULL) //v2 era o primeiro nó da lista 
            p->prim_vizinho = atual->prox; 
            else ant->prox = atual->prox; free(atual); }
         
        }     


void retira_aresta(Tgrafo *g ,int v1, int v2){ 
    
     if(busca_aresta(g,v1,v2)) {
        Tvizinho* v = busca_aresta(g,v1,v2);
         retira_um_sentido(g, v1, v2);
         retira_um_sentido(g, v2, v1); }
 }



Tgrafo *insere_vertice(Tgrafo *g, int x) { 
    
    if(busca(g, x)) {
         Tgrafo *p = busca(g, x);
        p = (Tgrafo*) malloc(sizeof(Tgrafo)); 
        p->id_vertice = x; 
        p->prox = g; 
        p->prim_vizinho = NULL; 
        g = p; } 
        
    return g; }


Tgrafo *retiraverticenaoorientado (Tgrafo *g, int v) {

    //2 passos
    //1 passo: remover cada vertice do vertice que queremos remover e vice versa. se 2 tem ligações com o 3 e com o 4, devemos remover estas ligações e remover o 2 de 3 e de 4
    //2 passo: remover o vertice v
    if (!busca(g,v)) {
        return g;
    }

    else {

        Tgrafo *verticearemover = busca(g,v);
        Tvizinho *vizinhoatual = verticearemover->prim_vizinho;
        while(vizinhoatual != NULL) {
            retira_aresta(g, verticearemover->id_vertice, vizinhoatual->id_vizinho);
            vizinhoatual = verticearemover->prox;
        }

        

        Tgrafo* ant = NULL;
        Tgrafo* atual = g;


        while ( atual != NULL && atual->id_vertice != v )
        {
            ant = atual;
            atual = atual->prox;
        }

        if (ant == NULL) {

            g = atual->prox;
        }

        else {
            ant->prox = atual->prox;
        }
        
        free(atual);



    }



    return g;





}



Tgrafo *retiraverticedigrafo (Tgrafo *g, int v) {


    // 1: liberar vizinhos do vertice que a gente procura
    // 2: liberar arestas de outros vertices que contenham v
    // 3: liberar v


    if (!busca(g, v)) {

        return g;
    }

    else {

        Tgrafo *verticeremover = busca(g,v);
        //1 passo: liberar os filhos.

        libera_vizinhos(verticeremover->prim_vizinho);
        verticeremover->prim_vizinho = NULL;

        //2 passo: tirar vertices de v que estao em outros vertices. 

        Tgrafo *vertices = g;

        while(vertices != NULL) {

            if (vertices != verticeremover) {

                if (busca_aresta(g, vertices->id_vertice, v)){

                    retira_um_sentido(g, vertices->id_vertice, v);
                }

            }

             vertices = vertices->prox;

        }

        //3 passo: remover v;

        //cuidados a se tomar: se g for NULL ou se g for o primeiro.

        Tgrafo* ant = NULL;
        Tgrafo* atual = g;


        while ( atual != NULL && atual->id_vertice != v )
        {
            ant = atual;
            atual = atual->prox;
        }

        if (ant == NULL) {

            g = atual->prox;
        }

        else {
            ant->prox = atual->prox;
        }
        
        free(atual);



    }



    return g;


}
