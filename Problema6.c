#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct typevertices Pessoas;

struct typevertices{
    int numero;
    double x;
    double y;
    Pessoas *origem;
};

typedef struct typearesta{
    double peso;
    Pessoas *vertice1;
    Pessoas *vertice2;
}Aresta;

#define MALLOC(t,n) (t*) malloc(sizeof(t)*n)
#define distancia(ponto1, ponto2) sqrt(pow(ponto1->x - ponto2->x, 2) + pow(ponto1->y - ponto2->y, 2))

int comparadorPeso(const void ** a, const void ** b) {
    double peso_a, peso_b;
    peso_a = ((Aresta*)*a)->peso;
    peso_b = ((Aresta*)*b)->peso;

    if (peso_a == peso_b)
        return 0;

    if (peso_a < peso_b)
        return -1;

    return 1;
}

int main(){

    int n, k, i, j;

    scanf("%d %d", &n, &k);

    int NArestas;

    NArestas = k * (n - k);

    Aresta *arestas[k][n-k];

    Pessoas *vertice[n];

    for(i = 0; i < n; i++){
        vertice[i] = MALLOC(Pessoas, 1);
        vertice[i]->origem = vertice[i];
        vertice[i]->numero = i;
        scanf("%lf %lf", &vertice[i]->x, &vertice[i]->y);
    }
    
    double soma;
    soma = 0;
    int cont[k];
    for(i = 0; i < k; i++){
        cont[i] = 0;
        for(j = k; j < n; j++){
            arestas[i][j-k] = MALLOC(Aresta, 1);
            arestas[i][j-k]->peso = distancia(vertice[i], vertice[j]);

            arestas[i][j-k]->vertice1 = vertice[i];

            arestas[i][j-k]->vertice2 = vertice[j];
        }
        qsort(arestas[i], NArestas, sizeof(Aresta*), comparadorPeso);
    }
        
    i = 0;
    
    int cont2, ver;

    ver = 0;

    while(ver == 0){
        Pessoas *vertice1, *vertice2;
        for(i = 0; i < k; i++){
            vertice1 = arestas[i][cont[i]]->vertice1;
            vertice2 = arestas[i][cont[i]]->vertice2;
            vertice1->origem = vertice2;
        }
        if(arestas[i][0]->vertice1->numero < k){
            Pessoas *vertice1, *vertice2;

            // vertice1 = arestas[i]->vertice1;
            // vertice2 = arestas[i]->vertice2;

            // cont1 = cont2 = 0;

            while(vertice1 != vertice1->origem){
                // cont1++;
                vertice1 = vertice1->origem;
            }

            while(vertice2 != vertice2->origem){
                cont2++;
                vertice2 = vertice2->origem;
            }

            if(vertice1 != vertice2){
                // if(cont1 < cont2){
                    vertice1->origem = vertice2;
                }
                else{
                    vertice2->origem = vertice1;
                }
                // soma += arestas[i]->peso;
            }
        }
        i++;
    }

    // printf("%.5lf\n", soma);

    return 0;

}