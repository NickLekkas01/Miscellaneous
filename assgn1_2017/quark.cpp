#include <iostream>
#include <string>
#include "commons.h"
#include "quark.h"

using namespace std;

Quark::Quark(string mass, double electricCharge) :
		ElementarySubatomicParticle(mass, electricCharge, half_integer_spin, Statistics::Fermi_Dirac)
{
	this->type = "Quark";
}

Quark::~Quark()
{

}

UpQuark::UpQuark() :
		Quark("2.01 MeV/c^2", (double)2/3)
{
	this->type = "Up Quark";

	cout << "An up quark has been constructed" << endl;
}

UpQuark::~UpQuark()
{
	cout << "An up quark will be destroyed" << endl;
}

DownQuark::DownQuark() :
		Quark("4.7 MeV/c^2", (double)-1/3)
{
	this->type = "Down Quark";

	cout << "A down quark has been constructed" << endl;
}

DownQuark::~DownQuark()
{
	cout << "A down quark will be destroyed" << endl;
}
