/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 20:05:26 by tamigore          #+#    #+#             */
/*   Updated: 2021/10/14 17:50:56 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_neg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char			*p;
	int				unit;
	unsigned int	nb;
	int				i;

	i = 0;
	if (n < 0)
		nb = -n;
	else
		nb = n;
	unit = ft_nbrlen(nb);
	p = (char *)malloc(unit + 1 + ft_neg(n));
	if (!p)
		return (NULL);
	while (unit > 0)
	{
		p[i++] = nb % 10 + '0';
		nb /= 10;
		unit--;
	}
	if (n < 0)
		p[i++] = '-';
	p[i] = '\0';
	p = ft_strrev(p);
	return (p);
}
