# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_conv(int i, unsigned long n, char *base)
{
	char	*array;
	int		b;

	b = ft_strlen(base);
	array = malloc(sizeof(char) * (i + 1));
	if (!array)
		return (0);
	array[i] = '\0';
	while (n > 0)
	{
		array[--i] = base[n % b];
		n = n / b;
	}
	while (array[i])
		write (1, &array[i++], 1);
	free (array);
	return (i);
}

int	ft_putnbr_fd(int n)
{
	int		temp;
	int		i;

	i = 0;
	if (n == 0)
		return (write(1, "0", 1), 1);
	else if (n < 0)
	{
		write (1, "-", ++i);
		if (n == -2147483648)
		{
			write(1, "2147483648", 10);
			return (i + 10);
		}
		n = -n;
	}
	temp = n;
	while (temp > 0)
	{
		temp /= 10;
		i++;
	}
	return (ft_conv(i, n, "0123456789"));
}

int	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putbase(unsigned long n, char *base)
{
	unsigned long	temp;
	int				i;

	temp = n;
	i = 0;
	if (n == 0)
		return (write (1, "0", 1), 1);
	while (temp > 0)
	{
		temp /= 16;
		i++;
	}
	return (ft_conv(i, n, base));
}

static int	ft_check_arg(const char *input, va_list *arg, int *i, int *len)
{
	if (input[*i] != '%')
		return (0);
	else if (input[*i + 1] == 's')
		*len += ft_putstr_fd(va_arg(*arg, char *), 1);
	else if (input[*i + 1] == 'd')
		*len += ft_putnbr_fd(va_arg(*arg, int));
	else if (input[*i + 1] == 'x')
		*len += ft_putbase(va_arg(*arg, unsigned int), "0123456789abcdef");
	else if (input[*i + 1] == '%')
		*len += ft_putchar_fd('%', 1);
	return ((*i)++, 1);
}

int	ft_printf(const char *input, ...)
{
	va_list	arg;
	int		i;
	int		len;

	i = -1;
	len = 0;
	va_start(arg, input);
	while (input[++i])
	{
		if (ft_check_arg(input, &arg, &i, &len) == 0)
		{
			write(1, &input[i], 1);
			len++;
		}
	}
	va_end(arg);
	return (len);
}

// int main()
// {
// 	printf("%s: %d, %x\n", "prova", 10, 88);
//     ft_printf("%s: %d, %x\n", "prova", 10, 88);
//     return (0);
// }