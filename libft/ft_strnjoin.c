/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:22:44 by tamigore          #+#    #+#             */
/*   Updated: 2021/10/14 18:22:49 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char *s1, char *s2, int r)
{
	char	*join;
	char	*tmp;

	tmp = s1;
	join = ft_strnew(ft_strlen(s1) + ft_strlen(s2) - (ft_strlen(s2) - r));
	if (!s1 || !s2 || !join)
		return (NULL);
	ft_strncat(join, s1, ft_strlen(s1));
	ft_strncat(join, s2, r);
	free(tmp);
	return (join);
}
