/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 16:41:32 by jbarette          #+#    #+#             */
/*   Updated: 2021/07/07 20:54:42 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_process = 0;

void	ft_quit(int i)
{
	(void)i;
	g_process = 1;
}

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(0);
}

void	endmessage(int pid)
{
	int	j;

	j = CHAR_BIT - 1;
	while (j >= 0)
	{
		g_process = 0;
		usleep(100);
		if (kill(pid, SIGUSR1) == -1)
			ft_error("Error: wrong pid\n");
		while (!g_process)
			;
		j--;
	}
}

void	message(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_process = 0;
		usleep(100);
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error("Error: wrong pid\n");
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error("Error: wrong pid\n");
		}
		while (!g_process)
			;
		i++;
	}
}

int	main(int ac, char **av)
{
	int		pid;
	int		i;

	i = -1;
	g_process = 0;
	signal(SIGUSR1, ft_quit);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		while (av[2][++i])
			message(av[2][i], pid);
		endmessage(pid);
		write(1, "Message received\n", 18);
	}
	else
		ft_error("usage: ./client [server-pid] [message]\n");
	return (1);
}
