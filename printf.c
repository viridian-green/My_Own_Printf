/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:31 by ademarti          #+#    #+#             */
/*   Updated: 2024/01/03 13:27:00 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
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


int	ft_string(char *str)
{
	int		i;

	i = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			ft_putchar_fd(str[i], 1);
			return (i);
		}
		ft_putchar_fd(str[i], 1);
		i++;
	}
	return (i);
}

int	ft_char(char c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
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

static int data_type_check(const char *s, va_list args_copy)
{
	size_t	i;

	i = 0;
if (s[i] == 'c')
	return ft_char(va_arg(args_copy, int), 1);
if (s[i] == 's' )
	return ft_string(va_arg(args_copy, char *));
if (s[i] == '%')
	return ft_string(va_arg(args_copy, char *));
/*
if (s[i] == 'd' || s[i] == 'i' )
	return ft_int(va_arg(args_copy, int), 1);
if (s[i] == 'u' )
	return ft_putnbr_fd_un(va_arg(args_copy, unsigned int), 1);
if (s[i] == 'x' )
	return ft_hexa_lowercase(va_arg(args_copy, unsigned int));
if (s[i] == 'X' )
	return ft_hexa_uppercase(va_arg(args_copy, unsigned int));
if (s[i] == 'p' )
	return ft_put_ptr(va_arg(args_copy, size_t));
*/
	return (-1);
}

int	writeformat(const char *s, va_list args_copy)
{
	size_t	i;
	size_t len;
	int size;

	i = 0;
	len = 0;
	i = -1;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			size = data_type_check(&s[i], args_copy);
			if (size == -1)
			{
				return (-1);
			}
		}
		else
		{
			write(1, &s[i], 1);
		}
		i++;
	}
	va_end(args_copy);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	va_start(args, format);

	va_list args_copy;
    va_copy(args_copy, args);
	int len = writeformat(format, args_copy);
	va_end(args);
	return len;
}


int main()
{
	//unsigned int n = 255;
	ft_printf("%%");
	printf("%%");
}

