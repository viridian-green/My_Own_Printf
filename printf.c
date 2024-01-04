/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:31 by ademarti          #+#    #+#             */
/*   Updated: 2024/01/04 11:17:29 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_putchar_fd(char c, int fd)
{
	int count;
	count = 0;
	write(fd, &c, 1);
	count++;
	return (count);
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

int ft_putnbr_fd_un(unsigned int n, int fd)
{
	int count = 0;
	if (n >= 10)
	{
		count += ft_putnbr_fd(n / 10, fd);
	}
	count += ft_putchar_fd(n % 10 + '0', fd);
	return (count);
}

int ft_putnbr_fd(int n, int fd)
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

int ft_hexa_lowercase(unsigned int c)
{
	int count;

	count = 0;
	if (c >= 16)
	{
		count += ft_hexa_lowercase(c / 16);
		count += ft_hexa_lowercase(c % 16);
	}
	else
	{
		if (c <= 9)
			count += ft_putchar_fd((c + '0'), 1);
		if (c == 0)
		{
			count += write(1, "0", 1);
			return (count);
		}
		else
		{
			count += ft_putchar_fd((c - 10 + 'a'), 1);
		}
	}
	return (count);
}

int	ft_hexa_uppercase(unsigned int c)
{
	int count;

	count = 0;
	if (c >= 16)
	{
		count += ft_hexa_uppercase(c / 16);
		count += ft_hexa_uppercase(c % 16);
	}
	else
	{
		if (c <= 9)
			count += ft_putchar_fd((c + '0'), 1);
		if (c == 0)
		{
			count +=  write(1, "0", 1);
			return (count);
		}
		else
		{
			count += ft_putchar_fd((c - 10 + 'A'), 1);
		}
	}
	return (count);
}
/*
int	put_ptr(void *p, va_list args_copy)
{
	int	count;
	char buffer[20];
	char *hexDigits = "0123456789abcdef";
	char *ptr;
	unsigned long	ptr_address;

	ptr_address = (unsigned long)ptr;
	count = 0;
	i = 0;
	while
}
*/
int	data_type_check(const char *s, va_list args_copy)
{
	int i;
	int count;
	count = 0;

	i = 0;
	if (s[i] == 'c')
		return ft_putchar_fd(va_arg(args_copy, int), 1);
	else if (s[i] == 's')
		return ft_string(va_arg(args_copy, char *));
	else if (s[i] == '%')
		return write(1, "%", 1);
	else if (s[i] == 'd' || s[i] == 'i')
		return ft_putnbr_fd(va_arg(args_copy, int), 1);
	else if (s[i] == 'u')
		return ft_putnbr_fd_un(va_arg(args_copy, unsigned int), 1);
	else if (s[i] == 'x' )
		return  ft_hexa_lowercase(va_arg(args_copy, unsigned int));
	else if (s[i] == 'X' )
		return ft_hexa_uppercase(va_arg(args_copy, unsigned int));
	/*
	else if (s[i] == 'p' )
		return ft_put_ptr(va_arg(args_copy, size_t));
	*/
	return (count);
}

int writeformat(const char *s, va_list args_copy)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			size += data_type_check(&s[i], args_copy);
			if (size < 0)
			{
				return (-1);
			}
		}
		else
		{
			write(1, &s[i], 1);
			size++;
		}
		i++;
	}
	va_end(args_copy);
	return (size);
}
int ft_printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	va_list args_copy;
	va_copy(args_copy, args);
	int len = writeformat(format, args_copy);
	va_end(args);
	return (len);
}

/*
int main()
{
	// ft_printf("%d", 12);
	//printf("%d", ft_printf(" %s ", "hey"));;
	//ft_printf(" %s ", "hey");
	//printf(" %s \n", "hey");

}
*/
