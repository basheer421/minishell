#include <stdio.h>

// this code will segfault
int main(int argc, char **argv)
{
	int *ptr;

	ptr = NULL;
	printf("%d\n", *ptr);
	return (0);
}
