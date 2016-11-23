#ifndef COMMONS_HEADER_FILE
#define COMMONS_HEADER_FILE

#include <string>
#include "list.cpp"

const std::string half_integer_spin = "half integer";
const std::string integer_spin = "integer";

enum class Statistics
{
	Fermi_Dirac, Bose_Einstein
};

class SubatomicParticle
{
private:
	std::string mass;
	std::string spin;
	Statistics statistics;

protected:
	std::string type;

public:
	SubatomicParticle(std::string, std::string, Statistics);
	virtual ~SubatomicParticle();

	void print();

	virtual double get_electric_charge();
};

class ElementarySubatomicParticle : public SubatomicParticle
{
private:
	typedef SubatomicParticle super;

	double electricCharge;

public :
	ElementarySubatomicParticle(std::string, double, std::string, Statistics);
	virtual ~ElementarySubatomicParticle();

	double get_electric_charge();
};

class CompositeSubatomicParticle : public SubatomicParticle
{
private :
	typedef SubatomicParticle super;

protected :
	typedef CompositeSubatomicParticle CSP;
	LinkedList<ElementarySubatomicParticle>* ll;

public :
	CompositeSubatomicParticle(std::string, std::string, Statistics);
	virtual ~CompositeSubatomicParticle();

	double get_electric_charge();

	void print();
};

#endif
