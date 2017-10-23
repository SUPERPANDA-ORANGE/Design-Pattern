#ifndef EVENT_H
#define EVENT_H

#include "Creature.h"
#include "Farm.h"

class Animal;
class Farm;

using namespace std;

class Event
{
public:
	enum EventStatus
	{
		NOT_STARTED = 0, START = 1, ON = 2, END = 3
	};
	Event(Farm* farm = nullptr, string name = "");

	bool statusChanged = false;

	virtual void start() = 0;
	virtual void on() = 0;
	virtual void end() = 0;

	virtual void notifyMembers(string message);
	void cleanChanged();
	void addMember(Animal* animal);
	void removeMember(Animal* ratgetAnimal);

	void setName(string name);
	string getName() const;


	void setEventStatus(EventStatus status);
	EventStatus getEventStatus() const;

private:
	EventStatus status;
	vector<Animal*>members;
	string name;
	Farm* farm;
};

class Olympic :public Event
{
public:
	Olympic(Farm* farm = nullptr, string name = "Olympic");
	void start();
	void on();
	void end();
};

#endif