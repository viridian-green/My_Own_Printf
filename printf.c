/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:31 by ademarti          #+#    #+#             */
/*   Updated: 2023/12/07 14:29:56 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);

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
