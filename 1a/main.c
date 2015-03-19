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

double getC();

int main(int argc, char *argv[]) {
	double sim_t = 0, curr_time = 0, c_avg = 0, next_c = 0, t_scale[15] = {0};;
	int n_samples = 0, hist[20] = {0}, i;
	FILE *f;
	
	srand(time(NULL));
	
	f = fopen("output.csv", "w");
	if (f == NULL) {
		printf("Erro ao criar ficheiro!\n");
		return -1;
	}
	
	for (i = 1 ; i < 15; i++) {
		t_scale[i] = t_scale[i-1] + 0.1;
	}
	
	printf("Simulação de tráfego por eventos discretos.\n");
	printf("Por favor introduza tempo de simulação (segundos): ");
	scanf("%lf", &sim_t);
	printf("A simular...\n");
	
	while (curr_time < sim_t) {
		c_avg += next_c;
		next_c = getC();			
		curr_time += next_c;
		n_samples++;
		hist[(int) floor(next_c / 0.1)]++;
	}
	
	c_avg = c_avg / n_samples;
	printf("Simulação concluída. Foram simuladas %d chamadas.\n", n_samples);
	
	for (int i = 0; i < 15; i++) {
		fprintf(f, "%lf;%d\n", t_scale[i], hist[i]);
	}
	
	printf("Média do intervalo entre chamadas: %lf\n", c_avg);
	
	fclose(f);
	
	system("python3 histogram.py");
	
	return 0;
}

double getC() {
	double u;
	
	u = (double) (rand() + 1) / RAND_MAX;

	return -(1.0 / LAMBDA) * log(u);
}