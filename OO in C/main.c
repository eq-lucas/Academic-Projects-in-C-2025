#include <stdio.h>
#include <stdlib.h>
#include "listaSeq.h"


int main()
{
    Lista* l1= lista_criar(); // [] // conceitualmetne, explicando para um macaco, mas especificametne esta com lixo



    lista_anexar(1,l1); // [1]
    lista_anexar(2,l1); // [1,2]
    lista_anexar(3,l1); // [1,2,3]

    lista_print(l1); // [1,2,3]

//int x = lista_elemento(0,l1) quero pegar o valor da lista l1 na posicao 0, mas assim ficac omplicado se n existir o vlaor devolver -1 fica meio ruim, entao:

int x;
int pos; // endereco de memorai onde quero q armaze este elemento
//lista_elemento(10,l1,&pos); // aqui apssa o endereco da variavel pos e consigo manipular com isto dentro de um if:
//if (lista_elemento(10,l1,&pos)){
//    ...
//}



//lista_inserir(50,0,l1);  // [50,1,2,3]
//lista_inserir(30,2,l1);  // [50,1,30,2,3]
//lista_inserir(30,5,l1);  // [50,1,30,2,3,0] 
//                         // neste contexto q ja foi craido com 10 posicoes n tem
//                         // rpoblema colocar numa posicao q ainda n existe na lista
//
//
//lista_print(l1); // [50,1,30,2,3,0] 


    return 0;
}
