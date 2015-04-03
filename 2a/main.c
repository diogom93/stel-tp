/*
	Sistemas de Telecomunicações
	Simulação de Tráfego por Eventos Discretos - Entrega 2
	Realizado Por:
		*	Diogo Martins
		* 	Miguel Freitas
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../lista_ligada.h"

#define LAMBDA (1200.0 / 3600.0)
#define DM 180
#define START 1
#define FINISH 0

double getC();
double getD();

int main(int argc, char *argv[]) {
	double sim_t, curr_t = 0, event_time = 0;
	int sim_calls = 0, n_chan = 1, event_type, n_calls = 0, n_rej_calls = 0, channel = 0, i;
	lista *lst = NULL;
	
	srand(time(NULL));
	
	printf("Simulação de tráfego por eventos discretos.\n");
	printf("Por favor introduza o tempo de simulação (segundos): ");
	scanf("%lf", &sim_t);
	printf("Por favor introduza o nº de canais: ");
	scanf("%d", &n_chan);
	printf("A simular...\n");
	
	int channel_calls[n_chan];
	for (i = 0; i < n_chan; i++) {
		channel_calls[i] = 0;
	}
	
	lst = adicionar(lst, START, getC());
	
	while (event_time < sim_t) {
		event_type = lst->tipo;
		event_time = lst->tempo;
		lst = remover(lst);
		
		if (event_type == START) {
			lst = adicionar(lst, START, (getC() + event_time));
			if (channel < n_chan) {
				n_calls++;
				channel_calls[channel]++;
				channel++;
				lst = adicionar(lst, FINISH, (getD() + event_time));
			} else {
				n_calls++;
				n_rej_calls++;
			}
		} else {
			channel--;
		}
	}

	printf("Probabilidade de perda de chamadas: %f%%\n", ((double) n_rej_calls / n_calls) * 100);
	for (i = 0; i < n_chan; i++) {
		printf("Probabilidade de utilização do canal %d: %f%%\n", i, ((double) channel_calls[i] / n_calls) * 100);
	}
	
	return 0;
}

double getC() {
	double u;
	
	u = (double) (rand() + 1) / (RAND_MAX + 1.0) ;

	return -(1.0 / LAMBDA) * log(u);
}

double getD() {
	double u;
	
	u = (double) (rand() + 1) / (RAND_MAX + 1.0);
	return -DM * log(u);
}