/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:31 by ademarti          #+#    #+#             */
/*   Updated: 2023/12/12 14:53:48 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "printf.h"
#include <stdio.h>

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

void ft_string(char *str, int fd)
{
	ft_putstr_fd(str, fd);

}

char ft_char(char c, int fd)
{
	char result;

	result = (char)malloc((sizeof(char) * 1));
	result = ft_putchar_fd(c, fd);

}

int	writeformat(const char *s, va_list args_copy);

void data_type_check(const char *s, va_list args_copy)
{
	size_t	i;

	i = 0;
if (s[i] == 'c' )
	ft_char(va_arg(args_copy, int), 1);
if (s[i] == 's' )
	ft_string(va_arg(args_copy, char *), 1);
/*
if (s[i] == 'p' )
	ft_string(va_arg(args_copy, char *));
if (s[i] == '%' )
	ft_string(va_arg(args_copy, char *));
if (s[i] == 'd' || s[i] == 'i' )
	ft_int(va_arg(args_copy, int));
if (s[i + 1] == 'u' )
	ft_string(va_arg(args_copy, char *));
if (s[i] == 'x' )
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
			i++;
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
	ft_printf("The answer is %c %s.\n", 's',"hello");
	printf("The answer is %c.\n", 's');
}
