#include <iostream>
#include <cstdlib>
#include <cmath>
#include <list>
#include "Event.h"

#define LAMBDA 8

using namespace std;

double getC();

int main(int argc, char *argv[]) {
	double sim_t = 0, curr_time = 0, c_avg = 0, next_c = 0;
	int n_samples = 0;
	list<Event> list;
	
	cout << "Please input simulation time: ";
	cin >> sim_t;
	cout << "Simulating..." << endl;
	
	while (curr_time < sim_t) {
		Event event(curr_time, start);
		list.push_front(event);
		list.sort();
		c_avg += next_c;
		n_samples++;
		
		next_c = getC();
		curr_time += next_c;
	}
	
	c_avg = c_avg / n_samples;
	
	
	return 0;
}

double getC() {
	double u;
	
	srand(time(NULL));
	
	u = (double) (rand() + 1) / RAND_MAX;
	
	return -(1.0 / LAMBDA) * log(u);
}