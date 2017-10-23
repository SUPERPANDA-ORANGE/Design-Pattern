#include "State.h"

/*
**class Healthy
*/

void Healthy::getSick(Creature *c) 
{
	printf("%s is going from HEALTHY to SICK", c->getName());

	c->setState(new Sick());

	delete this;
}

/*
**class Sick
*/

void Sick::getHealthy(Creature *c) 
{
	printf("%s is going from SICK to HEALTHY", c->getName());

	c->setState(new Healthy());

	delete this;
}

void Sick::goDie(Creature *c)
{
	printf("%s is going from SICK to DEAD", c->getName());

	c->setState(new Dead());

	delete this;
}

/*
**class Dead
*/

void Dead::revive(Creature *c) 
{
	printf("%s is going from DEAD to HEALTHY", c->getName());

	c->setState(new Healthy());

	delete this;
}