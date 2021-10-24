/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:06:18 by tamigore          #+#    #+#             */
/*   Updated: 2019/11/06 15:04:51 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	init(t_list *p, t_list *tmp, t_list *lst, void (*del)(void *))
{
	if (!p)
	{
		ft_lstclear(&lst, del);
		return (0);
	}
	tmp = p;
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = NULL;
	p = ft_lstnew((*f)(lst->content));
	if (!init(p, tmp, lst, del))
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		p->next = ft_lstnew((*f)(lst->content));
		if (!p->next)
		{
			ft_lstclear(&lst, del);
			break ;
		}
		lst = lst->next;
		p = p->next;
	}
	p = tmp;
	return (p);
}
