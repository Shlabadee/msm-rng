#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_args(int argc, char** argv)
{
	int i;
	for (i = 0; i < argc; ++i)
	{
		printf("%s ", argv[i]);
	}
	printf("\n");
}

uint8_t count_digits(uint32_t n)
{
	uint8_t digits = 0;

	while (n > 0)
	{
		n /= 10;
		++digits;
	}

	return digits;
}

uint64_t powi(uint64_t base, uint64_t exponent)
{
	uint64_t n = 1;
	uint64_t i;
	for (i = 0; i < exponent; ++i)
	{
		n *= base;
	}

	return n;
}

uint64_t shake_off(uint64_t n, uint8_t* c)
{
	if (*c % 2)
	{
		n = n % powi(10, *c);
	}
	else
	{
		n /= 10;
	}

	--(*c);
	return n;
}

uint32_t msm(uint32_t n)
{
	uint64_t squared;
	uint8_t digits;

	squared = n * n;
	digits = count_digits(squared);
	while (digits >= 6)
	{
		squared = shake_off(squared, &digits);
	}

	return (uint32_t)squared;
}

int main(int argc, char** argv)
{
	char input[32];
	uint32_t n;
	int i;
	if (argc < 2)
	{
		printf("Middle-square method RNG\n");
		printf("Usage: msm <number> (4 digit minimum)\n");
		printf("Received: ");
		print_args(argc, argv);
		return 0;
	}

	strcpy(input, argv[1]);
	n = strtoul(input, NULL, 0);

	for (i = 0; i < 10; ++i)
	{
		n = msm(n);
		printf("Output: %u\n", n);
	}

	return 0;
}
