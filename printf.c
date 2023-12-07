/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:31 by ademarti          #+#    #+#             */
/*   Updated: 2023/12/07 17:12:49 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	writeformat(char *s, va_list args)
{
	size_t	pos;

	pos = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] == '%')
		{
			if (s[pos + 1] == 'c' || s[pos + 1] == 's' || s[pos + 1] == 'p')
			{
				characters(args);
				pos = pos + characters(args);
			}
			else if (s[pos + 1] == 'd' || s[pos + 1] == 'i' || s[pos + 1] == 'u'|| s[pos + 1] == 'x' ||
			s[pos + 1] == 'X' || s[pos + 1] == '%')
			{
				numbers(args);
				pos = pos + characters(args);
			}
		}
		else
		{
			write(1, &s[pos], 1);
		}
		pos++;
	}
	return (pos);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	va_start(args, format);
	size_t	i;

	//number of arguments

	while (args[i] != 0)
	{
		writeformat(format, args[i]);
		i++;
	}

	if (va_arg( args,  char * ))
	if (va_arg( args,  char))
	if (va_arg( args,  int)) //%d
	if (va_arg( args,  int)) //%i
	if (va_arg( args,  unsigned int)) //%u
	if (va_arg( args,  void))
	if (va_arg( args,  unsigned int)) //%x
	if (va_arg( args,  unsigned int)) //%X
	if (va_arg( args,  char)) //%% percent sign
	va_end (args);
}
