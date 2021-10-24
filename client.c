/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamigore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 14:15:16 by tamigore          #+#    #+#             */
/*   Updated: 2021/10/24 14:39:16 by tamigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error(char *str)
{
	if (str)
		free(str);
	ft_putstr("Error in client.\n");
	exit(EXIT_FAILURE);
}

int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			error(str);
		return (0);
	}
	return (1);
}

int	send_bit(int s_pid, char *str)
{
	static int	bit = -1;
	static char	*msg = 0;
	static int	pid = 0;

	if (str)
		msg = ft_strdup(str);
	if (!msg)
		error(NULL);
	if (s_pid)
		pid = s_pid;
	if (msg[++bit / 8])
	{
		if (msg[bit / 8] & (0x80 >> (bit % 8)))
		{
			if (kill(pid, SIGUSR2) == -1)
				error(msg);
		}
		else if (kill(pid, SIGUSR1) == -1)
			error(msg);
		return (0);
	}
	if (!send_null(pid, msg))
		return (0);
	free(msg);
	return (1);
}

void	handler(int signum)
{
	int	end;

	end = 0;
	if (signum == SIGUSR1)
		end = send_bit(0, 0);
	else if (signum == SIGUSR2)
	{
		ft_putstr("Error: client received SIGUSR2");
		exit(EXIT_FAILURE);
	}
	if (end)
	{
		ft_putstr("Message received: processus end.\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	nb;

	if (ac != 3)
		exit(EXIT_FAILURE);
	i = 0;
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i++]))
			exit(EXIT_FAILURE);
	}
	nb = ft_atoi(av[1]);
	if (nb <= 0)
		exit(EXIT_FAILURE);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	send_bit(nb, av[2]);
	while (1)
		pause();
}
