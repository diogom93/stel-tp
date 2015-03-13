#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista_ligada.h"

#define LAMBDA 8

double getC();

int main(int argc, char *argv[]) {
	double sim_t = 0, curr_time = 0, c_avg = 0, next_c = 0;
	int n_samples = 0;
	lista * event_list = NULL;
	
	printf("Tempo de simulação: ");
	scanf("%lf", &sim_t);
	printf("A simular...\n");
	
	while (curr_time < sim_t) {
		c_avg += next_c;
		n_samples++;
		event_list = adicionar(event_list, 1, curr_time);
		next_c = getC();			
		curr_time += next_c;
	}
	
	c_avg = c_avg / n_samples;
	printf("Média C: %lf\n", c_avg);
	
	return 0;
}

double getC() {
	double u;
	
	u = (double) (rand() + 1) / RAND_MAX;
	
	return -(1.0 / LAMBDA) * log(u);
}