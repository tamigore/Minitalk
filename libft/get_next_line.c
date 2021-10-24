/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:14:16 by tamigore          #+#    #+#             */
/*   Updated: 2021/10/14 18:04:42 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_lst	*ft_file(t_lst **file, int fd)
{
	t_lst	*tmp;

	tmp = *file;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = (t_lst *)malloc(sizeof(t_lst));
	if (!tmp)
		return (NULL);
	tmp->content = ft_strnew(1);
	if (!tmp->content)
		return (NULL);
	tmp->fd = fd;
	tmp->next = *file;
	*file = tmp;
	return (tmp);
}

static int	ft_strcncat(char **content, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	*content = ft_strnew(i + 1);
	if (!*content)
		return (-1);
	ft_strncat(*content, str, i);
	return (i);
}

static char	*ft_free(char *content, int r, char *buf)
{
	char	*tmp;

	tmp = content;
	content = ft_strdup(content + r);
	if (!content)
		return (NULL);
	free(tmp);
	free(buf);
	return (content);
}

static int	read_to_join(t_lst *list, int fd, int r, char *buf)
{
	while (r > 0)
	{
		buf[r] = '\0';
		list->content = ft_strnjoin(list->content, buf, r);
		if (!list->content)
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
		r = read(fd, buf, BUFFER_SIZE);
	}
	return (r);
}

int	get_next_line(int fd, char **line)
{
	static t_lst	*file;
	t_lst			*list;
	int				r;
	int				i;
	char			*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	list = ft_file(&file, fd);
	if (fd < 0 || !buf || read(fd, buf, 0) == -1 || !list || !line)
		return (-1);
	r = read(fd, buf, BUFFER_SIZE);
	r = read_to_join(list, fd, r, buf);
	if (r == -1)
		return (-1);
	i = ft_strcncat(line, list->content);
	if (i == -1)
		return (-1);
	if (r < BUFFER_SIZE && !(ft_strchr(list->content, '\n')))
		r = 0;
	else
		r = 1;
	list->content = ft_free(list->content, i + 1, buf);
	if (!list->content)
		return (-1);
	return (r);
}
