#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vizinho {
    char nome[10];
    struct vizinho *prox;
} TVizinho;

typedef struct grafo {
    char nome[10];
    int idade;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;

TGrafo *insere_vertice(TGrafo *g, char *nome, int idade) {
    TGrafo *vertice = (TGrafo *) malloc(sizeof(TGrafo));
    strcpy(vertice->nome, nome);
    vertice->idade = idade;
    vertice->prox = g;
    vertice->prim_vizinho = NULL;
    return vertice;
}

TGrafo *busca_vertice(TGrafo *vertice, char *nome) {
    while ((vertice != NULL) && (strcmp(vertice->nome, nome) != 0)) {
        vertice = vertice->prox;
    }
    return vertice;
}

TVizinho *busca_vizinho(TVizinho *vizinho, char *nome) {
    while ((vizinho != NULL) && (strcmp(vizinho->nome, nome) != 0)) {
        vizinho = vizinho->prox;
    }
    return vizinho;
}

void insere_aresta(TGrafo *g, char *nome_origem, char *nome_destino) {
    TGrafo *pv1 = busca_vertice(g, nome_origem);
    TGrafo *pv2 = busca_vertice(g, nome_destino);
    if (pv1 != NULL && pv2 != NULL) {
        TVizinho *vizinho = (TVizinho *) malloc(sizeof(TVizinho));
        strcpy(vizinho->nome, nome_destino);
        vizinho->prox = pv1->prim_vizinho;
        pv1->prim_vizinho = vizinho;
    }
}

void imprime(TGrafo *vertice) {
    while (vertice != NULL) {
        printf("Pessoa: %s - %d anos\n", vertice->nome, vertice->idade);
        printf("Segue: ");
        TVizinho *vizinho = vertice->prim_vizinho;
        while (vizinho != NULL) {
            printf("%s ", vizinho->nome);
            vizinho = vizinho->prox;
        }
        printf("\n\n");
        vertice = vertice->prox;
    }
}

int numero_seguidos(TGrafo *g, char *nome) {
    if (!busca_vertice(g, nome)){printf("Pessoa nao encontrada.\n"); return 0;}
    
    else {
        TGrafo * pessoa = busca_vertice(g,nome);
        TVizinho *segue = pessoa->prim_vizinho;
        int cont = 0;
        while(segue != NULL) {
            cont++;
            segue = segue->prox;
        }
        return cont;
    }
}

int seguidores(TGrafo *g, char *nome, int imprime) {
    int cont = 0;
    TGrafo *aux = g; TVizinho *verif = NULL;
    while(aux != NULL) {
        if(!strcmp(nome, aux->nome)) {aux = aux->prox; continue;} //pula pessoa que tem o nome que estamos varrendo com o aux, ja que queremos ver os seguidos dela, nao os seguidores dela
        verif = aux->prim_vizinho;
        while(verif != NULL) {
            if(!strcmp(nome, verif->nome)) {
                
                cont++; if (imprime) {
                printf("%s \n", aux->nome);
            }
        
            break; //procura pela proxima pessoa que segue.
        }
        verif = verif->prox;
        }

        aux = aux->prox;
    }

    return cont;
}

TGrafo *mais_popular(TGrafo *g) {

    int maisseguidores = -1, seguidoresatual = 0;
    TGrafo *famoso = NULL;
    TGrafo *aux = g;


    while(aux != NULL) {
        seguidoresatual = seguidores(g,aux->nome, 0);
        if (seguidoresatual > maisseguidores) {
            famoso = aux;
            maisseguidores = seguidoresatual;
        }
        aux = aux->prox;
    }
    return famoso;
}

int segue_mais_velho(TGrafo *g, int imprime) {
    int velhos = 0, velhoatual = 0;
    TGrafo *aux = g;
    TVizinho *verif = NULL;

    while (aux != NULL) {
        verif = aux->prim_vizinho;
        velhoatual = 0;

        while (verif != NULL) {
            if (busca_vertice(g, verif->nome)->idade > aux->idade) {
                velhoatual++;
            }

            verif = verif->prox;
        }

        // Segue pelo menos alguém, e todos são mais velhos.
        if (velhoatual > 0 &&
            velhoatual == numero_seguidos(g, aux->nome)) {
            
            velhos++;

            if (imprime == 1) {
                printf("%s\n", aux->nome);
            }
        }

        aux = aux->prox;
    }

    return velhos;
}

void libera_vizinho(TVizinho *vizinho) {
    if (vizinho != NULL) {
        libera_vizinho(vizinho->prox);
        free(vizinho);
    }
}

void libera_vertice(TGrafo *vertice) {
    if (vertice != NULL) {
        libera_vizinho(vertice->prim_vizinho);
        libera_vertice(vertice->prox);
        free(vertice);
    }
}

int main() {
    /* A função main lê os dados de entrada, cria o grafo e chama as funções solicitadas no problema
    * depois imprime os resultados solicitados
    * ELA NÃO DEVE SER MODIFICADA
    * */
    int num_vertices, num_arestas;
    char nome[30];
    char origem[30], destino[30];
    char l[100];
    char delimitador[] = "-";
    char *ptr;
    int idade;
    int i;
    TGrafo *g = NULL;

    //le numero de vertices
    scanf("%d", &num_vertices);
    //le e cria os vertices
    for (i = 0; i < num_vertices; i++) {
        scanf("%s", l);
        //quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(nome,ptr);
        //printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        idade = atoi(ptr);
        g = insere_vertice(g, nome, idade);
    }

    //Le numero de arestas e depois le os dados de cada aresta
    //Cria as arestas no grafo
    scanf("%d", &num_arestas);
    for (i = 0; i < num_arestas; i++) {
        scanf("%s", l);
        //quebra a string de entrada
        ptr = strtok(l, delimitador);
        strcpy(origem,ptr);
        //printf("%s", nome);
        ptr = strtok(NULL, delimitador);
        strcpy(destino,ptr);
        insere_aresta(g, origem, destino);
    }

    //Le nome de pessoa
    scanf("%s", nome);

    //Encontra o número de seguidos dessa pessoa
    printf("SEGUIDOS por %s: %d\n", nome, numero_seguidos(g, nome));

    //Encontra os seguidores de uma determinada pessoa
    printf("SEGUIDORES de %s:\n", nome);
    seguidores(g, nome, 1);

    TGrafo *p;

    //Encontra mais popular
    p = mais_popular(g);
    printf("MAIS POPULAR: %s\n", p->nome);

    //Encontra as pessoas que seguem apenas pessoas mais velhas
    printf("SEGUEM APENAS PESSOAS MAIS VELHAS:\n");
    segue_mais_velho(g,1);

    libera_vertice(g);
}
