#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int generationsSize;
int populationSize;
int fitnessGoal;

double crossingPropability;
double mutationPropability;

int citySize;

typedef struct Guess
{
	int distance;
	
	int* values;
} Guess;

// two dimension array. D(i,j) is the distance from city i to city j.
int** D;

Guess* population;

double drand()
{
	return ((double) rand()) / (double) RAND_MAX ;
}

// returns a random integer i where 0 <= i <= limit.
int Rand(int limit)
{
	return drand() * limit;
}

int distance(Guess guess)
{
	int dist = 0;
	
	int i;
	for( i = 0; i < citySize - 1; i ++)
	{
		dist += D[guess.values[i]][guess.values[i+1]];
	}	

	return dist;
}

//Fisher - Yates shuffle.
int* randomSequence(int size)
{
	int* temp = (int * ) malloc(sizeof(int) * size);
	int* seq = (int * ) malloc(sizeof(int) * size);
	
	int i;
	for( i = 0; i < size; i++)
	{
		temp[i] = i + 1;
	}
	
	for( i = 0 ; i < size; i++)
	{
		int k = Rand(size - i - 1) ;
		
		int j = 0;
		
		while(temp[j] == 0)
			j++;
		while(k)
		{
			j++;
			k--;	
			while(temp[j] == 0)
				j++;
		}
				
		seq[i] =  temp[j] - 1;
		temp[j] = 0;
		
	}
	
	return seq;
}

void init_population()
{
	int i;
	for(i = 0; i < populationSize; i++)
	{
		Guess guess;
		guess.values = randomSequence(citySize);
		population[i] = guess;
	}
}

int compute()
{
	int maxPos = 0;
	int i;
	
	for(i = 0; i < populationSize; i++)
	{
		population[i].distance = distance(population[i]);
		
		if(population[i].distance > population[maxPos].distance)
		{
			maxPos = i;
		}
	}

	
	return maxPos;
}

//Too slow do something faster!
char isWithin(Guess* guess, int i, int j, int city)
{
	int k;
	for(k = i; k < j; k++)
	{
		if(guess->values[k] ==  city)
		return 1;
	}
	
	return 0;
}

void cross(Guess* a, Guess* b)
{
	
	int i = Rand(citySize - 2);
	int j = i + Rand(citySize - i - 2) + 1;
	
	Guess ta;
	Guess tb;
	
	ta.values = (int *)malloc(sizeof(int)* citySize);
	tb.values = (int *)malloc(sizeof(int)* citySize);
	
	int k;
	int l = j, m = j;
	
	for(k = 0; k < i; k++)
	{
		while(isWithin(a, i, j, b->values[l % citySize]))
		{
			l++;
		}
		
		ta.values[k] = b->values[l++%citySize];
		
		while(isWithin(b, i, j, a->values[m % citySize]))
		{
			m++;
		}
		
		tb.values[k] = a->values[m++%citySize];
	}
	
	for(k = i; k < j; k++)
	{
		ta.values[k] = a->values[k];
		tb.values[k] = b->values[k];
	}
	
	for(k = j; k < citySize; k++)
	{
		while(isWithin(a, i, j, b->values[l % citySize]))
		{
			l++;
		}
		
		ta.values[k] = b->values[l++%citySize];
		
		while(isWithin(b, i, j, a->values[m % citySize]))
		{
			m++;
		}
		
		tb.values[k] = a->values[m++%citySize];
	}
		
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
	int k;
	for(k = 0; k < populationSize; k++ )
	{
		double r = drand();
		if( r < mutationPropability)
		{
			int i = Rand(citySize-1);
			int j = Rand(citySize-1);
			while(i == j)
			{
				j = Rand(citySize - 1);
			}
			
			int temp = population[k].values[i];
			population[k].values[i] = population[k].values[j];
			population[k].values[j] = temp;
		}
	}
}


void parseArguments(int argc, int* argv[])
{
	populationSize = 10;
	generationsSize = 50;
	fitnessGoal = 1024;

	crossingPropability = 0.3;
	mutationPropability = 0.1;
	
	int i;
	for( i = 1; i < argc; i++)
	{
		int * option = argv[i];
		if(strcmp(option, "-P") == 0)
		{
			populationSize = atoi(argv[++i]);
		}else if(strcmp(option, "-G") == 0)
		{
			generationsSize = atoi(argv[++i]);
		}else if(strcmp(option, "-FT") == 0)
		{
			fitnessGoal =  atoi(argv[++i]);
		}else if(strcmp(option, "-PC") == 0)
		{
			sscanf(argv[++i], "%lf", &crossingPropability);
		}else if(strcmp(option, "-PM") == 0)
		{
			sscanf(argv[++i], "%lf", &mutationPropability);
		}else
		{
			printf("You dummy !! Look at the README for the proper usage format!!");
			exit(1);
		}
	}
}

Guess* copy(Guess guess)
{
	
	Guess* copy = malloc(sizeof(Guess));

	copy->distance = guess.distance;
	copy->values = (double*) malloc(sizeof(double) * citySize);
	
	int i;
	for( i =0 ; i < citySize; i++)
	{
		copy->values[i] = guess.values[i];
	}
	
	return copy;
}

void parseInput()
{
	scanf("%d", &citySize);
	
	D = (int **) malloc(sizeof(int*) * citySize);
	
	int i;
	for(i = 0; i < citySize; i++)
	{
		D[i] = (int *) malloc(sizeof(int) * citySize);
	}
	
	for( i = 0; i < citySize; i++)
	{
		int j;
		D[i][i] = 0;

		for(j = i+1; j < citySize; j++)
		{
			int temp;
			scanf("%d", &temp);
			D[i][j] = D[j] [i] = temp;
		}
	}
}

int main(int argc, int* argv[])
{
	
	parseArguments(argc, argv);
	parseInput();

	srand(time(NULL));
	
	population = (Guess*) malloc(sizeof(Guess) * populationSize);
	
	init_population();

	int g;
	Guess* maxGuess = copy(population[0]);

	for (g = 0; g <= generationsSize; g++)
	{ 
		Guess genMax = population[compute()];
		if(genMax.distance > maxGuess->distance)
		{
			maxGuess = copy(genMax);
			if (maxGuess->distance > fitnessGoal)
				break;
		}
		
		crossing();
		mutation();
 	}
 	
 	printf("Distance : %d\n", maxGuess->distance);

}
