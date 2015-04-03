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
	double sim_t, curr_t = 0, event_time = 0, delay_t = 0, sum_delay_t = 0;
	int sim_calls = 0, n_chan = 1, event_type, n_calls = 0, n_delayed_calls = 0, channel = 0, histogram[100] = {0}, t_scale[100] = {0}, index = 0, i;
	lista *lst = NULL, *queue = NULL;
	FILE *f;
	
	srand(time(NULL));
	
	f = fopen("output.csv", "w");
	if (f == NULL) {
		printf("Erro ao criar ficheiro!\n");
		return -1;
	}
	
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
				n_delayed_calls++;
				queue = adicionar(queue, START, event_time);
			}
		} else {
			channel--;
			
			if (queue != NULL) {
				delay_t = event_time - queue->tempo;
				sum_delay_t = sum_delay_t + delay_t;
				queue = remover(queue);
				lst = adicionar(lst, FINISH, (getD() + event_time));
				channel_calls[channel]++;
				channel++;
				
				index = (int) (delay_t / 2);
				if (index < 100) {
					histogram[index]++;
				}
			}
		}
	}

	printf("Probabilidade de atraso: %f%%\n", ((double) n_delayed_calls / n_calls) * 100);
	printf("Média do tempo de atraso: %fs\n", (sum_delay_t / n_calls));
	for (i = 0; i < n_chan; i++) {
		printf("Probabilidade de utilização do canal %d: %f%%\n", i, ((double) channel_calls[i] / n_calls) * 100);
	}
	
	t_scale[0] = 0;
	for (i = 1; i < 100; i++) {
		t_scale[i] = t_scale[i-1] + 2;
	}
	
	for (i = 0; i < 100; i++) {
		fprintf(f, "%d;%d\n", t_scale[i], histogram[i]);
	}
	
	fclose(f);
	
	system("python3 histogram.py");
	
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