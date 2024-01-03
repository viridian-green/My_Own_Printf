/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:31 by ademarti          #+#    #+#             */
/*   Updated: 2024/01/03 17:53:28 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	int count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		count += write(fd, &s[i], 1);
		i++;
	}
	return (count);
}
int	ft_putnbr_fd_un(unsigned int n, int fd)
{
	int count = 0;
	if (n >= 10)
	{
		count += ft_putnbr_fd(n / 10, fd);
	}
	count += ft_putchar_fd(n % 10 + '0', fd);
	return (count);
}

int	ft_putnbr_fd(int n, int fd)
{
	int count = 0;
	if (n == -2147483648)
	{
		count += write(fd, "-2147483648", 11);
		return count;
	}
	if (n < 0)
	{
		count += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_putnbr_fd(n / 10, fd);
	}
	count += ft_putchar_fd(n % 10 + '0', fd);
	return (count);
}

void	ft_hexa_lowercase(unsigned int c)
{
	int count;

	count = 0;
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

int data_type_check(const char *s, va_list args_copy)
{
	int	count;
	int i;

	count = 0;
	i = 0;
if (s[i] == 'c')
	count += ft_putchar_fd(va_arg(args_copy, int), 1);
else if (s[i] == 's' )
	return ft_putstr_fd(va_arg(args_copy, char *), 1);
	// count += ft_string(va_arg(args_copy, char *));
else if (s[i] == '%')
	count += write(1, "%", 1);
else if (s[i] == 'd' || s[i] == 'i' )
	count += ft_putnbr_fd(va_arg(args_copy, int), 1);
else if (s[i] == 'u' )
	count += ft_putnbr_fd_un(va_arg(args_copy, unsigned int), 1);
/*
else if (s[i] == 'x' )
	return ft_hexa_lowercase(va_arg(args_copy, unsigned int));
else if (s[i] == 'X' )
	return ft_hexa_uppercase(va_arg(args_copy, unsigned int));
else if (s[i] == 'p' )
	return ft_put_ptr(va_arg(args_copy, size_t));
*/
	return (count);
}

 int	writeformat(const char *s, va_list args_copy)
{
	size_t	i;
	int size;

	i = 0;
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
	return (size);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	va_start(args, format);

	va_list args_copy;
    va_copy(args_copy, args);
	int len = writeformat(format, args_copy);
	va_end(args);
	return (len);
}
// my printf does not return the good int for strings and %.

int main()
{
	unsigned int n = 255;
	// ft_printf("%d", 12);
	printf("%d", ft_printf("hey is this okay%% fff e"));
}

