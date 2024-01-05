/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:31 by ademarti          #+#    #+#             */
/*   Updated: 2024/01/05 14:58:43 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
//#include "../include/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_putchar_fd(char c, int fd)
{
	int	count;

	count = 0;
	write(fd, &c, 1);
	count++;
	return (count);
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



int	ft_string(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (str[i] != '\0')
	{
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
		else if (c == 0)
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
		else if (c == 0)
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

int	ft_put_ptr(unsigned long long num)
{

	int count;

	count = 0;
	if (num >= 16)
	{
		count += ft_put_ptr(num / 16);
		count += ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			count += ft_putchar_fd((num + '0'), 1);
		else
		{
			count += ft_putchar_fd((num - 10 + 'a'), 1);
		}
	}
	return (count);
}

int	ft_print_ptr(void *ptr)
{
	int	count;
	unsigned long long un_ptr = (unsigned long long)ptr;

	count = 0;
	count += write(1, "0x", 2);
	if (ptr == 0)
		count += write(1, "0", 1);
	else
	{
		count += ft_put_ptr(un_ptr);
	}
	return (count);
}

int	data_type_check(const char *s, va_list args_copy)
{
	int	i;
	char *str_arg;

	i = 0;
	if (s[i] == 'c')
		return ft_putchar_fd(va_arg(args_copy, int), 1);
	else if (s[i] == 's')
		str_arg = va_arg(args_copy, char *);
    	if (str_arg != 0)
        return ft_string(str_arg);
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
	else if (s[i] == 'p' )
		return ft_print_ptr(va_arg(args_copy, void *));

	return (-1);
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
		if (s[i] != '\0')
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


int main()
{
	// ft_printf("%d", 12);
	//printf("%d", printf(" %x ", 17));;
	//ft_printf("%p \n", "hey");
	//printf("%p \n", "hey");
	printf("%s", "some string with\0 hehe");
}
