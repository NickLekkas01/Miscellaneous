#include <iostream>
#include <cstdlib>
#include <string>
#include "list.cpp"
#include "commons.h"
#include "quark.h"
#include "atom.h"

using namespace std;

Nucleus::Nucleus(int protonNumber, int neutronNumber)
{
	protonList = new LinkedList<Proton>();

	for (int i = 0; i < protonNumber; i++)
		protonList->add(new Proton());

	neutronList = new LinkedList<Neutron>();

	for (int i = 0; i < neutronNumber; i++)
		neutronList->add(new Neutron());
}

Nucleus::~Nucleus()
{
	delete protonList;
	delete neutronList;
}


Atom::Atom(int protonNumber, int neutronNumber)
{
	nucleus = new Nucleus(protonNumber, neutronNumber);

	electronList = new LinkedList<Electron>();
	for (int i = 0; i < protonNumber; i++)
		electronList->add(new Electron());

	cout << "An atom has been constructed " << protonNumber << " " << neutronNumber
			<< endl;
}

Atom::~Atom()
{

	cout << "An atom will be destroyed with " << get_atom_number()
			<< " atom number and " << get_mass_number() << " mass number."
			<< endl;
}

int Atom::get_atom_number()
{
	return nucleus->protonList->getSize();
}

int Atom::get_mass_number()
{
	return nucleus->neutronList->getSize();
}

int Atom::get_electric_charge()
{
	double charge = 0;

	Iterator<Proton>* pIt = nucleus->protonList->iterator();

	while (pIt->hasNext())
	{
		charge += pIt->next()->get_electric_charge();
	}

	Iterator<Electron>* eIt = electronList->iterator();

	while (eIt->hasNext())
	{
		charge += eIt->next()->get_electric_charge();
	}

	return charge;
}

void Atom::print()
{
	cout << get_atom_number() << " " << get_mass_number() << " "
			<< get_electric_charge() << endl;

	cout << "{" << endl;
	Iterator<Electron>* eIt = electronList->iterator();
	while(eIt->hasNext())
		eIt->next()->print();
	Iterator<Proton>* pIt = nucleus->protonList->iterator();
	while(pIt->hasNext())
		pIt->next()->print();
	Iterator<Neutron>* nIt = nucleus->neutronList->iterator();
	while(nIt->hasNext())
		nIt->next()->print();
}

class Gluon: public ElementarySubatomicParticle
{
public:
	Gluon() :
			ElementarySubatomicParticle("0", 0.0, integer_spin,
					Statistics::Bose_Einstein)
	{
		this->type = "Gluon";
		cout << "A gluon has been constructed" << endl;
	}

	~Gluon()
	{
		cout << "A gluon will be destroyed" << endl;
	}
};

Proton::Proton() :
		super("1.007 u", half_integer_spin, Statistics::Fermi_Dirac)
{
	this->type = "Proton";

	ll->add(new UpQuark());
	ll->add(new UpQuark());
	ll->add(new DownQuark());
	ll->add(new Gluon());
	ll->add(new Gluon());
	ll->add(new Gluon());

	cout << "A proton has been constructed." << endl;
}

Proton::~Proton()
{
	cout << "A proton will be destroyed." << endl;
}

Neutron::Neutron() :
		super("1.0085 u", half_integer_spin, Statistics::Fermi_Dirac)
{
	this->type = "Neutron";

	ll->add(new UpQuark());
	ll->add(new DownQuark());
	ll->add(new DownQuark());
	ll->add(new Gluon());
	ll->add(new Gluon());
	ll->add(new Gluon());

	cout << "A neutron has been constructed." << endl;
}

Neutron::~Neutron()
{
	cout << "A neutron will be destroyed." << endl;
}

Electron::Electron() :
		super("5.48579909070 * 10^-4 u", -1, half_integer_spin,
				Statistics::Fermi_Dirac)
{
	this->type = "Electron";

	cout << "An electron has been constructed." << endl;
}

Electron::~Electron()
{
	cout << "An electron will be destroyed." << endl;
}

int main()
{
	int protonCount = 0;
	int neutronCount = 0;
	double chargeCount = 0.0;

	int N = rand() % 1000;

	for( int i = 0; i < N; i++)
	{
		int isotope = 12 + (rand() % 3);

		Atom* atom = new Atom(6, isotope - 6);

		atom->print();

		protonCount += atom->get_atom_number();
		neutronCount += atom->get_mass_number() - atom->get_atom_number();
		chargeCount += atom->get_electric_charge();
	}

	cout << "Total protons created : " << protonCount << endl;
	cout << "Total neutrons created : " << neutronCount << endl;
	cout << "Total electric charge created : " << chargeCount << endl;


	return 0;
}
