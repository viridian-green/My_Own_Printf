/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:55:08 by ademarti          #+#    #+#             */
/*   Updated: 2024/01/05 16:00:20 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_put_ptr(unsigned long long num)
{
	int	count;

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
