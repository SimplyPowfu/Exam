# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_strlen(const char *s)
{
	int	i = 0;
	while(s[i])
		i++;
	return (i);
}

int ft_putstr(char *s)
{
	int	i;

	i = -1;
	if (!s)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (s[++i])
		write (1, &s[i], 1);
	return (i);
}

int	ft_conv(int pos, unsigned int n, char *base)
{
	char *array;
	int b;

	b = ft_strlen(base);
	array = malloc(pos + 1);
	if (!array)
		return (0);
	array[pos] = '\0';
	while (n > 0)
	{
		array[--pos] = base[n % b];
		n = n / b;
	}
	while(array[pos])
		write(1, &array[pos++], 1);
	free(array);
	return (pos);
}

int ft_putnbr(int n)
{
	int	i = 0;
	int temp;

	if (n == 0)
		return (write(1, "0", 1), 1);
	else if (n < 0)
	{
		write(1, "-", ++i);
		if (n == -2147483648)
		{
			write(1, "2147483648", 10);
			return (i + 10);
		}
		n = -n;
	}
	temp = n;
	while(temp > 0)
	{
		temp /= 10;
		i++;
	}
	return(ft_conv(i, n, "0123456789"));
}

int ft_putbase(unsigned int n)
{
	int	i = 0;
	unsigned int temp;

	if (n == 0)
		return (write(1, "0", 1), 1);
	temp = n;
	while(temp > 0)
	{
		temp /= 16;
		i++;
	}
	return(ft_conv(i, n, "0123456789abcdef"));
}

int ft_check_arg(const char *input, va_list *arg, int *i, int *len)
{
	if (input[*i] != '%')
		return (0);
	else if (input[*i + 1] == 's')
		*len += ft_putstr(va_arg(*arg, char *)); 
	else if (input[*i + 1] == 'd')
		*len += ft_putnbr(va_arg(*arg, int));
	else if (input[*i + 1] == 'x')
		*len += ft_putbase(va_arg(*arg, unsigned int));
	return ((*i)++, 1);
}

int	ft_printf(const char *input, ...)
{
	va_list arg;
	int     i;
	int     len;

	i = -1;
	len = 0;
	va_start(arg, input);
	while (input[++i])
	{
		if (!ft_check_arg(input, &arg, &i, &len))
		{
			write(1, &input[i], 1);
			len++;
		}
	}
	va_end(arg);
	return (len);
}

