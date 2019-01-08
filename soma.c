#include <stdio.h>
#include <stdlib.h>

typedef struct lista Lista;

struct lista{

        int linha;
        int coluna;
        int valor;
        Lista* prox;
};

typedef struct posicao LPosicao;
struct posicao{
    int linha;
    int coluna;
    LPosicao* prox;
};

Lista* insere(Lista* lst, int  num, int i, int j);
Lista* salvaLista(int ** matriz, int l, int c);
Lista* soma(LPosicao* guarda, Lista* lista1, Lista* lista2);
Lista* lst_retira(Lista* lst, int val);
Lista* removeNos(Lista* lst);

LPosicao* salvaPosicoes(LPosicao* guarda, Lista* lista);
LPosicao* lst_insere_ordenado(LPosicao* lst, int linha, int coluna);

void imprimeLista(Lista* lst);
void aleatoria(int l, int c , int **matriz);
int  procuraPosicao(LPosicao*lst, int i, int j);
int procura(Lista *lst, int i, int j);

int main()
{

        int **matriz, **matriz2;
        int l1, c1, l2, c2;

        printf("Digite o número de linhas e colunas da matriz 1\n");
        scanf("%d %d", &l1 , &c1);

        printf("Digite o número de linhas e colunas da matriz 2\n");
        scanf("%d %d", &l2 , &c2);

        if (c1 != c2 && l1 != l2)
             printf("Não é possível somar estas matrizes. (c1 != c2 && l1 != l2) \n");


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



                LPosicao* guarda = (LPosicao*) malloc(sizeof(LPosicao));

                guarda = salvaPosicoes(guarda, lista1);
               guarda = salvaPosicoes(guarda, lista2);



                 Lista* lista3 = soma(guarda, lista1, lista2);

                imprimeLista(lista3);


                free(matriz);
                free(matriz2);


    return 0;
}


Lista* soma(LPosicao* guarda, Lista* lista1, Lista* lista2)
{
        LPosicao * p;
        Lista* lista3 = (Lista*) malloc(sizeof(Lista));

        for(p = guarda; p != NULL; p = p->prox)
        {
                lista3 = insere( lista3, (procura(lista1, p->linha, p->coluna) + procura(lista2, p->linha, p->coluna)), p->linha, p->coluna );
        }

        return lista3;
}


Lista* salvaLista(int ** matriz,  int l, int c)
{
        Lista* lst = (Lista*) malloc(sizeof(Lista));


        for(int i = 0; i < l; i++)
        {    for(int j  =0; j < c; j++)
            {
                    if(matriz[i][j] != 0)
                     {

                        lst = insere(lst, matriz[i][j], i, j);
                     }
            }
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


int  procuraPosicao(LPosicao*lst, int i, int j)
{
        LPosicao* p;

        for(p = lst; p != NULL; p = p->prox)
            if(p->linha == i && p->coluna == j)
            {
                return 1;
            }

           return 0;
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


LPosicao* salvaPosicoes(LPosicao* guarda, Lista* lista)
{
        Lista * p;

        for(p = lista; p != NULL; p  = p->prox)
        {
                if(!procuraPosicao(guarda, p->linha, p->coluna))
                {
                        guarda = lst_insere_ordenado(guarda, p->linha , p->coluna);
                }
        }

        return guarda;
}




LPosicao* lst_insere_ordenado(LPosicao* lst, int linha, int coluna)
{
        LPosicao* p = lst;
        LPosicao * ant = NULL;
        LPosicao * novo;

      while(p != NULL && (p->linha < linha || p->linha <= linha && p->coluna < coluna) )
        {
                ant = p;
                p = p->prox;
        }

        novo = (LPosicao*) malloc(sizeof(LPosicao));
        novo->linha = linha;
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
           if(p->valor != 0)
            printf("Linha: %d. Coluna: %d. Valor: %d\n", p->linha, p->coluna, p->valor);
}
