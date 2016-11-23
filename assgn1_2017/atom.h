#ifndef ATOM_HEADER
#define ATOME_HEADER

#include "list.cpp"
#include "commons.h"

class Proton: public CompositeSubatomicParticle
{
private:
	typedef CompositeSubatomicParticle super;

public:
	Proton();
	~Proton();
};

class Neutron: public CompositeSubatomicParticle
{
private:
	typedef CompositeSubatomicParticle super;

public:
	Neutron();
	~Neutron();
};

class Electron: public ElementarySubatomicParticle
{
private:
	typedef ElementarySubatomicParticle super;

public:
	Electron();
	~Electron();
};

class Nucleus
{
public:
	Nucleus(int protonNumber, int neutronNumber);
	~Nucleus();

	LinkedList<Proton>* protonList;
	LinkedList<Neutron>* neutronList;

};

class Atom
{
private:
	Nucleus* nucleus;
	LinkedList<Electron>* electronList;

public:
	Atom(int protonNumber, int neutronNumber);
	~Atom();

	int get_atom_number();
	int get_mass_number();
	int get_electric_charge();

	void print();
};

#endif
