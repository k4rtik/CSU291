#include <stdio.h>
#include <stdlib.h>
int main ()
{
	FILE *fp;
	fp = fopen("input","wb");
	int i, count=100000, temp;
	for (i = 0; i < count; i += 1)
	{
		temp = (int)random();
		fwrite(&temp, sizeof(int), 1, fp);
	}
	fclose(fp);
	return 0;
}
