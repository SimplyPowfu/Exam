int	is_power_of_2(unsigned int n)
{
	if (n <= 0)
		return (0);
	if (n == 1)
		return (1);
	while (n % 2 == 0 && n != 2)
		n = n / 2;
	if (n == 2)
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int main()
// {
// 	int i = 1;
// 	printf("%d", is_power_of_2(i));
// }