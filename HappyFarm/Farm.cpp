#include "Farm.h"
#include "Tool.h"

int Farm::count = 0;

Farm::Farm():id(count),maxSize(MIDDLE_FARM_SIZE)
{
	++count;
}

Farm::Farm(int size):id(count),maxSize(size)
{
}

Farm::~Farm()
{
	freeVector<Animal>(animals);
	freeVector<Event>(events);
	freeVector<Monster>(monsters);
}

int Farm::getId() const
{
	return id;
}

Farm * Farm::createFarmBySize(FarmSize size)
{
	switch (size) {
	case LARGE:
		return new LargeFarm();
	case MIDDLE:
		return new MiddleFarm();
	case SMALL:
		return new SmallFarm();
	default:
		return new MiddleFarm();
	}
}

void Farm::addCreature(Creature * newCreature)
{
	switch (newCreature->getCreatureType())
	{
	case Creature::CreatureType::ANIMAL:
		addAnimal((Animal*)newCreature);
		break;
	case Creature::CreatureType::MONSTER:
		addMonster((Monster*)newCreature);
		break;
	default:
		break;
	}
}

void Farm::addMonster(Monster * newMonster)
{
	//如果该Monster实例已经存在在某农场，需要将该农场中清除该Monster实例
	//即Monster实例只能出现在一个农场
	if (newMonster->getFarm()) {
		newMonster->getFarm()->removeMonster(newMonster);
	}
	//判断是否重复添加
	if (!isInVector(monsters, newMonster)) {
		monsters.push_back(newMonster);
		newMonster->setFarm(this);
	}
}

void Farm::removeMonster(Monster * targetMonster)
{
	removeVectorMember(monsters, targetMonster);
}

void Farm::removeAndFreeMonster(Monster * targetMonster)
{
	removeAndFreeVectorMember(monsters, targetMonster);
}

int Farm::getMonstersCount() const
{
	return monsters.size();
}

void Farm::addEvent(Event * newEvent)
{
	//避免重复添加事件
	if (newEvent && !isInVector(events, newEvent)) {
		events.push_back(newEvent);
	}
}

void Farm::removeAndFreeEvent(Event* targetEvent) 
{
	removeAndFreeVectorMember(events, targetEvent);
}

int Farm::CountAndCleanEvents()
{
	int count=0;
	for (vector<Event*>::iterator iter = events.begin(); iter != events.end();) {
		if ((*iter)->getEventStatus() != Event::EventStatus::END) {
			++count;
			++iter;
		}
		else {
			cout << "***************  Free " << (*iter)->getName() << endl;
			delete(*iter);
			iter = events.erase(iter);
		}
	}
	return count;
}

void Farm::addAnimal(Animal * newAnimal)
{
	//如果该Animal实例已经存在在某农场，需要将该农场中该实例清除
	//即Animal实例只能存在在一个农场
	if (newAnimal->getFarm()) {
		newAnimal->getFarm()->removeAnimal(newAnimal);
	}
	//Animal实例数量具有上限
	if (newAnimal && getAnimalCount() < maxSize && !isInVector(animals, newAnimal)) {
		animals.push_back(newAnimal);
		newAnimal->setFarm(this);
	}
}

void Farm::removeAnimal(Animal * targetAnimal)
{
	removeVectorMember(animals, targetAnimal);
}

void Farm::removeAndFreeAnimal(Animal * targetAnimal)
{
	removeAndFreeVectorMember(animals, targetAnimal);
}

int Farm::getAnimalCount() const
{
	return animals.size();
}

LargeFarm::LargeFarm() :Farm(LARGE_FARM_SIZE)
{
}

MiddleFarm::MiddleFarm() : Farm(MIDDLE_FARM_SIZE)
{
}

SmallFarm::SmallFarm() : Farm(SMALL_FARM_SIZE)
{
}