#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da lista
typedef struct{
	int tipo;
	double tempo;
	double tempo_f;
	struct lista * proximo;
} lista;

lista * remover (lista * apontador);
lista * adicionar (lista * apontador, int n_tipo, double n_tempo, double tempo_f);
void imprimir (lista * apontador);
