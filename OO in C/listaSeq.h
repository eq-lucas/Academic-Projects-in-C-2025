#ifndef LISTASEQ_H
#define LISTASEQ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct lista Lista;


Lista* lista_criar();

bool lista_anexar(int elemento, Lista* lista);

bool lista_inserir(int elemento, int pos, Lista* lista);

void lista_print(Lista* lista);

#endif