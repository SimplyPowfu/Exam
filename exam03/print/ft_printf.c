# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr(char *s)
{
	int i = -1;
	if (!s)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (s[++i])
		write(1, &s[i], 1);
	return (i);
}

int	ft_conv(int i, unsigned int n,char *base)
{
	char *str;
	int b = ft_strlen(base);
	str = malloc(i + 1);
	str[i] = '\0';
	while (n > 0)
	{
		str[--i] = base[n % b];
		n = n / b;
	}
	while (str[i])
		write(1, &str[i++], 1);
	free(str);
	return(i);
}

int	ft_putnbr(int n)
{
	int	i = 0;
	int	temp;

	if (n == 0)
		return(write(1, "0", 1), 1);
	else if (n < 0)
	{
		write(1, "-", ++i);
		if (n == -2147483648)
			return (write(1, "2147483648", 10), 11);
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

int	ft_putnbr_base(unsigned int n)
{
	int i = 0;
	unsigned int temp = n;

	if (n == 0)
		return(write(1, "0", 1), 1);
	while (temp > 0)
	{
		temp /= 16;
		i++;
	}
	return (ft_conv(i, n, "0123456789abcdef"));
}

int	ft_check_arg(char *input, va_list *arg, int *i, int *len)
{
	if (input[*i] != '%')
		return (0);
	else if (input[*i + 1] == 's')
		*len += ft_putstr(va_arg(*arg, char *));
	else if (input[*i + 1] == 'd')
		*len += ft_putnbr(va_arg(*arg, int));
	else if (input[*i + 1] == 'x')
		*len += ft_putnbr_base(va_arg(*arg, unsigned int));
	return ((*i)++, 1);
}

int ft_printf(char *input, ...)
{
	va_list arg;
	int     len = 0;
	int     i = -1;

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
