/*
 * If the jokes are annoying, live with it. This assignment is also annoying.
 */

#include <stdio.h>
#include <stdlib.h>

int byteCount = 0;

/*
 * Prints the character <ch> and adds a new line for every 50 bytes of output.
 */
void print_output(int ch)
{
	if (ch == '\n')
	{
		putchar(ch);
		byteCount = 0;
	} else
	{
		putchar(ch);
		byteCount++;

		if (byteCount == 50)
		{
			putchar('\n');
			byteCount = 0;
		}
	}
}

unsigned int toInt(char a, char b, char c, char d)
{
	return (a << 24) | (b << 16) | (c << 8) | d;
}

/*
 * reverses the base 85 digits of <a> .
 */
long reverse_base85(long a)
{
	long b = a % 85;

	int i;
	for (i = 1; i < 5; i++)
	{
		b *= 85;
		a /= 85;

		b += a % 85;
	}

	return b;
}

/*
 * Prints the first <bytes> of the unsigned integer in Ascii 85 encoding.
 */
void print_base85(long i, int bytes)
{
	if (bytes > 5 || bytes <= 0)
	{
		/*
		 * Houston, we have a problem!
		 * This case should never happen, if so the code is messed up. Happy Debugging!
		 */

		exit(-1);
	}

	if (i == 0)
	{
		print_output('z');

		/* Prettier than a if-else statement. */
		return;
	}

	i = reverse_base85(i);

	int k;
	for (k = 1; k <= bytes; k++)
	{
		/*
		 * Black magic!
		 * Not really, just convert to base 85 by doing repeatedly modulus 85 and division by 85.
		 *
		 * Also, add 33 to display the right ascii characters on the output.
		 */
		print_output((i % 85) + 33);
		i /= 85;
	}
}

int main()
{
	int ch;
	int count = 0;
	long integer = 0; // used for storing the input.

	putchar('<');
	putchar('~');
	putchar('\n');

	// Until the end of love!
	// or at least the end of file...
	while ((ch = getchar()) != EOF)
	{
		int i = 3 - (count % 4);
		integer |= ch << (8 * i);

		if (i == 0)
		{
			print_base85(integer, 5);

			integer = 0;
		}

		count++;
	}

	/* Maybe some bytes are missing. */
	if (count % 4 != 0)
	{
		/* N is  4 - i, thus 5 - N is i + 1 */
		print_base85(integer, (count % 4) + 1);
	}

	putchar('\n');
	putchar('~');
	putchar('>');
	putchar('\n');

	return 0;
}
