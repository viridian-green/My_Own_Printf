/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:31 by ademarti          #+#    #+#             */
/*   Updated: 2023/12/12 17:25:47 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

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

void ft_string(char *str, int fd)
{
	ft_putstr_fd(str, fd);
}

void ft_char(char c, int fd)
{
	ft_putchar_fd(c, fd);
}

void ft_int(int c, int fd)
{
	ft_putnbr_fd(c, fd);
}

void ft_hexa(int c, int fd)
{

}

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
	ft_hexa(va_arg(args_copy, unsigned int), 1);
/*
if (s[i] == 'p' )
	ft_string(va_arg(args_copy, char *));

if (s[i] == 'i' )
	ft_string(va_arg(args_copy, char *));
if (s[i] == 'X' )
	ft_string(va_arg(args_copy, char *));
	*/
}

int	writeformat(const char *s, va_list args_copy)
{
	size_t	i;

	i = 0;

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
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	va_start(args, format);

	va_list args_copy;
    va_copy(args_copy, args);
	writeformat(format, args_copy);

	va_end(args);
	return (-1);
}

int main()
{
	unsigned int n = 255;
	//ft_printf("The answer is %s.\n", n, "hello");
	printf("The answer is %x.\n", n);
}

