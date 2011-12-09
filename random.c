#include <stdio.h>
#include <stdlib.h>
int main ()
{
	int i, count=99999999;
	for (i = 0; i < count; i += 1)
	{
		printf("%d\n", (int)random());
	}
	return 0;
}
