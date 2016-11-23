#include <iostream>
#include <string>
#include "commons.h"
#include "list.cpp"

using namespace std;

SubatomicParticle::SubatomicParticle(string mass, string spin, Statistics stats)
{
	this->mass = mass;
	this->spin = spin;
	this->statistics = stats;
}

SubatomicParticle::~SubatomicParticle()
{

}

double SubatomicParticle::get_electric_charge()
{
	return 0;//should be overriden by sub-classses.
}

void SubatomicParticle::print()
{
	cout << "[type=" << type;
	cout << ", mass=" << mass;
	cout << ", spin=" << spin;

	double electricCharge =  get_electric_charge();

	cout << ", electricCharge=";
	if( electricCharge > 0)
		cout << "+";
	cout << get_electric_charge() << "e";

	switch (statistics) {
	case Statistics::Fermi_Dirac:
		cout << ", statistics=Fermi-Dirac";
		break;
	case Statistics::Bose_Einstein:
		cout << ", statistics=Bose-Einstein";
		break;
	default:
		break;
	}

	cout << "]" << endl;
}

ElementarySubatomicParticle::ElementarySubatomicParticle(string mass,
		double electricCharge, string spin, Statistics stats) :
		super(mass, spin, stats)
{
	this->electricCharge = electricCharge;
}

ElementarySubatomicParticle::~ElementarySubatomicParticle()
{

}

double ElementarySubatomicParticle::get_electric_charge()
{
	return electricCharge;
}

CompositeSubatomicParticle::CompositeSubatomicParticle(string mass, string spin,
		Statistics stats) :
		super(mass, spin, stats)
{
	ll = new LinkedList<ElementarySubatomicParticle>();
}

CompositeSubatomicParticle::~CompositeSubatomicParticle()
{
	delete ll;
}

double CompositeSubatomicParticle::get_electric_charge()
{
	double electricCharge = 0.0;

	Iterator<ElementarySubatomicParticle>* it = ll->iterator();

	while (it->hasNext())
	{
		electricCharge += it->next()->get_electric_charge();
	}

	return electricCharge;
}

void CompositeSubatomicParticle::print()
{
	super::print();
	cout << "{" << endl;
	Iterator<ElementarySubatomicParticle>* it = ll->iterator();

	while (it->hasNext())
	{
		it->next()->print();
	}
	cout << "}" << endl;

}
