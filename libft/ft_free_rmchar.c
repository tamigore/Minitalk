/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_rmchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 14:39:00 by tamigore          #+#    #+#             */
/*   Updated: 2021/10/14 17:45:57 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_rmchar(char *str, char c)
{
	char	*new;
	int		i;
	int		j;

	new = ft_strnew(ft_strlen(str) - ft_count_char(str, c));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
			new[j++] = str[i++];
	}
	free(str);
	return (new);
}
