#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listaSeq.h"

// usando struct lista aqui dentro do .c e deixando so a especificacao no .h, assim podemos criar outro .h com outra forma de estrutura da struct...

struct lista {
    int* ponteiroArray; // nesta nova versao agr vamos fazer um array de tamanho que desejar
    int qtde;
    int tamanho;
}; 

Lista* lista_criar(){

    int tamanho=10;

    Lista* novalista = (Lista*) malloc(sizeof(Lista));

    novalista->ponteiroArray= (int*)calloc(tamanho,sizeof(int)); // este vetor q o calloc ta criando eh um array de tamanho TAMANHO e devolve o endereco deste array
    novalista->tamanho=10;
    novalista->qtde=0;

    return novalista;
}



bool lista_anexar(int elemento, Lista* lista){ // agora Lista eh uma struct lista e assim eh um atalho por conta do typedef, e estamos esperando receber aqui um Lista* 

lista->ponteiroArray[lista->qtde]= elemento;
lista->qtde++;
return true;

}



void lista_print(Lista* lista){

printf("[");

for(int i =0;i< lista->qtde;i++)
{
    printf("%d", lista->ponteiroArray[i]);
    
    if( i < lista->qtde -1)
    {
        printf(",");
    }
}

printf("]");


}



bool lista_inserir(int elemento,int pos, Lista* lista){

}