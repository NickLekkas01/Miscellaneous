#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Guess
{
	double* values;
	double fitness;
} Guess;

int variableSize = 5;
int generationsSize;
int populationSize;
int fitnessGoal;

double crossingPropability;
double mutationPropability;

Guess* population;
Guess* temp;

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
	return ((double) rand()) / (double) RAND_MAX;
}

double randValue()
{
	double r;
	r=drand();
	return (r * 2) - 1;
}

void init_population()
{
	int i;
	for (i = 0; i < populationSize; i++)
	{
		Guess guess;
		guess.values = (double*) malloc(sizeof(double) * variableSize);
		int j;
		for (j = 0; j < variableSize; j++)
		{
			guess.values[j] = randValue();
		}
		population[i] = guess;
	}
}

int compute()
{
	int maxPos = 0;
	int i;
	for(i = 0; i < populationSize; i++)
	{
		population[i].fitness = fitness(population[i]);
		
		if(population[i].fitness > population[maxPos].fitness)
		{
			maxPos = i;
		}
	}
	
	return maxPos;
}

void cross(Guess* a, Guess* b)
{
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

	for(j = i; j < variableSize; j++)
	{
		ta.values[j] = b->values[j];
		tb.values[j] = a->values[j];
	}
	
	a = &ta;
  	b = &tb;
}

void crossing()
{
	int i ;
	for( i = 0; i < populationSize; i+=2)
	{
		cross(&population[i], &population[i+1]);
	}
}
void mutation()
{
	int i;
	for(i = 0; i < populationSize; i++ )
	{
		int j;
		for( j = 0; j < variableSize; j++)
		{
			double r = drand();
			if( r < mutationPropability)
			{
				population[i].values[j] = randValue();
			}
		}
	}
}

void parseArguments(int argc, int* argv[])
{
	populationSize = 100;
	generationsSize = 50	;
	fitnessGoal = 1024;

	crossingPropability = 0.3;
	mutationPropability = 0.1;
	
	int i;
	for( i = 1; i < argc; i++)
	{
		int* option = argv[i];
		if(strcmp(option, "-P") == 0)
		{
			populationSize = atoi(argv[++i]);
		}else if(strcmp(option, "-G") == 0)
		{
			generationsSize = atoi(argv[++i]);
		}else if(strcmp(option, "-FT"))
		{
			fitnessGoal =  atoi(argv[++i]);
		}else if(strcmp(option, "-PC") == 0)
		{
			sscanf(argv[++i], "%lf", &crossingPropability);
		}else if(strcmp(option, "-PM") == 0)
		{
			sscanf(argv[++i], "%lf", &mutationPropability);
		}else if(strcmp(option, "-N") == 0)
		{
			variableSize = atoi(argv[++i]);
		}else
		{
			printf("You dummy !! Look at the README for the proper usage format!!");
			exit(1);
		}
	}
}

int main(int argc, int* argv[])
{
	parseArguments(argc, argv);
	
	srand(time(0));
	
	population = (Guess*) malloc(sizeof(Guess) * populationSize);
	
	init_population();

	int g;
	Guess* maxGuess = copy(population[0]);
	int c = 0;
	for (g = 0; g <= generationsSize; g++)
	{ 
		Guess genMax = population[compute()];
		if(genMax.fitness > maxGuess->fitness)
		{
			maxGuess = copy(genMax);
			if (maxGuess->fitness>fitnessGoal)
				break;
		}
		
		crossing();
		mutation();
 	}
	
	printf("Best Guess : (");
	
	int i;
	for(i = 0; i < variableSize; i++)
	{
		printf("x%d = %lf ", i, maxGuess->values[i]);
	}
	
	printf(") -> %lf \n", maxGuess->fitness);
}
