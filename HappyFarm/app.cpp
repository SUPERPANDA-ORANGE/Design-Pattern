#include "FarmFramework.h"


int main() {

	LargeFarm* farm = (LargeFarm*) Farm::createFarmBySize(Farm::FarmSize::LARGE);

	Animal* cat = new Animal(farm, "cat");
	Animal* dog = new Animal(farm, "dog");

	Vampire* vampire1 = (Vampire*)Monster::findAndClone(Monster::MonsterType::VAMPIRE, farm, "vampire1");
	Vampire* vampire2 = (Vampire*)Monster::findAndClone(Monster::MonsterType::VAMPIRE, farm, "vampire2");
	MonsterCreator* monsterCreator1 = (MonsterCreator*)Monster::findAndClone(Monster::MONSTER_CREATOR, farm, "monsterCreator1");
	MonsterCreator* monsterCreator2 = (MonsterCreator*)Monster::findAndClone(Monster::MONSTER_CREATOR, farm, "monsterCreator2");
	//                  ½á¹¹
	//             monsterCreator1
	//              /           \
	//        vampire1    monsterCreator2
	//							|
	//						 vampire2
	monsterCreator1->addChild(vampire1);
	monsterCreator1->addChild(monsterCreator2);
	monsterCreator2->addChild(vampire2);
	monsterCreator1->printChildren();
	

	vampire1->killAnimal();


	Olympic* o = new Olympic(farm, "Olympic");
	cat->joinEvent(o);
	dog->joinEvent(o);
	dog->quitEvent();

	cout << "Event number(farm id:" << farm->getId() << "): " << farm->CountAndCleanEvents() << endl;
	o->start();
	o->on();
	o->end();
	cout << "Event number(farm id:" << farm->getId() << "): " << farm->CountAndCleanEvents() << endl;

	delete farm;


}