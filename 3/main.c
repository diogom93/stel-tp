/*
	Sistemas de Telecomunicações
	Simulação de Tráfego por Eventos Discretos - Entrega 3
	Realizado Por:
		*	Diogo Martins
		* 	Miguel Freitas
*/

#include <math.h>
#include <time.h>
#include "../lista_ligada.h"

#define LAMBDA 1.2
#define DM 180
#define DM_C 2
#define DM_P 3
#define START 1
#define FINISH 0
#define CONVERSATION 2
#define PAUSE 3
#define DELTA 0.1

double getC();
double getD(double dm);
lista* creator(lista* lst, int type, double c_time, double e_time);

int main(int argc, char *argv[]) {
	int i = 0;
	int q_full = 0;
	double n_calls = 0, calls = 0, curr_calls = 0;
	double q_size = 0, q_ocup = 0;
	double bits_p = 0, bits_c = 0;
	double lost_bits_p = 0, lost_bits_c = 0;
	double sim_t = 0, curr_t = 0, prev_t = 0, e_time = 0;
	double channel_cap = 0, i_cap = 0, p_cap = 0, c_cap = 0, avg_c = 0;
	double c_packets = 0, p_packets = 0;
	lista *lst = NULL;
		
	srand(time(NULL));
	
	printf("Simulação de tráfego por eventos discretos.\n");
	printf("Por favor introduza o nº de chamadas a simular: ");
	scanf("%lf", &n_calls);
	printf("Por favor introduza o débito do canal (Kbit/s): ");
	scanf("%lf", &channel_cap);
	printf("Por favor introduza o tamanho da fila de espera (bit): ");
	scanf("%lf", &q_size);
	printf("A simular...\n");
	
	for (int j = 0; j < 50; j++) {
		lst = creator(lst, START, 0, 0);
	}
	
	while (1) {
		prev_t = curr_t;
		curr_t = lst->tempo;
		
		if (curr_t == lst->tempo_f) {
			if (lst->tipo == CONVERSATION) {
				i_cap -= 1.104;
				p_cap -= 1.104;
				p_packets -= 3;
			} else if (lst->tipo == PAUSE) {
				i_cap -= 17.2;
				c_cap -= 17.2;
				c_packets -= 25;
			}
			
			curr_calls--;
			lst = remover(lst);
			if (calls < n_calls) {
				lst = creator(lst, START, curr_t, 0);
			}
			
		} else if (lst->tipo == START) {
			curr_calls++;
			calls++;
			int r = rand() % 2;
			
			if (r == 0) {
				i_cap += 17.2;
				c_cap += 17.2;
				c_packets += 25;
				e_time = lst->tempo_f;
				lst = remover(lst);
				lst = creator(lst, PAUSE, curr_t, e_time);
				
			} else {
				i_cap += 1.104;
				p_cap += 1.104;
				p_packets += 3;
				e_time = lst->tempo_f;
				lst = creator(lst, CONVERSATION, curr_t, e_time);
			}
			
		} else if (lst->tipo == CONVERSATION) {
			i_cap += 16.096;
			c_cap += 17.2;
			p_cap -= 1.104;
			c_packets += 25;
			p_packets -= 3;
			e_time = lst->tempo_f;
			lst = remover(lst);
			lst = creator(lst, PAUSE, curr_t, e_time);
			
		} else if (lst->tipo == PAUSE) {
			i_cap -= 16.096;
			c_cap -= 17.2;
			p_cap += 1.104;
			c_packets -= 25;
			p_packets += 3;
			e_time = lst->tempo_f;
			lst = remover(lst);
			lst = creator(lst, CONVERSATION, curr_t, e_time);
		}
		
		if (curr_calls > 0) {
			avg_c = avg_c + (i_cap / curr_calls);
		}
		
		q_ocup += (curr_t - prev_t) * (i_cap - channel_cap);
		if (q_ocup > q_size) {
			q_full = 1;
		} else if (q_ocup <= 0) {
			q_ocup = 0;
			q_full = 0;
		} else {
			q_full = 0;
		}
		
		if (q_full == 1) {
			lost_bits_c += (q_ocup - q_size) * (c_cap / i_cap) * 1024;
			lost_bits_p += (q_ocup - q_size) * (p_cap / i_cap) * 1024;
			q_ocup = q_size;
		}
		
		bits_c += (curr_t - prev_t) * c_cap * 1024;
		bits_p += (curr_t - prev_t) * p_cap * 1024;
		
		i++;
		
		if (lst == NULL) {
			break;
		}

	}
	
	printf("Débito médio: %.2lf Kbit/s\n", avg_c / i);
	printf("Nº total de bits: %.2lf Mbit/s\n", (bits_c + bits_p) / (1024 * 1024));
	printf("Nº total de pacotes de voz: %.0lf Milhões de pacotes\n", (bits_c / (86 * 8)) / 1000000);
	printf("Nº total de pacotes de pausa: %.0lf Milhões de pacotes\n", (bits_p / (46 * 8)) / 1000000);
	printf("Nº de bits perdidos: %.2lf Mbit/s\n", (lost_bits_c + lost_bits_p) / (1024 * 1024));
	printf("Nº de pacotes de voz perdidos: %.0lf Milhões de pacotes\n", (lost_bits_c / (86 * 8)) / 1000000);
	printf("Nº de pacotes de pausa perdidos: %.0lf Milhões de pacotes\n", (lost_bits_p / (46 * 8)) / 1000000);
	printf("Taxa de perda de pacotes de voz: %.2lf%%\n", ((lost_bits_c / (86 * 8)) / (bits_c / (86 * 8))) * 100);
		
	return 0;
}

double getC() {
	double u;
	
	u = (double) (rand() + 1) / (RAND_MAX + 1.0) ;

	return -(1.0 / LAMBDA) * log(u);
}

double getD(double dm) {
	double u;
	
	u = (double) (rand() + 1) / (RAND_MAX + 1.0);
	
	return -dm * log(u);
}

lista* creator(lista* lst, int type, double c_time, double e_time) {
	double s_time = 0, d_time = 0;
	
	if (type == START) {
		s_time = getC();
		d_time = getD(DM);
		return lst = adicionar(lst, START, s_time + c_time, c_time + s_time + d_time);
		
	} else if (type == CONVERSATION) {
		d_time = getD(DM_P);
		
		if (c_time + d_time > e_time) {
			return lst = adicionar(lst, CONVERSATION, e_time, e_time);
		} else {
			return lst = adicionar(lst, CONVERSATION, c_time + d_time, e_time);
		}
	} else {
		d_time = getD(DM_C);
		
		if (c_time + d_time > e_time) {
			return lst = adicionar(lst, PAUSE, e_time, e_time);
		} else {
			return lst = adicionar(lst, PAUSE, c_time + d_time, e_time);
		}
	}
}