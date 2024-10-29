#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>


void	ft_putchar(int c, int *count)
{
	write(1, &c, 1);
	*count += 1;
}

void	ft_putstr(char *str, int *count)
{
	int	i = 0;
	
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		*count += 1;
	}
}

void	ft_putnbr(int num, int *count)
{
	if (num == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2", 1);
		*count += 2;
		ft_putnbr(num, count);
	}
	else if (num < 0)
	{
		write(1, "-", 1);
		*count += 1;
		ft_putnbr(num * -1, count);
	}
	else if (num > 10)
	{
		ft_putnbr(num/10, count);
		ft_putnbr(num%10, count);
	}
	else
	{
		char c = num + 48;
		write(1, &c , 1);
		*count += 1;
	
	}
}

void	ft_puthex(unsigned int num, int *count)
{
	char	hex[] = "0123456789abcdef";

	if (num >= 16)
	{
		ft_puthex(num/16, count);
		ft_puthex(num%16, count);
	}
	else
		ft_putchar(hex[num], count);
}

void	transport(const char	*arg, va_list str, int *count)
{
	int	i = 0;

	if (!arg)
		return ;
	while (arg[i])
	{
		if (arg[i] == '%')
		{
			i++;
			if (arg[i] == 's')
				ft_putstr(va_arg(str, char *), count);
			if (arg[i] == 'd')
				ft_putnbr(va_arg(str, int), count);
			if (arg[i] == 'x')
				ft_puthex(va_arg(str, unsigned int), count);
		}
		else
			ft_putchar(arg[i], count);
		i++;
	}
}

int	ft_printf(const char *arg, ...)
{
	va_list str;
	int	count;

	count = 0;
	va_start(str, arg);
	transport(arg, str, &count);
	va_end(str);
	return (count);
}

int main()
{
	char	str[] = "teste1";
	int	i = __INT_MAX__;
	int	d;

	d = ft_printf("I: %x\n", i);
	ft_printf("d: %d\n", d);
	d = printf("I: %x\n", i);
	printf("d: %d", d);
}
