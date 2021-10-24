/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 13:38:32 by tamigore          #+#    #+#             */
/*   Updated: 2021/10/14 17:37:26 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(sizeof(void) * size * count);
	if (!ptr)
		return (NULL);
	ptr = ft_memset(ptr, 0, count * size);
	if (!ptr)
		return (NULL);
	return (ptr);
}
