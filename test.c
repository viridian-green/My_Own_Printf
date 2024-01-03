#include "ft_printf.h"
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd_un(unsigned int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar_fd(n % 10 + '0', fd);
}
void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_string(char *str, int fd)
{
	ft_putstr_fd(str, fd);
}

void	ft_char(char c, int fd)
{
	ft_putchar_fd(c, fd);
}

void	ft_int(int c, int fd)
{
	ft_putnbr_fd(c, fd);
}


void	ft_hexa_lowercase(unsigned int c)
{
	if (c >= 16)
	{
		ft_hexa_lowercase(c / 16);
		ft_hexa_lowercase(c % 16);
	}
	else
	{
		if (c <= 9)
			ft_putchar_fd((c + '0'), 1);
		if (c == 0)
		{
			(write(1, "0", 1));
			return;
		}
		else
		{
				ft_putchar_fd((c - 10 + 'a'), 1);
		}
	}
}

void ft_hexa_uppercase(unsigned int c)
{
	if (c >= 16)
	{
		ft_hexa_uppercase(c / 16);
		ft_hexa_uppercase(c % 16);
	}
	else
	{
		if (c <= 9)
			ft_putchar_fd((c + '0'), 1);
		if (c == 0)
		{
			(write(1, "0", 1));
			return;
		}
		else
		{
				ft_putchar_fd((c - 10 + 'A'), 1);
		}
	}
}
/*
void	ft_pointer(size_t pointer, int *length)
{
	char	string[25];
	int		i;
	char	*base_character;

	base_character = "0123456789abcdef";
	i = 0;
	write(1, "0x", 2);
	//(*length) += 2;
	if (pointer == 0)
	{
		ft_putcharacter_length('0', length);
		return ;
	}
	while (pointer != 0)
	{
		string[i] = base_character[pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	while (i--)
	{
		ft_putcharacter_length(string[i], length);
	}
}
*/
void data_type_check(const char *s, va_list args_copy)
{
	size_t	i;

	i = 0;
if (s[i] == 'c')
	ft_char(va_arg(args_copy, int), 1);
if (s[i] == 's' )
	ft_string(va_arg(args_copy, char *), 1);
if (s[i] == '%')
	ft_putchar_fd('%', 1);
if (s[i] == 'd' || s[i] == 'i' )
	ft_int(va_arg(args_copy, int), 1);
if (s[i] == 'u' )
	ft_putnbr_fd_un(va_arg(args_copy, unsigned int), 1);
if (s[i] == 'x' )
	ft_hexa_lowercase(va_arg(args_copy, unsigned int));
if (s[i] == 'X' )
	ft_hexa_uppercase(va_arg(args_copy, unsigned int));
/*
if (s[i] == 'p' )
	ft_put_ptr(va_arg(args_copy, size_t));
*/
}

int	writeformat(const char *s, va_list args_copy)
{
	size_t	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			data_type_check(&s[i], args_copy);
		}
		else
		{
			write(1, &s[i], 1);
		}
		i++;
	}
	va_end(args_copy);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	va_start(args, format);

	va_list args_copy;
    va_copy(args_copy, args);
	writeformat(format, args_copy);
	va_end(args);
	return (0);
}


int main()
{
	//unsigned int n = 255;
	ft_printf("%%");
	printf("%%");
}

