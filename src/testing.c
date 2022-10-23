#include <stdio.h>

void printmap(char **map)
{
	int i;
	

	i = 0;
	printf("\t");
	while (i < 10)
	{
		printf("%d", i);
		i++;
	}
	printf("\n");
	i = 0;

	while (map[i])
	{
		printf("%d\t", i);
		printf("%s\n", map[i]);
		i++;
	}
}