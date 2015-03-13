//
// Event.h
// Created by Diogo Martins on 12/03/15.

#ifndef _Event_h_
#define _Event_h_

enum types {
	start, finish
};

class Event {
	private:
		double time;
		types type;
		
	public:
		Event(double time, types type);
		double getTime();
		types getType();
};

#endif