#ifndef CREATURE_H
#define CREATURE_H

#include "Farm.h"
#include "State.h"

using namespace std;

class Animal;
class Monster;
class Event;
class Farm;
class State;

class Creature {
public:
	enum CreatureType {
		ANIMAL, MONSTER, PLANT//����plant
	};
	Creature(CreatureType type = CreatureType::ANIMAL, Farm* farm = nullptr, string name = "");
	~Creature();
	
	string getName() const;
	void setName(string name);
	CreatureType getCreatureType() const;//������������ (ANIMAL,MONSTER)

	void setFarm(Farm* farm);
	Farm* getFarm() const;
	
	class State* curState;//����state���ģʽ
	void setState(State* s) {
		curState = s;
	}
	virtual void born();//��ӽ�state
	virtual void die();
	virtual void injure();
	virtual void recover();
	virtual void revive();

protected:
	Farm* farm;//��Creatureʵ������ũ��
	string name;
	CreatureType creatureType;
};

class Plant :public Creature 
{
public:
	enum PlantType {
		CABBAGE, GRASS, POTATO, PEA
	};
	Plant(PlantType pType) {
		this->plantType = pType;
	}
	virtual ~Plant() = 0;
	int getRefCount(){
		return ref;
	}
private:
	PlantType plantType;
	int ref;
};

class Cabbage :public Plant
{
	Cabbage();
	~Cabbage(){}
};

class Grass :public Plant
{
	Grass();
	~Grass() {}
};

class Potato :public Plant
{
	Potato();
	~Potato() {}
};

class Pea :public Plant
{
	Pea();
	~Pea() {}
};

class Animal :public Creature {
public:
	enum AnimalType
	{
		MAMMAL, REPTILE, INSECT, BIRD
	};
	Animal(Farm* farm = nullptr, string name = "");
	virtual ~Animal();

	void joinEvent(Event* event);//������¼�
	void quitEvent();//�˳��������¼�
	Event* getEvent();
	void receiveEventMessage(string message);//�յ��¼����͵���Ϣ

private:
	Event* event;
};


class Monster :public Creature {
	//Monster�����prototype,composite���ģʽ
public:
	enum MonsterType
	{
		VAMPIRE, MONSTER_CREATOR
	};
	static Monster* findAndClone(MonsterType type, Farm* farm = nullptr, string name = "");

	//�漰parent�Ĳ���Ϊcomposite���ģʽ
	//Monster����������MonsterCreator��������ӵ��vector���������������Monster������ʵ��
	//�������Ϊ�ļ�ϵͳ��MonsterCreator��ӦΪ�ļ��У�����Monster��ʵ����ӦΪ�ļ�
	//parentָ��ָ���Monster�������ڵ�vector��Ӧ��MonsterCreatorʵ��
	Monster* getParent() const;
	void setParent(Monster* parent);

protected:
	Monster(Farm* farm = nullptr, string name = "");
	virtual Monster* clone(Farm* farm = nullptr, string name = "") = 0;
	virtual MonsterType getMonsterType() const = 0;
	static void addPrototype(Monster* monster);
	MonsterType monsterType;

	Monster* parent;
private:
	static vector<Monster*> prototypes;
};

class Vampire :public Monster //Vampire-��Ѫ��
{
public:
	MonsterType getMonsterType() const;

	Monster* clone(Farm* farm = nullptr, string name = "");

	void killAnimal();//������
protected:
	Vampire(int dummy, Farm* farm = nullptr, string name = "");
private:
	static Vampire _vampire;
	Vampire();
};

class MonsterCreator :public Monster
{
public:
	MonsterType getMonsterType() const;
	//prototypeģʽ
	Monster* clone(Farm* farm = nullptr, string name = "");

	//Compositeģʽ
	void addChild(Monster* child);//���ĳMonsterʵ������children
	void removeChild(Monster* child);//�Ƴ�children��ĳMonster����ʵ��
	void printChildren() const; //��ӡ��children�еĸ���Monster����ʵ��������
protected:
	MonsterCreator(int dummy, Farm* farm = nullptr, string name = "");
private:
	static MonsterCreator _monsterCreator;
	MonsterCreator();
	vector<Monster*> children;
};

#endif