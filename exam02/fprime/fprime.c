#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int j = 0;
		while (argv[1][j])
			j++;
		char str[j];
		j = 0;
		while (argv[1][j])
		{
			str[j] = argv[1][j];
			j++;
		}
		str[j] = '\0';
		int i = 2;
		int flag = 1;
		int n = atoi(str);
		while (n != 1 && n >= 2)
		{
			if (n % i == 0)
			{
				if (!flag)
                    printf("*");
				n /= i;
				flag = 0;
				printf("%d", i);
				i = 1;
			}
			i++;
		}
	}
	printf("\n");
}