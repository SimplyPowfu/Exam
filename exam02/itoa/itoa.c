#include <stdlib.h>
#include <stdio.h>

static int	ft_size(int n)
{
	int size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void	ft_putnbr(char *str, int nb, int *i)
{
	if (nb == -2147483648)
	{
		str[*i] = '-';
		(*i)++;
		str[*i] = '2';
		(*i)++;
		nb = 147483648;
	}
	if (nb < 0)
	{
		str[*i] = '-';
		(*i)++;
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr(str, nb / 10, i);
	str[*i] = (nb % 10) + 48;
	(*i)++;
}

char	*ft_itoa(int n)
{
	char *str;
	int i = 0;
	str = malloc(ft_size(n) + 1);
	if (str == NULL)
		return (NULL);
	ft_putnbr(str, n, &i);
	str[i] = '\0';
	return (str);
}

int main()
{
	int n = 41;
	printf("%s", ft_itoa(n));
}
