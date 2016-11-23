#ifndef QUARK_HEADER_FILE
#define QUARK_HEADER_FILE

#include <string>

class Quark: public ElementarySubatomicParticle
{
public:
	Quark(std::string, double);
	~Quark();
};

class UpQuark: public Quark
{
public:
	UpQuark();
	~UpQuark();
};

class DownQuark: public Quark
{
public:
	DownQuark();

	~DownQuark();
};

#endif

