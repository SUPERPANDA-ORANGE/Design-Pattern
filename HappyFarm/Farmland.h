#ifndef FARMLAND_H
#define FARMLAND_H

#include "Creature.h"
#include <vector>
#include <list>

using namespace std;

class Farmland
{
public:
	enum PlantStrategyType {
		SOW, WATER, DIG, WEED, SERIES, MAGICAL_SOW, MAGICAL_WATER, MAGICAL_DIG, MAGICAL_WEED
		//SERIES表示四个动作一起进行,运用外观模式；后4中表示运用装饰模式修饰后的动作
	};
	enum FarmlandColor {BLACK , RED , BROWN};
	struct FarmlandPos
	{
		int x;
		int y;
		FarmlandPos(int a , int b ): x(a) , y(b){}
	};
	Farmland(){
		plantStrategy_ = NULL;
	}
	int getPlantCount(){
		return plants.size;
	}
	void setPlantStrategy(int type);
	void addPlant(Plant &);
	void removePlant(int cur);
private:
	vector<vector<Plant> > plants;
	PlantStrategy* plantStrategy_;
};
// 使用了策略模式，装饰模式
class PlantStrategy
{
public:
	PlantStrategy(){
	}
	void getFarmland(Farmland* farmland) {
		this->farmland = farmland;
	}
	void help();//显示策略选项
	void doIt();
	virtual void operation(Plant*) = 0;
protected:
	Farmland* farmland;
	list<Plant> plantList;//用于命令模式，待完善
	
};

class SOWStrategy : public PlantStrategy
{
public:
	SOWStrategy(){}
	void operation(Plant*);
};

class WATERStrategy : public PlantStrategy
{
public:
	WATERStrategy(){}
	void operation(Plant*);
};

class DIGStrategy : public PlantStrategy
{
public:
	DIGStrategy(){}
	void operation(Plant*);
};

class WEEDStrategy : public PlantStrategy
{
public:
	WEEDStrategy(){}
	void operation(Plant*);
};
//外观模式
class SERIESStrategy : public PlantStrategy
{
public:
	SERIESStrategy(){}
	~SERIESStrategy();
	void operation(Plant*);
private:
	SOWStrategy* sowStrategy;
	WEEDStrategy* weedStrategy;
	WATERStrategy* waterStrategy;
	DIGStrategy* digStrategy;
};

class DecoratorStrategy : public PlantStrategy
{
private:
	PlantStrategy* pStrategy;
public:
	DecoratorStrategy(PlantStrategy* p):pStrategy(p) {}
	virtual void operation(Plant* p) { pStrategy->operation(p); }
};

class MagicalStrategy : public DecoratorStrategy
{
private:
	void useMagic();
public:
	MagicalStrategy(PlantStrategy* p):DecoratorStrategy(p){}
	void operation(Plant*);
};


class Soil
{
public:
	Soil(string sColor) {
		this->soilColor = sColor;
	}

private:
	string soilColor;
};

class Farmland_Pos_Color : public Farmland {
protected:
	FarmlandColor f_color;
public:
	Farmland_Pos_Color(FarmlandColor color): f_color(color){}
	~Farmland_Pos_Color() {}
	virtual void Set(){}
};

class BlackFarmland : public Farmland_Pos_Color {
public :
	BlackFarmland(FarmlandColor color): Farmland_Pos_Color(color){}
	~BlackFarmland(){}
	void Set() { cout << "set a piece of black Farmland"; }
};

class RedFarmland : public Farmland_Pos_Color {
public:
	RedFarmland(FarmlandColor color) : Farmland_Pos_Color(color) {}
	~RedFarmland() {}
	void Set() { cout << "set a piece of red Farmland"; }
};

class BrownFarmland : public Farmland_Pos_Color {
public:
	BrownFarmland(FarmlandColor color) : Farmland_Pos_Color(color) {}
	~BrownFarmland() {}
	void Set() { cout << "set a piece of brown Farmland"; }
};

class FarmlandBoard : public Farmland
{
private:
	vector<FarmlandPos> f_Posl;
	Farmland_Pos_Color *f_blackFarmland;
	Farmland_Pos_Color *f_brownFarmland;
	Farmland_Pos_Color *f_redFarmland;
	string f_blackName;
	string f_redName;
	string f_brownName;
public:
	FarmlandBoard(string black, string red, string brown) :f_blackName(black), f_redName(red), f_brownName(brown) {
		f_blackFarmland = NULL;
		f_redFarmland = NULL;
		f_brownFarmland = NULL;
	}
	~FarmlandBoard() { delete f_blackFarmland; delete f_redFarmland; delete f_brownFarmland; }
	void SetFarmland(FarmlandColor color, FarmlandPos pos)
	{
		if (color == BLACK)
		{
			if(f_blackFarmland == NULL)
			{
				f_blackFarmland = new BlackFarmland(color);
			}
			cout << f_blackFarmland << "is in position" << pos.x << "," << pos.y;
			f_blackFarmland->Set();
		}
		else if (f_redFarmland == NULL) 
		{
			{
				f_redFarmland = new RedFarmland(color);

			}
			cout << f_redFarmland << "is in position" << pos.x << "," << pos.y;
			f_redFarmland->Set();
		}
		else
		{
			if (f_brownFarmland == NULL)
			{
				f_brownFarmland = new BrownFarmland(color);
			}
			cout << f_brownFarmland << "is in position" << pos.x << "," << pos.y;
			f_brownFarmland->Set();
		}
		f_Posl.push_back(pos);
	}
};
#endif
