#include <stdio.h>
#include <stdlib.h>

typedef struct lista Lista;

struct lista{

        int linha;
        int coluna;
        int valor;
        Lista* prox;
};


Lista* salvaLista(int ** matriz, int l, int c);
Lista* multplicacao(Lista* lista1, Lista* lista2);
Lista* insere_ordenado(Lista* lst, int valor, int linha, int coluna);


void imprimeLista(Lista* lst);
void aleatoria(int l, int c , int **matriz);

int procura(Lista *lst, int i, int j);
int calculaLinha(Lista* lst);
int calculaColuna(Lista* lst);
Lista* insere(Lista* lst, int  num, int i, int j);


int main()
{

        int **matriz, **matriz2;
        int l1, c1, l2, c2;

        printf("Digite o número de linhas e colunas da matriz 1\n");
        scanf("%d %d", &l1 , &c1);

        printf("Digite o número de linhas e colunas da matriz 2\n");
        scanf("%d %d", &l2 , &c2);

        if (c1 != l2)
        {
              printf("Não é possível multiplicar estas matrizes. (c1 != l2) \n");
              exit(1);
        }

        matriz  = (int**) malloc(l1* sizeof(int*));
        matriz2 = (int**) malloc(l2* sizeof(int*));

        for(int i = 0; i < l1; i++)
                matriz[i] = (int*) malloc(c1* sizeof(int));

        for(int i = 0; i < l2; i++)
                matriz2[i] = (int*) malloc(c2* sizeof(int));



          //Recebe as matrizes
            printf("Digite os elementos da matriz1:  \n");
            for(int i = 0; i < l1; i++)
                for(int j = 0; j < c1; j++ )
                    scanf("%d", &matriz[i][j]);

            printf("Digite os elementos da matriz2: \n");
            for(int i = 0; i < l2; i++)
                for(int j = 0; j < c2; j++)
                    scanf("%d", &matriz2[i][j]);

                Lista* lista1 = salvaLista(matriz, l1, c1);
                Lista* lista2 = salvaLista(matriz2, l2, c2);



              Lista* lista3  = multplicacao(lista1, lista2);
              imprimeLista(lista3);

              free(matriz);
              free(matriz2);

    return 0;
}


Lista* multplicacao(Lista* lista1, Lista* lista2)
{
        Lista* lista3 = (Lista*) malloc(sizeof(Lista));
          int soma = 0 ;

          int tamI = calculaLinha(lista1);
          int tamJ = calculaColuna(lista2);
          int tamK = calculaColuna(lista1);


          for(int i = 0; i < tamI; i++)
          {
                for(int j = 0; j < tamJ;  j++)
                 {

                    for(int k = 0; k < tamK; k++)
                       soma += procura(lista1, i, k) * procura(lista2, k, j);

                        lista3 = insere(lista3, soma, i, j);
                        soma = 0;

                    }
            }

    return lista3;
}


int calculaLinha(Lista* lst)
{
        int tam = 0;
        Lista* p ;

        for(p = lst; p != NULL; p = p->prox)
        {
                if(p->linha > tam)
                    tam = p->linha;
        }

        return tam + 1;
}

int calculaColuna(Lista* lst)
{
        int tam = 0;
        Lista* p ;

        for(p = lst; p != NULL; p = p->prox)
        {
                if(p->coluna > tam)
                    tam = p->coluna;
        }

        return tam + 1;
}

Lista* salvaLista(int ** matriz,  int l, int c)
{
        Lista* lst = (Lista*) malloc(sizeof(Lista));


        for(int i = 0; i < l; i++)
        {    for(int j  =0; j < c; j++)
            {
                    if(matriz[i][j] != 0)
                     {

                        lst = insere_ordenado(lst, matriz[i][j], i, j);
                     }
            }
        }

        return lst;
}


Lista* insere_ordenado(Lista* lst, int valor, int linha, int coluna)
{
        Lista* p = lst;
        Lista * ant = NULL;
        Lista * novo;

        while(p != NULL && (p->linha < linha || p->linha <= linha && p->coluna < coluna) )
        {
                ant = p;
                p = p->prox;
        }

        novo = (Lista*) malloc(sizeof(Lista));
        novo->valor = valor;
        novo-> linha = linha;
        novo->coluna = coluna;

        if(ant == NULL)
         {
                  novo->prox = lst;
                  lst = novo;
        }

        else
        {
                novo->prox = ant->prox;
                ant->prox  = novo;
        }

        return lst;
}

Lista* insere(Lista* lst, int  num, int i, int j)
{
         Lista* novo = (Lista*) malloc(sizeof(Lista));

                            novo->linha = i;
                            novo->coluna = j;
                            novo->valor = num;
                            novo->prox = lst;

            return novo;
}



int  procura(Lista*lst, int i, int j)
{
        Lista* p;

        for(p = lst; p != NULL; p = p->prox)
            if(p->linha == i && p->coluna == j)
            {
                return p->valor;
            }

           return 0;
}




void aleatoria(int l, int c , int **matriz)
{
    int i, j;

    for(i = 0; i < l; i++)
    {
        for(j = 0; j < c; j++)
        {
            matriz[i][j] = rand() % 100;
        }
    }
}

void imprimeLista(Lista* lst)
{
        Lista* p;

        for(p  = lst; p!= NULL; p = p->prox)
            if(p ->valor !=  0)
            printf("Linha: %d. Coluna: %d. Valor: %d\n", p->linha, p->coluna, p->valor);
}