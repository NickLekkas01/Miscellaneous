#include <stdio.h>
#include <math.h>

/*
 * Checks whether <ch> is a whitespace character.
 *
 * 1 only if <ch> is ' ', '\n' or '\t'
 * else 0.
 */
char is_whitespace(char ch)
{
	if (ch == '\n' || ch == ' ' || ch == '\t')
		return 1;
	return 0;
}

/*
 * Returns whether <ch> is a valid input character.
 */
char is_valid(char ch)
{
	if (ch >= '!' && ch <= 'u')
		return 1;
	if (is_whitespace(ch))
		return 1;

	return 0;
}

unsigned int reverse(unsigned int a)
{
	unsigned int b = (a & 0xFF000000) >> 24;

	b |= (a & 0x00FF0000) >> 8;
	b |= (a & 0x0000FF00) << 8;
	b |= (a & 0x000000FF) << 24;

	return b;
}

void print(unsigned int i, int bytes)
{
	i = reverse(i);

	int k;
	for (k = 1; k <= 4; k++)
	{
		putchar(i & 0xFF);
		i >>= 8;
	}
}

int main()
{
	if (getchar() != '<' || getchar() != '~')
	{
		printf("bad input start\n");
		return -1;
	}

	int count = 0;
	char ch = getchar();
	long integer = 0;

	while (is_valid(ch= getchar()))
	{
		if (is_whitespace(ch))
		{
			/* Ignore whitespace characters. */
			continue;
		}

		if (ch == 'z')
		{
			/* 'z' means 4 zeros, so if integer already contains data there is an error. */
			if (integer)
			{
				printf("Bad input character\n");
				return 0;
			}

			print(0, 4);
			continue;
		}

		int i = 4 - (count % 5);

		integer += pow(85, i) * (ch - 33);

		if (i == 0)
		{
			/* check for overflow */
			if (integer > 0xFFFFFFFF)
			{
				printf("Bad input character\n");
				return 0;
			}

			print(integer, 4);

			integer = 0;
		}

		count++;
	}

	if(integer)
	{
		int i;
		int zCount = 0;

		while( (i = 4 - (count % 5)) != 0)
		{

			integer += ('u' - 33) * pow(85, i);
			count ++;
			zCount++;
		}

		print(integer, 4);
	}

	if (ch != '~' || getchar() != '>' || getchar() != '\n')
	{
		printf("bad input end\n");
		return -1;
	}

	if (getchar() != EOF)
	{
		printf("Unnecessary input\n");
	}

	return 0;
}
