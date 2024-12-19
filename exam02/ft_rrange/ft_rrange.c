#include <stdlib.h>
void	ft(int *result, int start, int end)
{
	int i = 0;
	if (start <= end)
	{
		while(start <= end)
		{
			result[i] = end;
			end--;
			i++;
		}
	}
	else if (start > end)
	{
		while(end <= start)
		{
			result[i] = end;
			end++;
			i++;
		}
	}
}

int     *ft_rrange(int start, int end)
{
	int *array;
	int size = start - end;
	if (size < 0)
		size *= -1;
	array = (int *)malloc((size + 1) * sizeof(int));
	ft(array, start, end);
	return (array);
}
// #include <stdio.h>
// int main()
// {
// 	int *d = ft_rrange(3, 7);
// 	printf("%d,%d,%d,%d\n", d[0],d[1],d[2],d[3]);
// }