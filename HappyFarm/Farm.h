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

	static int count;//ũ��������
	int getId() const;//�õ�ũ��id
	static Farm* createFarmBySize(FarmSize size);//��������������ũ��

	void addCreature(Creature* newCreature);//���Animal��Monsterʵ�������ӦVector

	void addMonster(Monster* newMonster);//���Monsterʵ�������ӦVector
	void removeMonster(Monster* targetMonster);//�Ƴ�Vector�е�ָ��Monsterʵ��
	void removeAndFreeMonster(Monster* targetMonster);//�Ƴ�Vector�е�ָ��Monsterʵ�������ͷ��ڴ�
	int getMonstersCount() const;//�õ���ũ��Monsterʵ������

	void addEvent(Event* newEvent);//���Eventʵ�������ӦVector
	void removeAndFreeEvent(Event* targetEvent);//�Ƴ�Vector��ָ����Eventʵ�������ͷ��ڴ�
	int CountAndCleanEvents();//�õ���ũ����ǰEventʵ����������Ҳ��������Ѿ�������Events

	void addAnimal(Animal* newAnimal);//���Aniamlʵ�������ӦVector
	void removeAnimal(Animal* targetAnimal);//�Ƴ�Vector�е�ָ��Animalʵ��
	void removeAndFreeAnimal(Animal* targetAnimal);//�Ƴ�Vector��ָ����Animalʵ�������ͷ��ڴ�
	int getAnimalCount() const;//�õ���ũ��Animalʵ��������
	
private:
	vector<Monster*> monsters;
	vector<Event*> events;
	vector<Animal*> animals;
	int id;
	const int maxSize;//Animalʵ�����������
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