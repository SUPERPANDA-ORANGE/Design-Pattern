#include "Farmland.h"

void SOWStrategy::operation(Plant*)
{
	cout << "sow the seed on the soil" << endl;
}

void WATERStrategy::operation(Plant*)
{
	cout << "water the seed" << endl;
}

void DIGStrategy::operation(Plant*)
{
	cout << "dig the soil" << endl;
}

void WEEDStrategy::operation(Plant*)
{
	cout << "weed the grass" << endl;
}

void Farmland::setPlantStrategy(int type)
{
	delete plantStrategy_;

	if (type == SOW) {
		plantStrategy_ = new SOWStrategy();
	}
	else if (type == WATER) {
		plantStrategy_ = new WATERStrategy();
	}
	else if (type == DIG) {
		plantStrategy_ = new DIGStrategy();
	}
	else if (type == WEED) {
		plantStrategy_ = new WEEDStrategy();
	}
	else if (type == SERIES) {
		plantStrategy_ = new SERIESStrategy();
	}
	else if (type == MAGICAL_SOW) {
		plantStrategy_ = new MagicalStrategy(new SOWStrategy());
	}
	else if (type == MAGICAL_WATER) {
		plantStrategy_ = new MagicalStrategy(new WATERStrategy());
	}
	else if (type == MAGICAL_DIG) {
		plantStrategy_ = new MagicalStrategy(new DIGStrategy());
	}
	else if (type == MAGICAL_WEED) {
		plantStrategy_ = new MagicalStrategy(new WEEDStrategy());
	}
}

SERIESStrategy::~SERIESStrategy()
{
	delete sowStrategy;
	delete weedStrategy;
	delete digStrategy;
	delete waterStrategy;
}

void SERIESStrategy::operation(Plant* p)
{
	sowStrategy->operation(p);
	weedStrategy->operation(p);
	waterStrategy->operation(p);
	digStrategy->operation(p);
}

void PlantStrategy::help()
{
	cout << "Exit:(0) Weed:(1) Dig:(2) Sow:(3) Water:(5)" << endl;
}


void MagicalStrategy::useMagic() {
	cout << "by magic" << endl;
}
void MagicalStrategy::operation(Plant* p) {
	DecoratorStrategy::operation(p);
	useMagic();
}


