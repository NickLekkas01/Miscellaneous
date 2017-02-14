#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int* C1;
unsigned int* C2;
int* K;
unsigned int NUMBER; 
int generationsSize;
int populationSize;
int fitnessGoal;
double crossingPropability;
double mutationPropability;

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


int fitness(int N)
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


void initPopulation()

{
	int i;
	for (i = 0; i < populationSize; i++)

	{
		C1[i] = rand();
	}
}


int precomp()
{
	int i;
	K[0] = 0;
	int max = K[0], maxPos = 0;
	for (i = 0; i < populationSize; i++)
	{
		int f = fitness(C1[i]);
		if (f > max)
		{
			max = f;
			maxPos = i;
		}
		K[i + 1] = K[i] + f;
	}
	return maxPos;

}



void selection()

{
	int j;
	for (j = 0; j < populationSize; j++)

	{
		//check for bugs....
		int p = rand() % K[populationSize - 1];
		int pos = binarySearch(p);
		C2[j] = C1[pos];
	}

}


void cross(unsigned int* a, unsigned int* b)
{
	int i = (rand() % 31) + 1;
	int rmask = (1 << i) - 1, lmask = !rmask;
	int temp = (*b & rmask);
	*b = (*a & rmask) | (*b & lmask);
	*a = temp | (*a & lmask);

}


void crossing()
{
	int j;
	for (j = 0; j < populationSize; j += 2)
	{
		double r = ((double) rand()) / RAND_MAX;
		if (crossingPropability > r)
			cross(&C2[j], &C2[j + 1]);
	}
}


void mutation()

{
	int i;
	for (i = 0; i < populationSize; i++)
	{
		C1[i] = C2[i];
		unsigned int mask = 1;
		while (mask)
		{
			double r = ((double) rand()) / RAND_MAX;
			if (r < mutationPropability)
			{
				C1[i] = C1[i] ^ mask;
			}
			mask <<= 1;
		}
	}
}


int main()
{
	double max;
	printf("Give me the binary number\n");
	scanf("%d",&NUMBER); 			//100011100101100111000101010101
	srand(time(NULL));
	populationSize = 10;
	generationsSize = 50;
	fitnessGoal = 1024;
	crossingPropability = 0.3;
	mutationPropability = 0.1;
	C1 = (unsigned int*) malloc(sizeof(unsigned int) * populationSize);
	C2 = (unsigned int*) malloc(sizeof(unsigned int) * populationSize);
	K = (int *) malloc(sizeof(int) * (populationSize + 1));
	initPopulation();
	int i,maxplace;
	max=-1;
	for (i = 0; i < generationsSize; i++)
	{
		int maxPos = precomp();
		int f = fitness(C1[maxPos]);
		if (f > fitnessGoal)
		{
			break;
		}
		printf("Generation %d: Best Fitness %d Average Fitness %.6lf \n", i+1, f,
				((double) K[populationSize]) / (double) populationSize);
		if (f>max)
		{
			max=f;
			maxplace=i+1;
		}
		selection();
		crossing();
		mutation();
	}
	printf("Your number: %d \n",NUMBER);
	printf("Found in generation %d \n",maxplace);
	printf("Fitness %lf \n",max);
	return 0;
}
