#include "minitalk.h"

void	error(int pid, char *str)
{
	if (str)
		free(str);
	ft_putstr("server: unexpected error.\n");
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

char	*print_string(char *message)
{
	ft_putstr(message);
	free(message);
	return (NULL);
}

char    	*ft_str_add_char(char *str, char c)
{
	char	*res;
	int		i;

	if (!c)
		return (NULL);
	i = 1;
	if (str)
		i += ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (i + 1));
	res[i--] = '\0';
	res[i--] = c;
	if (str)
	{
		while (i >= 0)
		{
			res[i] = str[i];
			i--;
		}
	}
	return (res);
}

void	handler(int signum, siginfo_t *info, void *context)
{
	static char	c = 0xFF;
	static int	bits = 0;
	static int	pid = 0;
	static char	*message = 0;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (signum == SIGUSR1)
		c ^= 0x80 >> bits;
	else if (signum == SIGUSR2)
		c |= 0x80 >> bits;
	if (++bits == 8)
	{
		if (c)
			message = ft_str_add_char(message, c);
		else
			message = print_string(message);
		bits = 0;
		c = 0xFF;
	}
	if (kill(pid, SIGUSR1) == -1)
		error(pid, message);
}

int	main(void)
{
	struct sigaction	sa_signal;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa_signal.sa_handler = 0;
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_mask = block_mask;
	sa_signal.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	ft_putstr("PID: ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	while (1)
		pause();
}
