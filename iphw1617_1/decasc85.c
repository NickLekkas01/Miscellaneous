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
	if (ch == 'z')
		return 1;
	if (is_whitespace(ch))
		return 1;

	return 0;
}

/*
 * Reverses the bytes of the integer.
 */
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
	for (k = 1; k <= bytes; k++)
	{
		putchar(i & 0xFF);
		i >>= 8;
	}
}

int main()
{
	//check the start of the input.
	if (getchar() != '<' || getchar() != '~')
	{
		fprintf(stderr, "bad start\n");
		return -1;
	}

	int count = 0;
	int ch;
	long integer = 0; //use long to avoid overflows in case of bad input.

	while ((ch = getchar()) != EOF)
	{
		/* check for the end. */
		if (ch == '~' && getchar() == '>' && getchar() == '\n')
		{
			while (is_whitespace(ch = getchar()))
			{
				/* trash any whitespaces at the end.*/
			}

			if (ch != EOF)
			{
				fprintf(stderr, "Unnecessary input\n");
				return -1;
			}

			if (count % 5)
			{
				int i;
				for (i = 0; i < 4 - (count % 5); i++)
				{
					integer += ('u' - 33) * pow(85, i);
				}

				print(integer, (count % 5) - 1);
			}
			return 0;
		}

		if (!is_valid(ch))
		{
			fprintf(stderr, "Bad input character\n");
			return -1;
		}

		if (is_whitespace(ch))
			continue;

		if (ch == 'z')
		{
			if (integer)
			{
				fprintf(stderr, "Bad input character\n");
				return -1;
			}

			print(0, 4);
		}

		int i = 4 - (count % 5);

		integer += (ch - 33) * pow(85, i);

		if (i == 0)
		{
			if (integer > 0xFFFFFFFF)
			{
				fprintf(stderr, "Bad input character\n");
				return -1;
			}

			print(integer, 4);

			integer = 0;
		}

		count++;

	}

	fprintf(stderr, "Bad end\n");

	return -1;
}
