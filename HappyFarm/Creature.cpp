#include "Creature.h"
#include "Tool.h"

Creature::Creature(CreatureType type, Farm * farm, string name) :
	name(name), creatureType(type)
{
	this->farm = nullptr;
	if (farm) {
		farm->addCreature(this);
	}
}

Creature::~Creature()
{
}

void Creature::born()
{
	cout << name << " is borned" << endl;

	curState->getHealthy(this);
}

void Creature::injure()
{
	cout << name << " is injured" << endl;

	curState->getSick(this);
}

void Creature::recover()
{
	cout << name << " is recovered" << endl;

	curState->getHealthy(this);
}

void Creature::die()
{
	cout << name << "is dead" << endl;

	curState->goDie(this);
}

void Creature::revive()
{
	cout << name << " is reived" << endl;

	curState->getHealthy(this);
}

string Creature::getName() const
{
	return name;
}

void Creature::setName(string name)
{
	this->name = name;
}

Creature::CreatureType Creature::getCreatureType() const
{
	return creatureType;
}

void Creature::setFarm(Farm * farm)
{
	if (farm) {
		switch (creatureType)
		{
		case ANIMAL:
			if (this->farm) {
				this->farm->removeAnimal((Animal*)this);
			}
			farm->addAnimal((Animal*)this);
			break;
		case MONSTER:
			if (this->farm) {
				this->farm->removeMonster((Monster*)this);
			}
			farm->addMonster((Monster*)this);
			break;
		default:
			break;
		}
		this->farm = farm;
	}
}

Farm * Creature::getFarm() const
{
	return farm;
}


Animal::Animal(Farm * farm, string name) :Creature(CreatureType::ANIMAL, farm, name)
{
	this->event = nullptr;
}

Animal::~Animal()
{
}

void Animal::joinEvent(Event * event)
{
	if (event) {
		if (this->event) {
			quitEvent();
		}
		this->event = event;
		event->addMember(this);
	}
}

void Animal::quitEvent()
{
	if (this->event) {
		cout << name + " quits event " + this->event->getName() << endl;
		event->removeMember(this);
		this->event = nullptr;
	}
}

Event * Animal::getEvent()
{
	return event;
}

void Animal::receiveEventMessage(string message)
{
	cout << getName() << " receive the message: " << message << " in Event:" << getEvent()->getName() << endl;
	if (event->getEventStatus() == Event::EventStatus::END) {
		quitEvent();
	}
}


vector<Monster*> Monster::prototypes;


Monster * Monster::findAndClone(MonsterType type, Farm* farm, string name)
{
	for (auto monster : prototypes) {
		if (monster->getMonsterType() == type) {
			return monster->clone(farm, name);
		}
	}
	return nullptr;
}

Monster * Monster::getParent() const
{
	return parent;
}

void Monster::setParent(Monster * parent)
{
	this->parent = parent;
}

Monster::Monster(Farm * farm, string name) :Creature(CreatureType::MONSTER, farm, name)
{
	parent = nullptr;
}

void Monster::addPrototype(Monster * monster)
{
	prototypes.push_back(monster);
}

Vampire Vampire::_vampire;

Vampire::Vampire(int dummy, Farm * farm, string name) :Monster(farm, name)
{
	monsterType = MonsterType::VAMPIRE;
}

Vampire::Vampire()
{
	monsterType = MonsterType::VAMPIRE;
	addPrototype(this);
}

Monster::MonsterType Vampire::getMonsterType() const
{
	return Monster::MonsterType::VAMPIRE;
}

Monster * Vampire::clone(Farm* farm, string name)
{
	return new Vampire(1, farm, name);
}

void Vampire::killAnimal()
{
	cout << "kill a animal" << endl;
}



MonsterCreator MonsterCreator::_monsterCreator;

MonsterCreator::MonsterCreator()
{
	monsterType = MonsterType::MONSTER_CREATOR;
	addPrototype(this);
}

MonsterCreator::MonsterCreator(int dummy, Farm * farm, string name) :Monster(farm, name)
{
	monsterType = MonsterType::MONSTER_CREATOR;
}

Monster::MonsterType MonsterCreator::getMonsterType() const
{
	return MONSTER_CREATOR;
}

Monster * MonsterCreator::clone(Farm * farm, string name)
{
	return new MonsterCreator(1, farm, name);
}

void MonsterCreator::addChild(Monster * child)
{
	if (child && !isInVector(children, child)) {
		if (child->getParent()) {
			((MonsterCreator*)child->getParent())->removeChild(child);
		}
		child->setParent(this);
		children.push_back(child);
	}
}

void MonsterCreator::removeChild(Monster * child)
{
	removeVectorMember(children, child);
	child->setParent(nullptr);
}

void MonsterCreator::printChildren() const
{
	cout << "Monster creator: " + getName() + "'s Children: ";
	for (auto child : children) {
		cout << child->getName()+" ";
	}
	cout << endl;
}