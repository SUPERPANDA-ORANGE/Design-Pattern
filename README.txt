三大基类 Farm, Creature, Event

Farm	//Farm类已经使用FactoryMethod模式
	LargeFarm
	MiddleFarm
	SmallFarm

Creature
	Animal
		(//哺乳、爬行、鱼、鸟)
		
	Monster      //Monster类已经使用Prototype、Composite模式
		MonsterCreator
		Vampire
		
	(Guardian or Manager)
	
	(Plant)
		
Event		//Event类已经使用Observer模式
	Olympic
	(Concert)
	(Party)

State //状态类，目前只设置了生物状态
	Healthy
	Sick
	Dead