/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:10:31 by smallem           #+#    #+#             */
/*   Updated: 2023/09/10 13:56:33 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_size(int n)
{
	int				size;
	unsigned int	nb;

	size = 0;
	if (n < 0)
	{
		nb = n * (-1);
		size++;
	}
	else
		nb = n;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

int	ft_pow(int i)
{
	if (i == 0)
		return (1);
	return (10 * ft_pow(i - 1));
}

char	*ft_itoa(int n, t_term *term)
{
	int				size;
	char			*tmp;
	int				i;
	unsigned int	nb;

	size = count_size(n);
	tmp = my_malloc(&term->mem_lst, size + 1);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		tmp[i++] = '-';
		nb = n * (-1);
	}
	else
		nb = n;
	while (i < size)
	{
		tmp[i] = (nb / (ft_pow(size - i - 1))) + '0';
		nb %= ft_pow(size - (i++) - 1);
	}
	tmp[i] = '\0';
	return (tmp);
}
