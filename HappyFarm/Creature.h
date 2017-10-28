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
		ANIMAL, MONSTER, PLANT//新增plant
	};
	Creature(CreatureType type = CreatureType::ANIMAL, Farm* farm = nullptr, string name = "");
	~Creature();
	
	string getName() const;
	void setName(string name);
	CreatureType getCreatureType() const;//返回生物类型 (ANIMAL,MONSTER)

	void setFarm(Farm* farm);
	Farm* getFarm() const;
	
	class State* curState;//采用state设计模式
	void setState(State* s) {
		curState = s;
	}
	virtual void born();//添加进state
	virtual void die();
	virtual void injure();
	virtual void recover();
	virtual void revive();

protected:
	Farm* farm;//该Creature实例所处农场
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

	void joinEvent(Event* event);//加入该事件
	void quitEvent();//退出所处的事件
	Event* getEvent();
	void receiveEventMessage(string message);//收到事件发送的信息

private:
	Event* event;
};


class Monster :public Creature {
	//Monster类采用prototype,composite设计模式
public:
	enum MonsterType
	{
		VAMPIRE, MONSTER_CREATOR
	};
	static Monster* findAndClone(MonsterType type, Farm* farm = nullptr, string name = "");

	//涉及parent的部分为composite设计模式
	//Monster将衍生子类MonsterCreator，该子类拥有vector容器，可用于添加Monster的子类实例
	//可以类比为文件系统，MonsterCreator对应为文件夹，其它Monster类实例对应为文件
	//parent指针指向该Monster子类所在的vector对应的MonsterCreator实例
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

class Vampire :public Monster //Vampire-吸血鬼
{
public:
	MonsterType getMonsterType() const;

	Monster* clone(Farm* farm = nullptr, string name = "");

	void killAnimal();//待完善
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
	//prototype模式
	Monster* clone(Farm* farm = nullptr, string name = "");

	//Composite模式
	void addChild(Monster* child);//添加某Monster实例进入children
	void removeChild(Monster* child);//移除children中某Monster子类实例
	void printChildren() const; //打印出children中的各个Monster子类实例的名称
protected:
	MonsterCreator(int dummy, Farm* farm = nullptr, string name = "");
private:
	static MonsterCreator _monsterCreator;
	MonsterCreator();
	vector<Monster*> children;
};

#endif