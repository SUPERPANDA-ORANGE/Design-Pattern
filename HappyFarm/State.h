#ifndef STATE_H
#define STATE_H

#include "Creature.h"

using namespace std;

class  State
{
public:
	virtual void getSick(Creature *c) {
		printf("State: already sick!");
	}

	virtual void getHealthy(Creature *c) {
		printf("State: already healthy!");
	}

	virtual void goDie(Creature *c) {
		printf("State: already dead!");
	}

	virtual void revive(Creature *c) {
		printf("State: already alive!");
	}
};

class Healthy : public State
{
public:
	Healthy() {

	}

	~Healthy() {

	}

	void getSick(Creature *c);
};

class Sick : public State
{
public:
	Sick() {

	}

	~Sick() {

	}

	void getHealthy(Creature *c);

	void goDie(Creature *c);
};

class Dead : public State
{
public:
	Dead() {

	}

	~Dead() {

	}

	void revive(Creature *c);
};
#endif