TP *retira_antes_depois_x(TP *p, int(x)) {

    TP *aux = TP_inicializa() //reestruturar a pilha original.
    TP *resp = TP_inicializa()
    int q = INT_MIN, r; //x é como se fosse o topo, por isso o int min

    while (1)
    {
        r = TP_pop(p);
        TP_push(aux, r);
        if(r != x) {
            if (q != INT_MIN) { //anterior é intmin? (aqui verifica se x está no topo, porque se estiver, nao podemos colocar o vazio como resposta.)
                TP_push(resp, r);
            }
        }

        else if(!TP_vazia(p)) {
            int z = TP_pop(p);
            TP_push(aux, z);
        }

        q = r;
        if(TP_vazia(p)) {
            TP_push(resp, q);
            break;
        }

    

    }
    

    while(!TP_vazia(aux)) {
        int y = TP_pop(aux);
        TP_push(p, y);
    }

    while(!TP_vazia(resp)) {
        int y = TP_pop(resp);
        TP_push(aux,y);
    }

    TP_retira(resp);
    return aux;




}
