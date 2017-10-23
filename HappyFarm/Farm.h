#ifndef FARM_H
#define FARM_H

#include <string>
#include <vector>
#include <iostream>
#include "Creature.h"
#include "Event.h"


using namespace std;

#define LARGE_FARM_SIZE 50
#define MIDDLE_FARM_SIZE 30
#define SMALL_FARM_SIZE 10

class Creature;
class Animal;
class Monster;
class Event;

class Farm {
public:
	enum FarmSize {
		LARGE, MIDDLE, SMALL
	};
	Farm();
	Farm(int maxSize);
	~Farm();

	static int count;//农场计数器
	int getId() const;//得到农场id
	static Farm* createFarmBySize(FarmSize size);//工厂函数，创建农场

	void addCreature(Creature* newCreature);//添加Animal或Monster实例进入对应Vector

	void addMonster(Monster* newMonster);//添加Monster实例进入对应Vector
	void removeMonster(Monster* targetMonster);//移除Vector中的指定Monster实例
	void removeAndFreeMonster(Monster* targetMonster);//移除Vector中的指定Monster实例，并释放内存
	int getMonstersCount() const;//得到该农场Monster实例数量

	void addEvent(Event* newEvent);//添加Event实例进入对应Vector
	void removeAndFreeEvent(Event* targetEvent);//移除Vector中指定的Event实例，并释放内存
	int CountAndCleanEvents();//得到该农场当前Event实例的数量，也负责清除已经结束的Events

	void addAnimal(Animal* newAnimal);//添加Aniaml实例进入对应Vector
	void removeAnimal(Animal* targetAnimal);//移除Vector中的指定Animal实例
	void removeAndFreeAnimal(Animal* targetAnimal);//移除Vector中指定的Animal实例，并释放内存
	int getAnimalCount() const;//得到该农场Animal实例的数量
	
private:
	vector<Monster*> monsters;
	vector<Event*> events;
	vector<Animal*> animals;
	int id;
	const int maxSize;//Animal实例的最大数量
};

class LargeFarm :public Farm
{
public:
	LargeFarm();
};

class MiddleFarm :public Farm
{
public:
	MiddleFarm();
};

class SmallFarm :public Farm
{
public:
	SmallFarm();
};

#endif