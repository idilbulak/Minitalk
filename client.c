/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/23 15:02:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/03/23 15:20:49 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	ft_error_client(char *str)
{
	if (str)
		free(str);
	ft_putstr_fd("ERROR!", 1);
	exit(EXIT_FAILURE);
}

int	send_message(int pid, char *str)
{
	static char	*message = 0;
	static int	s_pid = 0;
	static int	bit_counter = 0;

	if (str)
		message = ft_strdup(str);
	if (!message)
		ft_error_client(0);
	if (pid)
		s_pid = pid;
	if (message[bit_counter / 8])
	{
		if (message[bit_counter / 8] & (0b10000000 >> (bit_counter % 8)))
		{
			if (kill(s_pid, SIGUSR2) == -1)
				ft_error_client(message);
		}
		else if (kill(s_pid, SIGUSR1) == -1)
			ft_error_client(message);
		bit_counter++;
		return (0);
	}
	free(message);
	return (1);
}

void	handler_client(int sig, siginfo_t *info, void *context)
{
	int	end;
	int	pid;

	(void)context;
	end = 0;
	pid = 0;
	if (info->si_pid)
		pid = info->si_pid;
	if (sig == SIGUSR1)
		end = send_message(pid, 0);
	if (end)
	{
		ft_putstr_fd("Message successfully sent to server!\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sact;

	if (argc != 3)
	{
		ft_putstr_fd("ERROR!\n", 1);
		exit(EXIT_FAILURE);
	}
	else
	{
		sigemptyset(&sact.sa_mask);
		sact.sa_handler = 0;
		sact.sa_sigaction = handler_client;
		sact.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sact, NULL);
		sigaction(SIGUSR2, &sact, NULL);
		send_message(atoi(argv[1]), argv[2]);
	}
	while (1)
		pause();
}
