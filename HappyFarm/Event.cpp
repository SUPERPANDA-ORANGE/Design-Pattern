#include "Event.h"
#include "Tool.h"

Event::Event(Farm* farm, string name) :name(name)
{
	if (farm) {
		this->farm = farm;
		farm->addEvent(this);
	}
	status = NOT_STARTED;
}

void Event::notifyMembers(string message)
{
	if (!statusChanged) {
		return;
	}
	for (auto member : members) {
		member->receiveEventMessage(message);
	}
	cleanChanged();
}

void Event::cleanChanged()
{
	statusChanged = false;
}

void Event::addMember(Animal * animal)
{
	if (!isInVector(members, animal)) {
		members.push_back(animal);
	}
}

void Event::removeMember(Animal * targetAnimal)
{
	removeVectorMember(members, targetAnimal);
}

void Event::setName(string name)
{
	this->name = name;
}

string Event::getName() const
{
	return name;
}

void Event::setEventStatus(EventStatus status)
{
	//必须按照 NOT_STARTED -> START -> ON -> END路线，或者除END外任何状态 -> END，才能引发statusChanged变化
	if ((status - this->status) == 1 || (status == END && this->status != END)) {
		this->status = status;
		statusChanged = true;
	}
}

Event::EventStatus Event::getEventStatus() const
{
	return status;
}



Olympic::Olympic(Farm * farm, string name) :Event(farm, name)
{
}

void Olympic::start()
{
	setEventStatus(EventStatus::START);
	notifyMembers("Olympic starts");
}

void Olympic::on()
{
	setEventStatus(EventStatus::ON);
	notifyMembers("Olympic is being held ");
}

void Olympic::end()
{
	setEventStatus(EventStatus::END);
	notifyMembers("Olympic ends ");
}