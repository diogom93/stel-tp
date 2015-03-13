//
// Event.cpp
// Created by Diogo Martins on 12/03/15.

#include "Event.h"

Event::Event(double time, types type) {
	Event::time = time;
	Event::type = type;
}

double Event::getTime() {
	return time;
}

types Event::getType() {
	return type;
}