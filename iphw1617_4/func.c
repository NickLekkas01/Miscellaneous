#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Guess
{
	double* values;

	double fitness;
} Guess;

int variableSize;

int generationsSize;
int populationSize;
int fitnessGoal;

double crossingPropability;
double mutationPropability;

Guess* population;

double fitness(Guess guess)
{
	double value;
	int i;
	value = 2 * variableSize;
	for (i = 0; i < variableSize; i++)
	{
		value -= 0.1 * cos(5 * M_PI * guess.values[i]);
		value += guess.values[i] * guess.values[i];
	}
	return value;
}

double drand()
{
	double r = ((double) rand()) / (double) RAND_MAX;
	return (r * 2) - 1;
}

void init()
{
	int i;

	for (i = 0; i < populationSize; i++)
	{
		Guess guess;
		guess.values = (double*) malloc(sizeof(double) * variableSize);

		int j;
		for (j = 0; j < variableSize; j++)
		{
			guess.values[j] = drand();
		}

		guess.fitness = fitness(guess);

		population[i] = guess;
	}
}

void cross(Guess* a, Guess* b)
{
	//Crossing
	int i = (rand() % (variableSize - 1)) + 1;

	Guess ta;
	Guess tb;

	ta.values = (double*) malloc(sizeof(double)*variableSize);
	tb.values = (double*) malloc(sizeof(double)*variableSize);

	int j;
	for(j = 0; j < i; j++)
	{
		ta.values[j] = a->values[j];
		tb.values[j] = b->values[j];
	}

	for(j = i; i < variableSize; j++)
	{
		ta.values[j] = b->values[j];
		tb.values[j] = a->values[j];
	}

	free(a);
	free(b);

	a = &ta;
  	b = &tb;
}

void mutation()
{
	r=drand();
	if (r<)
}

int main()
{
	srand(time(0));

	init();

	int g;
	for (g = 0; g <= generationsSize; g++)
	{

	}
}

