
/*
 * You dirty minded freak! You want some comments? I will give you some comments!
 *
 * A project made by Kostas  Alexopoulos (souperk) and Nikos Lekkas. 
 * 
 * We bring no responsibilty for any damage done to your property by the current software.
 *
 * However, some any damage done to your brain by the comments, you may accuse Kostas Alexopoulos.
 *
 * Compilation Instructions :
 * Pending....
 *
 * Execution Instructions : 
 * 
 * -FT <FT> : for setting the fitness goal. Can have any integer value. Default value is 1024 ( = 32 * 32 ).
 * -P <P> : for setting population size. Can have any integer value. Default value is 10.
 * -G <G> : for setting the generation size. Can have any integer value. Default value is 50.
 * -PC <PC> : for setting the probabilty of crossing. Can have any real value in [0,1] . Default value is 0.3 .
 * -PM <PM> : for setting the probability of mutation. Can have any real value in [0,1]. Default value is  0.1 .
 * 
 * 
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Chromosome array
unsigned int* C;

//Temporary array
unsigned int* temp;

//Sum array of fitness : Ki is F1 + ... + Fi
int* K;

unsigned int NUMBER; 

int generationsSize;
int populationSize;
int fitnessGoal;

double crossingPropability;
double mutationPropability;

void print(unsigned int num)
{
	unsigned int mask = 1<<31;
	int i;
	for(i=0;i<32;i++)
	{
		printf("%d", (num&mask) ==  mask);
		num<<=1;
	}
}

unsigned int scan()
{
	unsigned int i = 0;
	
	char ch;
	
	while((ch= getchar()) != '\n')
	{
		i <<= 1;
		i |= (ch - '0');
	}
	
	return i;
}

/*
 * Assuming K has the value described above, returns an integer pos so that
 * K[pos] <= num < K[pos+1}
 *
 */
int binarySearch(int num)
{
	int low = 0;
	int high = populationSize;

	if (K[high] == num)
		return high;

	while (low + 1 < high)
	{
		int mid = (low + high) / 2;
		if (num == K[mid])
			return mid;
		else if (num < K[mid])
			high = mid;
		else
			low = mid;
	}
	return low;
}


/*
 * Returns the fitness as described the excerise description.
 *
 */
int fitness(unsigned int N)
{
	unsigned int mask = 1;
	int count = 0; //count of common bits.
	while (mask)
	{
		//  NOT (N xor Number)
		if (!((N & mask) ^ (NUMBER & mask)))
			count++;
		mask <<= 1;
	}
	return count * count;
}


/*
 * Initiates the population using random values.
 */
void initPopulation()
{
	int i;
	for (i = 0; i < populationSize; i++)
	{
		C[i] = rand();
	}
}

/*
 * 
 */
int compute()
{
	int i;

	K[0] = 0;
	int max = K[0], maxPos = 0;

	for (i = 0; i < populationSize; i++)
	{
		int f = fitness(C[i]);
		if (f > max)
		{
			max = f;
			maxPos = i;
		}
		K[i + 1] = K[i] + f;
	}
	return maxPos;
}

/*
 * Swaps the 2 elements a and b.
 */
void swap(unsigned int* a, unsigned int* b)
{
	unsigned int* t = a;
	a=b;
	b =t;
}


/*
 * 
 */
void selection()
{
	int j;
	for (j = 0; j < populationSize; j++) 
	{
		//check for bugs....
		int p = rand() % K[populationSize - 1];
		int pos = binarySearch(p);
		temp[j] = C[pos];
	}

	
	swap(C, temp);
}


/*
 * Picks a random crossing point and crosses a and b on that point.
 */
void cross(unsigned int* a, unsigned int* b)
{
	int i = (rand() % 31) + 1;
	int rmask = (1 << i) - 1, lmask = !rmask;
	int temp = (*b & rmask);

	*b = (*a & rmask) | (*b & lmask);
	*a = temp | (*a & lmask);

}

/*
 * Applies crossing to the current population.
 */
void crossing()
{
	int j;
	// for odd populationSize this throws seg fault.
	for (j = 0; j < populationSize - 1; j += 2)
	{
		double r = ((double) rand()) / RAND_MAX;
		if (crossingPropability > r)
			cross(&C[j], &C[j + 1]);
	}
}

/*
 * Applies mutation to the current population.
 */
void mutation()
{
	int i;
	for (i = 0; i < populationSize; i++)
	{
		unsigned int mask = 1;
		while (mask)
		{
			double r = ((double) rand()) / RAND_MAX;
			if (r < mutationPropability)
			{
				C[i] = C[i] ^ mask;
			}
			mask <<= 1;
		}
	}
}

/*
 * 
 */
void parseArguments(int argc, int* argv[])
{
	populationSize = 100;
	generationsSize = 100;
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

int main(int argc, int* argv[])
{
	parseArguments(argc, argv);
	
	printf("Give me the binary number\n");
	NUMBER=scan(); 			//100011100101100111000101010101

	srand(time(NULL));


	C = (unsigned int*) malloc(sizeof(unsigned int) * populationSize);
	temp = (unsigned int *) malloc(sizeof(unsigned int) * populationSize);
	K = (int *) malloc(sizeof(int) * (populationSize + 1));
	
	initPopulation();
	
	int i;
	int maxGeneration;
	int maxFitness = -1;
	int maxChromosome;
	
	for (i = 0; i <= generationsSize; i++)
	{
		int maxPos = compute();
		
		int f = fitness(C[maxPos]);
		
		printf("Generation %d: Best Fitness %d Average Fitness %.6lf \n", i, f,
				((double) K[populationSize]) / (double) populationSize);
		if (f > maxFitness)
		{
			maxFitness = f;
			maxChromosome = C[maxPos];
			maxGeneration = i+1;
			if (f > fitnessGoal)
			{
				break;
			}
		}
		
		selection();
		crossing();
		mutation();
	}
	
	printf("Your Number : ") ;
	print(NUMBER);
	printf("\n");
	
	printf("My guess is : ");
	print(maxChromosome);
	printf("\n");
	
	printf("Found in generation %d \n", maxGeneration);
	printf("Fitness %d (%.0lf out of 32 matches)\n", maxFitness, sqrt((double)maxFitness));
	
	return 0;
}
