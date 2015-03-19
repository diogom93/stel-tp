/*
	Sistemas de Telecomunicações
	Simulação de Tráfego por Eventos Discretos - Entrega 1
	Realizado Por:
		*	Diogo Martins
		* 	Miguel Freitas
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../lista_ligada.h"

#define LAMBDA 8
#define DELTA (1.0/(100*LAMBDA))

double getC();

int main(int argc, char *argv[]) {
	double sim_t = 0, curr_time = 0, c_time = 0, c_avg = 0, next_c = 0, t_scale[15] = {0};
	int n_samples = 0, hist[15] = {0}, i;
	FILE *f;
	
	srand(time(NULL));
	
	f = fopen("output.csv", "w");
	if (f == NULL) {
		printf("Erro ao criar ficheiro!\n");
		return -1;
	}
	
	for (i = 1; i < 15; i++) {
		t_scale[i] = t_scale[i-1] + 0.1;
	}
	
	printf("Simulação de tráfego por eventos discretos.\n");
	printf("Por favor introduza tempo de simulação (segundos): ");
	scanf("%lf", &sim_t);
	printf("A simular...\n");
	
	while (curr_time < sim_t) {
		curr_time += DELTA;
		next_c = getC();		
		if (next_c < LAMBDA*DELTA) {
			hist[(int) floor(c_time / 0.1)]++;
			c_avg = c_avg + c_time;
			c_time = 0;
			n_samples++;
		} else {
			c_time = c_time + DELTA;
		}
	}
	
	c_avg = c_avg / n_samples;
	
	printf("Simulação concluída. Foram simuladas %d chamadas.\n", n_samples);
	
	for (int i = 0; i < 15; i++) {
		fprintf(f, "%lf;%d\n", t_scale[i], hist[i]);
	}
	
	printf("Média do intervalo entre chamadas: %lf\n", c_avg);
	
	fclose(f);
	
	return 0;
}

double getC() {
	double u;
	
	u = (double) (rand() + 1) / RAND_MAX;

	return u;
}